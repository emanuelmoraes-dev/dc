#include <string.h>
#include <stdlib.h>
#include <stdbool.h>
#include "uc/hash_map.h"

void key_value_init(KeyValue* key_value, move char* key, move void* value) {
	key_value->key = key;
	key_value->value = value;
}

uc_err hash_map_init(HashMap* hash_map, unsigned int capacity) {
	hash_map->size = 0;
	hash_map->capacity = capacity;
	hash_map->data = (KeyValue*) malloc(sizeof(KeyValue) * capacity);

	if (hash_map->data == NULL) {
		return UC_ERR_THROW_ALLOC(UC_ERR_ARG_ALLOC_HASH_MAP_DATA);
	}

	for (unsigned int i = 0; i < capacity; ++i) {
		key_value_init(&hash_map->data[i], NULL, NULL);
	}

	return UC_OK;
}

unsigned int __key_hash(const char* key, unsigned int capacity) {
    unsigned int hash = 0;
    while (*key) {
        hash = (hash * 31) + (*key++);
    }
    return hash % capacity;
}

uc_err hash_map_insert(HashMap* hash_map, move char* key, move void* value) {
	unsigned int capacity = hash_map->capacity;
	unsigned int index = __key_hash(key, capacity);

	unsigned int count = 0;
	for (unsigned int i = index; count < capacity; i = (i + 1) % capacity, count++) {
		if (hash_map->data[i].key != NULL && strcmp(hash_map->data[i].key, key) == 0) {
			hash_map->data[i].value = value;
			return UC_OK;
		}
	}

	bool inserted = false;
	count = 0;
	for (unsigned int i = index; count < capacity; i = (i + 1) % capacity, count++) {
		if (hash_map->data[i].key == NULL) {
			key_value_init(&hash_map->data[i], key, value);
			inserted = true;
			hash_map->size++;
			break;
		}
	}

	if (hash_map->size >= capacity * 0.7) {
		unsigned int new_capacity = capacity * 2;
		KeyValue* data = (KeyValue*) realloc(hash_map->data, new_capacity * sizeof(KeyValue));

		if (data == NULL) {
			return UC_ERR_THROW_REALLOC(UC_ERR_ARG_REALLOC_HASH_MAP_DATA);
		}

		for (unsigned int i = capacity; i < new_capacity; i++) {
			key_value_init(&data[i], NULL, NULL);
		}

		hash_map->data = data;
		hash_map->capacity = new_capacity;
	}

	if (!inserted) {
		return hash_map_insert(hash_map, key, value);
	}

	return UC_OK;
}
