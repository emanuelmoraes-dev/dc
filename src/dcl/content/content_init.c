#include "dcl/content.h"
#include <limits.h>

c_err dcl_content_init(DclContent* content, int alphabet_size, int keys_size) {
	content->alphabet_size = alphabet_size;
	content->keys_size = keys_size;

	int capacity;

	if(!UC_ERR_IS_OVERFLOW_LARGE_MULT(keys_size, CONTENT_CAPACITY_FACTOR, INT_MAX)) {
		capacity = keys_size * CONTENT_CAPACITY_FACTOR;
	} else if (!UC_ERR_IS_OVERFLOW_LARGE_MULT(keys_size, HASH_MAP_CAPACITY_FACTOR, UINT_MAX)) {
		capacity = keys_size * HASH_MAP_CAPACITY_FACTOR;
	} else {
		capacity = keys_size;
	}

	c_err error = uc_hash_map_init(&content->alphabet, capacity);

	if (error != C_OK) {
		dcl_content_free(content);
		return error;
	}

	error = uc_hash_map_init(&content->odds_graph, keys_size);

	if (error != C_OK) {
		dcl_content_free(content);
		return error;
	}

	return C_OK;
}
