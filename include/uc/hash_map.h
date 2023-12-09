#ifndef UC_HASH_MAP_H_INCLUDED
#define UC_HASH_MAP_H_INCLUDED

typedef struct key_value {
	char* key;
	void* value;
} KeyValue;

typedef struct hash_map {
	int size;
	int capacity;
	KeyValue* data;
} HashMap;

#endif
