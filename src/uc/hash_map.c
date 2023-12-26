#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include <limits.h>
#include "uc/hash_map.h"

void uc_key_value_init(UcKeyValue* key_value, owner char* key, share void* value) {
	key_value->key = key;
	key_value->value = value;
}

UcKeyValue* __uc_hash_map_new_data(int capacity) {
	UcKeyValue* data = (UcKeyValue*) malloc(sizeof(UcKeyValue) * capacity);

	if (data == NULL) {
		return NULL;
	}

	for (int i = 0; i < capacity; ++i) {
		uc_key_value_init(&data[i], NULL, NULL);
	}

	return data;
}

c_err uc_hash_map_init(UcHashMap* hash_map, int capacity) {
	hash_map->size = 0;
	hash_map->capacity = capacity;
	hash_map->data = __uc_hash_map_new_data(capacity);

	if (hash_map->data == NULL) {
		return UC_ERR_THROW_ALLOC(UC_ERR_ARG_ALLOC_HASH_MAP_DATA);
	}

	return C_OK;
}

void uc_hash_map_clear(UcHashMap* hash_map, void (*value_free)(void* value)) {
	UcKeyValue* data = hash_map->data;
	int capacity = hash_map->capacity;

	if (data == NULL) {
		return;
	}
	
	for (int i = 0; i < capacity; ++i) {
		if (data[i].key != NULL) {
			free(data[i].key);
			data[i].key = NULL;
		}

		if (data[i].value != NULL && value_free != NULL) {
			value_free(data[i].value);
			data[i].value = NULL;
		}
	}
}

void uc_hash_map_free(UcHashMap* hash_map, void (*value_free)(void* value)) {
	uc_hash_map_clear(hash_map, value_free);
	if (hash_map->data != NULL) {
		free(hash_map->data);
		hash_map->data = NULL;
	}
}

int __key_hash(const char* key, int capacity) {
    unsigned int hash = 0;
    while (*key) {
        hash = (hash * 31) + (*key++);
    }
    return hash % capacity;
}

int __uc_hash_map_index(const UcHashMap* hash_map, const char* key) {
	int capacity = hash_map->capacity;
	int index = __key_hash(key, capacity);

	int count = 0;
	for (int i = index; count < capacity; i = (i + 1) % capacity, ++count) {
		if (hash_map->data[i].key != NULL && strcmp(hash_map->data[i].key, key) == 0) {
			return i;
		}
	}

	return -1;
}

bool uc_hash_map_contains(const UcHashMap* hash_map, const char* key) {
	return __uc_hash_map_index(hash_map, key) >= 0;
}

bool __uc_hash_map_set(UcHashMap* hash_map, owner char* key, share void* value) {
	int index = __uc_hash_map_index(hash_map, key);

	if (index >= 0) {
		hash_map->data[index].value = value;
		return true;
	}

	int capacity = hash_map->capacity;
	index = __key_hash(key, capacity);
	bool inserted = false;
	int count = 0;

	for (int i = index; count < capacity; i = (i + 1) % capacity, ++count) {
		if (hash_map->data[i].key == NULL) {
			uc_key_value_init(&hash_map->data[i], key, value);
			inserted = true;
			hash_map->size++;
			break;
		}
	}

	return inserted;
}

c_err __uc_hash_map_realloc(UcHashMap* hash_map) {
	UcKeyValue* bk_data = hash_map->data;
	int bk_capacity = hash_map->capacity;

	if (UC_ERR_IS_OVERFLOW_LARGE_MULT(bk_capacity, 2, INT_MAX)) {
		return UC_ERR_THROW_OVERFLOW(UC_ERR_ARG_OVERFLOW_LARGE_HASH_MAP_CAPACITY);
	}

	int new_capacity = bk_capacity * 2;
	UcKeyValue* new_data = __uc_hash_map_new_data(new_capacity);

	if (new_data == NULL) {
		return UC_ERR_THROW_REALLOC(UC_ERR_ARG_REALLOC_HASH_MAP_DATA);
	}

	hash_map->data = new_data;
	hash_map->capacity = new_capacity;
	hash_map->size = 0;

	for (int i = 0; i < bk_capacity; ++i) {
		if (bk_data[i].key != NULL) {
			__uc_hash_map_set(hash_map, bk_data[i].key, bk_data[i].value);
		}
	}

	free(bk_data);
	return C_OK;
}

c_err uc_hash_map_insert(UcHashMap* hash_map, owner char* key, share void* value) {
	bool inserted = __uc_hash_map_set(hash_map, key, value);

	if (hash_map->size > hash_map->capacity * UC_HASH_MAP_SIZE_FACTOR) {
		c_err error = __uc_hash_map_realloc(hash_map);

		if (error != C_OK) {
			return error;
		}
	}

	if (!inserted) {
		__uc_hash_map_set(hash_map, key, value);
	}

	return C_OK;
}

void* uc_hash_map_get(const UcHashMap* hash_map, const char* key) {
	int index = __uc_hash_map_index(hash_map, key);

	if (index < 0) {
		return NULL;
	}

	return hash_map->data[index].value;
}

void* uc_hash_map_remove(UcHashMap* hash_map, const char* key) {
	int index = __uc_hash_map_index(hash_map, key);

	if (index < 0) {
		return NULL;
	}

	void* value = hash_map->data[index].value;
	hash_map->data[index].value = NULL;

	if (hash_map->data[index].key != NULL) {
		free(hash_map->data[index].key);
		hash_map->data[index].key = NULL;
	}

	return value;
}

void uc_hash_map_make_iterator(const UcHashMap* hash_map, UcHashMapIterator* iterator) {
	iterator->index = -1;
}

int __uc_hash_map_next_index(const UcHashMapIterator* iterator) {
	if (iterator->index < 0) {
		return 0;
	}
	return iterator->index + 1;
}

bool uc_hash_map_has_next(const UcHashMap* hash_map, const UcHashMapIterator* iterator) {
	int capacity = hash_map->capacity;
	int index = __uc_hash_map_next_index(iterator);

	if (index < 0 || index >= hash_map->capacity) {
		return false;
	}

	for (int i = index; i < capacity; ++i) {
		if (hash_map->data[i].key != NULL) {
			return true;
		}
	}

	return false;
}

c_err uc_hash_map_next(const UcHashMap* hash_map, UcHashMapIterator* iterator) {
	int capacity = hash_map->capacity;
	int index = __uc_hash_map_next_index(iterator);

	if (index < 0 || index >= hash_map->capacity) {
		return UC_ERR_THROW_NOT_FOUND(UC_ERR_ARG_NOT_FOUND_HASH_MAP_ITEM);
	}

	for (int i = index; i < capacity; ++i) {
		if (hash_map->data[i].key != NULL) {
			iterator->index = i;
			return C_OK;
		}
	}
	return UC_ERR_THROW_NOT_FOUND(UC_ERR_ARG_NOT_FOUND_HASH_MAP_ITEM);
}

c_err uc_hash_map_borrow_key_value(const UcHashMap* hash_map, const UcHashMapIterator* iterator, borrow char** key, borrow void** value) {
	int index = iterator->index;
	if (index < 0 || index >= hash_map->capacity) {
		return UC_ERR_THROW_NOT_FOUND(UC_ERR_ARG_NOT_FOUND_HASH_MAP_ITEM);
	}
	if (hash_map->data[index].key == NULL) {
		return UC_ERR_THROW_NOT_FOUND(UC_ERR_ARG_NOT_FOUND_HASH_MAP_ITEM);
	}
	*key = hash_map->data[index].key;
	*value = hash_map->data[index].value;
	return C_OK;
}
