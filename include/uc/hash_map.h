#ifndef UC_HASH_MAP_H_INCLUDED
#define UC_HASH_MAP_H_INCLUDED

#include "uc/errors.h"
#include "uc/tags.h"
#include <stdbool.h>

typedef struct key_value {
	owner char* key;
	void* value;
} KeyValue;

typedef struct hash_map {
	unsigned int size;
	unsigned int capacity;
	owner KeyValue* data;
} HashMap;

void key_value_init(KeyValue* key_value, move char* key, share void* value);
c_err hash_map_init(HashMap* hash_map, unsigned int capacity);
void hash_map_clear(HashMap* hash_map, void (*value_free)(void* value));
void hash_map_free(HashMap* hash_map, void (*value_free)(void* value));
bool hash_map_contains(HashMap* hash_map, const char* key);
c_err hash_map_insert(HashMap* hash_map, move char* key, share void* value);
void* hash_map_get(HashMap* hash_map, const char* key);
void* hash_map_remove(HashMap* hash_map, const char* key);

#endif
