#ifndef UC_HASH_MAP_H_INCLUDED
#define UC_HASH_MAP_H_INCLUDED

#include "uc/errors.h"
#include "uc/tags.h"

typedef struct key_value {
	owner char* key;
	owner void* value;
} KeyValue;

typedef struct hash_map {
	unsigned int size;
	unsigned int capacity;
	owner KeyValue* data;
} HashMap;

void key_value_init(KeyValue* key_value, move char* key, move void* value);
c_err hash_map_init(HashMap* hash_map, unsigned int capacity);
c_err hash_map_insert(HashMap* hash_map, move char* key, move void* value);

#endif
