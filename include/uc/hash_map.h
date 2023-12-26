#ifndef UC_HASH_MAP_H_INCLUDED
#define UC_HASH_MAP_H_INCLUDED

#include "uc/errors.h"
#include "uc/tags.h"
#include <stdbool.h>

#define UC_HASH_MAP_SIZE_FACTOR (0.7)

typedef struct uc_key_value {
	owner char* key;
	share void* value;
} UcKeyValue;

typedef struct uc_hash_map {
	int size;
	int capacity;
	owner UcKeyValue* data;
} UcHashMap;

typedef struct uc_hash_map_iterator {
	int index;
} UcHashMapIterator;

void uc_key_value_init(UcKeyValue* key_value, owner char* key, share void* value);
c_err uc_hash_map_init(UcHashMap* hash_map, int capacity);
void uc_hash_map_clear(UcHashMap* hash_map, void (*value_free)(void* value));
void uc_hash_map_free(UcHashMap* hash_map, void (*value_free)(void* value));
bool uc_hash_map_contains(const UcHashMap* hash_map, const char* key);
c_err uc_hash_map_insert(UcHashMap* hash_map, owner char* key, share void* value);
void* uc_hash_map_get(const UcHashMap* hash_map, const char* key);
void* uc_hash_map_remove(UcHashMap* hash_map, const char* key);
void uc_hash_map_make_iterator(const UcHashMap* hash_map, UcHashMapIterator* iterator);
bool uc_hash_map_has_next(const UcHashMap* hash_map, const UcHashMapIterator* iterator);
c_err uc_hash_map_next(const UcHashMap* hash_map, UcHashMapIterator* iterator);
c_err uc_hash_map_borrow_key_value(const UcHashMap* hash_map, const UcHashMapIterator* iterator, borrow char** key, borrow void** value);

#endif
