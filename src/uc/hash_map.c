#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "uc/hash_map.h"

void key_value_init(KeyValue* key_value, move char* key, share void* value) {
	key_value->key = key;
	key_value->value = value;
}

KeyValue* __hash_map_new_data(unsigned int capacity) {
	KeyValue* data = (KeyValue*) malloc(sizeof(KeyValue) * capacity);

	if (data == NULL) {
		return NULL;
	}

	for (unsigned int i = 0; i < capacity; ++i) {
		key_value_init(&data[i], NULL, NULL);
	}

	return data;
}

c_err hash_map_init(HashMap* hash_map, unsigned int capacity) {
	hash_map->size = 0;
	hash_map->capacity = capacity;
	hash_map->data = __hash_map_new_data(capacity);

	if (hash_map->data == NULL) {
		return UC_ERR_THROW_ALLOC(UC_ERR_ARG_ALLOC_HASH_MAP_DATA);
	}

	return C_OK;
}

void __hash_map_data_free(KeyValue* data, void (*value_free)(void* value), unsigned int capacity) {
	if (data == NULL) {
		return;
	}

	
	for (unsigned int i = 0; i < capacity; ++i) {
		free(data[i].key);
		if (value_free != NULL) {
			value_free(data[i].value);
		}
	}
}

void hash_map_free(HashMap* hash_map, void (*value_free)(void* value)) {
	__hash_map_data_free(hash_map->data, value_free, hash_map->capacity);
}

unsigned int __key_hash(const char* key, unsigned int capacity) {
    unsigned int hash = 0;
    while (*key) {
        hash = (hash * 31) + (*key++);
    }
    return hash % capacity;
}

bool __hash_map_set(HashMap* hash_map, move char* key, share void* value) {
	unsigned int capacity = hash_map->capacity;
	unsigned int index = __key_hash(key, capacity);

	unsigned int count = 0;
	for (unsigned int i = index; count < capacity; i = (i + 1) % capacity, ++count) {
		if (hash_map->data[i].key != NULL && strcmp(hash_map->data[i].key, key) == 0) {
			hash_map->data[i].value = value;
			return true;
		}
	}

	bool inserted = false;
	count = 0;
	for (unsigned int i = index; count < capacity; i = (i + 1) % capacity, ++count) {
		if (hash_map->data[i].key == NULL) {
			key_value_init(&hash_map->data[i], key, value);
			inserted = true;
			hash_map->size++;
			break;
		}
	}

	return inserted;
}

c_err __hash_map_realloc(HashMap* hash_map) {
	KeyValue* bk_data = hash_map->data;
	unsigned int bk_capacity = hash_map->capacity;
	unsigned int new_capacity = bk_capacity * 2;
	KeyValue* new_data = __hash_map_new_data(new_capacity);

	if (new_data == NULL) {
		return UC_ERR_THROW_REALLOC(UC_ERR_ARG_REALLOC_HASH_MAP_DATA);
	}

	hash_map->data = new_data;
	hash_map->capacity = new_capacity;
	hash_map->size = 0;

	for (unsigned int i = 0; i < bk_capacity; ++i) {
		if (bk_data[i].key != NULL) {
			__hash_map_set(hash_map, bk_data[i].key, bk_data[i].value);
		}
	}

	free(bk_data);
	return C_OK;
}

c_err hash_map_insert(HashMap* hash_map, move char* key, share void* value) {
	bool inserted = __hash_map_set(hash_map, key, value);

	if (hash_map->size >= hash_map->capacity * 0.7) {
		c_err error = __hash_map_realloc(hash_map);

		if (error != C_OK) {
			return error;
		}
	}

	if (!inserted) {
		__hash_map_set(hash_map, key, value);
	}

	return C_OK;
}

void* hash_map_get(HashMap* hash_map, const char* key) {
	unsigned int capacity = hash_map->capacity;
	unsigned int index = __key_hash(key, capacity);

	unsigned int count = 0;
	for (unsigned int i = index; count < capacity; i = (i + 1) % capacity, ++count) {
		if (hash_map->data[i].key != NULL && strcmp(hash_map->data[i].key, key) == 0) {
			return hash_map->data[i].value;
		}
	}

	return NULL;
}
