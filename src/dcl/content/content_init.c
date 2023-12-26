#include "dcl/content.h"
#include <limits.h>

c_err dcl_content_init(DclContent* content, int alphabet_size, int keys_size) {
	content->alphabet_size = alphabet_size;
	content->keys_size = keys_size;

	int capacity = DCL_HASH_MAP_CAPACITY(keys_size, UINT_MAX);
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
