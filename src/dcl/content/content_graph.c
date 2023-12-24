#include "dcl/content.h"
#include <limits.h>
#include <stdlib.h>

bool dcl_content_graph_contains_key1(const DclContent* content, const char* key1) {
	if (key1 == NULL) {
		return false;
	}

	return uc_hash_map_contains(&content->odds_graph, key1);
}

c_err dcl_content_graph_set_key1(DclContent* content, owner char* key1) {
	if (key1 == NULL) {
		return DCL_ERR_THROW_NULL(DCL_ERR_ARG_NULL_GRAPH_KEY);
	}

	if (dcl_content_graph_contains_key1(content, key1)) {
		free(key1);
		return C_OK;
	}

	UcHashMap* dep = (UcHashMap*) malloc(sizeof(UcHashMap));

	if (dep == NULL) {
		free(key1);
		return DCL_ERR_THROW_ALLOC(DCL_ERR_ARG_ALLOC_DEP_GRAPH);
	}

	int keys_size = content->keys_size;
	int capacity;

	if(!UC_ERR_IS_OVERFLOW_LARGE_MULT(keys_size, CONTENT_CAPACITY_FACTOR, INT_MAX)) {
		capacity = keys_size * CONTENT_CAPACITY_FACTOR;
	} else if (!UC_ERR_IS_OVERFLOW_LARGE_MULT(keys_size, HASH_MAP_CAPACITY_FACTOR, UINT_MAX)) {
		capacity = keys_size * HASH_MAP_CAPACITY_FACTOR;
	} else {
		capacity = keys_size;
	}

	c_err error = uc_hash_map_init(dep, capacity);

	if (error != C_OK) {
		free(dep);
		free(key1);
	}

	error = uc_hash_map_insert(&content->odds_graph, key1, dep);

	if (error != C_OK && !uc_hash_map_contains(&content->odds_graph, key1)) {
		free(dep);
		free(key1);
	}

	return error;
}

bool dcl_content_graph_contains_key2(const DclContent* content, const char* key1, const char* key2) {
	if (key1 == NULL || key2 == NULL) {
		return false;
	}

	if (!uc_hash_map_contains(&content->odds_graph, key1)) {
		return false;
	}

	UcHashMap* dep = (UcHashMap*) uc_hash_map_get(&content->odds_graph, key1);

	if (dep == NULL) {
		return false;
	}

	return uc_hash_map_contains(dep, key2);
}

void __graph_free(float** graph, int size) {
	if (graph == NULL) {
		return;
	}

	for (int i = 0; i < size; ++i) {
		float* node = graph[i];

		if (node != NULL) {
			free(node);
		}
	}

	free(graph);
}

c_err dcl_content_graph_set_key2(DclContent* content, const char* key1, owner char* key2) {
	if (key2 == NULL) {
		return DCL_ERR_THROW_NULL(DCL_ERR_ARG_NULL_GRAPH_KEY);
	}

	if (key1 == NULL) {
		free(key2);
		return DCL_ERR_THROW_NULL(DCL_ERR_ARG_NULL_GRAPH_KEY);
	}

	if (!dcl_content_graph_contains_key2(content, key1, key2)) {
		free(key2);
		return DCL_ERR_THROW_NOT_FOUND(DCL_ERR_ARG_NOT_FOUND_GRAPH_KEY);
	}

	UcHashMap* dep = (UcHashMap*) uc_hash_map_get(&content->odds_graph, key1);

	if (dep == NULL) {
		free(key2);
		return DCL_ERR_THROW_NOT_FOUND(DCL_ERR_ARG_NOT_FOUND_GRAPH_DEP);
	}

	DclOdds* odds = (DclOdds*) malloc(sizeof(DclOdds));

	if (odds == NULL) {
		free(dep);
		free(key2);
		return DCL_ERR_THROW_ALLOC(DCL_ERR_ARG_ALLOC_ODDS);
	}

	odds->content = content;
	odds->graph = (float**) malloc(sizeof(float*) * content->alphabet_size);

	if (odds->graph == NULL) {
		free(odds);
		free(dep);
		free(key2);
		return DCL_ERR_THROW_ALLOC(DCL_ERR_ARG_ALLOC_ODDS_GRAPH);
	}

	for (int i = 0; i < content->alphabet_size; ++i) {
		odds->graph[i] = (float*) malloc(sizeof(float) * content->alphabet_size);

		if (odds->graph[i] == NULL) {
			__graph_free(odds->graph, i);
			free(odds);
			free(dep);
			free(key2);
			return DCL_ERR_THROW_ALLOC(DCL_ERR_ARG_ALLOC_ODDS_GRAPH_NODE);
		}

		for (int j = 0; j < content->alphabet_size; ++j) {
			odds->graph[i][j] = 1;
		}
	}

	c_err error = uc_hash_map_insert(dep, key2, odds);

	if (error != C_OK && !uc_hash_map_contains(dep, key2)) {
		__graph_free(odds->graph, content->alphabet_size);
		free(odds);
		free(dep);
		free(key2);
	}

	return error;
}

c_err dcl_content_graph_borrow_odds(const DclContent* content, const char* key1, const char* key2, borrow DclOdds* odds) {
	if (key2 == NULL) {
		return DCL_ERR_THROW_NULL(DCL_ERR_ARG_NULL_GRAPH_KEY);
	}

	if (key1 == NULL) {
		return DCL_ERR_THROW_NULL(DCL_ERR_ARG_NULL_GRAPH_KEY);
	}

	if (!dcl_content_graph_contains_key2(content, key1, key2)) {
		return DCL_ERR_THROW_NOT_FOUND(DCL_ERR_ARG_NOT_FOUND_GRAPH_KEY);
	}

	UcHashMap* dep = (UcHashMap*) uc_hash_map_get(&content->odds_graph, key1);

	if (dep == NULL) {
		return DCL_ERR_THROW_NOT_FOUND(DCL_ERR_ARG_NOT_FOUND_GRAPH_DEP);
	}

	DclOdds* item = (DclOdds*) uc_hash_map_get(dep, key2);

	if (item == NULL) {
		return DCL_ERR_THROW_NOT_FOUND(DCL_ERR_ARG_NOT_FOUND_ODDS);
	}

	*odds = *item;

	return C_OK;
}

c_err dcl_content_graph_set_odds(DclContent* content, const char* key1, const char* key2, int index1, int index2, float odds_value) {
	if (index1 < 0 || index2 < 0 || index1 >= content->alphabet_size || index2 >= content->alphabet_size) {
		return DCL_ERR_THROW_INDEX_OUT(DCL_ERR_ARG_INDEX_OUT_ODDS);
	}

	DclOdds odds;
	c_err error = dcl_content_graph_borrow_odds(content, key1, key2, &odds);

	float** graph = odds.graph;

	if (graph == NULL) {
		return DCL_ERR_THROW_NOT_FOUND(DCL_ERR_ARG_NOT_FOUND_GRAPH);
	}

	float* node = graph[index1];

	if (node == NULL) {
		return DCL_ERR_THROW_NOT_FOUND(DCL_ERR_ARG_NOT_FOUND_GRAPH_NODE);
	}

	node[index2] = odds_value;

	return C_OK;
}
