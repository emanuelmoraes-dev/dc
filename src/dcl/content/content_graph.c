#include "dcl/content.h"
#include <limits.h>
#include <stdlib.h>

bool content_graph_contains_key1(const Content* content, const char* key1) {
	if (key1 == NULL) {
		return false;
	}

	return hash_map_contains(&content->odds_graph, key1);
}

c_err content_graph_set_key1(Content* content, owner char* key1) {
	if (key1 == NULL) {
		return DCL_ERR_THROW_NULL(DCL_ERR_ARG_NULL_GRAPH_KEY);
	}

	if (content_graph_contains_key1(content, key1)) {
		free(key1);
		return C_OK;
	}

	HashMap* dep = (HashMap*) malloc(sizeof(HashMap));

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

	c_err error = hash_map_init(dep, capacity);

	if (error != C_OK) {
		free(dep);
		free(key1);
	}

	error = hash_map_insert(&content->odds_graph, key1, dep);

	if (error != C_OK && !hash_map_contains(&content->odds_graph, key1)) {
		free(dep);
		free(key1);
	}

	return error;
}

bool content_graph_contains_key2(const Content* content, const char* key1, const char* key2) {
	if (key1 == NULL || key2 == NULL) {
		return false;
	}

	if (!hash_map_contains(&content->odds_graph, key1)) {
		return false;
	}

	HashMap* dep = (HashMap*) hash_map_get(&content->odds_graph, key1);

	if (dep == NULL) {
		return false;
	}

	return hash_map_contains(dep, key2);
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

c_err content_graph_set_key2(Content* content, const char* key1, owner char* key2) {
	if (key2 == NULL) {
		return DCL_ERR_THROW_NULL(DCL_ERR_ARG_NULL_GRAPH_KEY);
	}

	if (key1 == NULL) {
		free(key2);
		return DCL_ERR_THROW_NULL(DCL_ERR_ARG_NULL_GRAPH_KEY);
	}

	if (!content_graph_contains_key2(content, key1, key2)) {
		free(key2);
		return DCL_ERR_THROW_NOT_FOUND(DCL_ERR_ARG_NOT_FOUND_GRAPH_KEY);
	}

	HashMap* dep = (HashMap*) hash_map_get(&content->odds_graph, key1);

	if (dep == NULL) {
		free(key2);
		return DCL_ERR_THROW_NOT_FOUND(DCL_ERR_ARG_NOT_FOUND_GRAPH_DEP);
	}

	Odds* odds = (Odds*) malloc(sizeof(Odds));

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

	c_err error = hash_map_insert(dep, key2, odds);

	if (error != C_OK && !hash_map_contains(dep, key2)) {
		__graph_free(odds->graph, content->alphabet_size);
		free(odds);
		free(dep);
		free(key2);
	}

	return error;
}

c_err content_graph_borrow_odds(const Content* content, const char* key1, const char* key2, borrow Odds* odds) {
	if (key2 == NULL) {
		return DCL_ERR_THROW_NULL(DCL_ERR_ARG_NULL_GRAPH_KEY);
	}

	if (key1 == NULL) {
		return DCL_ERR_THROW_NULL(DCL_ERR_ARG_NULL_GRAPH_KEY);
	}

	if (!content_graph_contains_key2(content, key1, key2)) {
		return DCL_ERR_THROW_NOT_FOUND(DCL_ERR_ARG_NOT_FOUND_GRAPH_KEY);
	}

	HashMap* dep = (HashMap*) hash_map_get(&content->odds_graph, key1);

	if (dep == NULL) {
		return DCL_ERR_THROW_NOT_FOUND(DCL_ERR_ARG_NOT_FOUND_GRAPH_DEP);
	}

	Odds* item = (Odds*) hash_map_get(dep, key2);

	if (item == NULL) {
		return DCL_ERR_THROW_NOT_FOUND(DCL_ERR_ARG_NOT_FOUND_ODDS);
	}

	*odds = *item;

	return C_OK;
}

c_err content_graph_set_odds(Content* content, const char* key1, const char* key2, int index1, int index2, float odds_value) {
	if (index1 < 0 || index2 < 0 || index1 >= content->alphabet_size || index2 >= content->alphabet_size) {
		return DCL_ERR_THROW_INDEX_OUT(DCL_ERR_ARG_INDEX_OUT_ODDS);
	}

	Odds odds;
	c_err error = content_graph_borrow_odds(content, key1, key2, &odds);

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
