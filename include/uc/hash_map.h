#ifndef UC_HASH_MAP_H_INCLUDED
#define UC_HASH_MAP_H_INCLUDED

#include "uc/errors.h"
#include "uc/tags.h"
#include <stdbool.h>

#define UC_HASH_MAP_SIZE_FACTOR (0.7)

typedef struct key_value {
	owner char* key;
	void* value;
} KeyValue;

typedef struct hash_map {
	int size;
	int capacity;
	owner KeyValue* data;
} HashMap;

typedef struct hash_map_iterator {
	int index;
} HashMapIterator;

void key_value_init(KeyValue* key_value, move char* key, share void* value);
c_err hash_map_init(HashMap* hash_map, int capacity);
void hash_map_clear(HashMap* hash_map, void (*value_free)(void* value));
void hash_map_free(HashMap* hash_map, void (*value_free)(void* value));
bool hash_map_contains(const HashMap* hash_map, const char* key);
c_err hash_map_insert(HashMap* hash_map, move char* key, share void* value);
void* hash_map_get(const HashMap* hash_map, const char* key);
void* hash_map_remove(HashMap* hash_map, const char* key);
void hash_map_make_iterator(const HashMap* hash_map, HashMapIterator* iterator);
bool hash_map_has_next(const HashMap* hash_map, const HashMapIterator* iterator);
c_err hash_map_next(const HashMap* hash_map, HashMapIterator* iterator);
c_err hash_map_share_key_value(const HashMap* hash_map, const HashMapIterator* iterator, share char** key, share void** value);

#endif
