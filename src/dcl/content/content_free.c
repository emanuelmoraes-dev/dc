#include "dcl/content.h"
#include "uc/math_util.h"
#include <stdlib.h>

void __sentences_free(void* value);
void __odds_deps_free(void* value);
void __odds_free(void* value);

void content_free(Content* content) {
	hash_map_free(&content->alphabet, __sentences_free);
	hash_map_free(&content->odds_graph, __odds_deps_free);
}

void __sentences_free(void* value) {
	if (value == NULL) {
		return;
	}

	owner Sentences* sentences = (Sentences*) value;

	if (sentences->list != NULL) {
		owner char** list = sentences->list;
		int size = MAX(sentences->size, 0);

		for (int i = 0; i < size; ++i) {
			owner char* sentence = list[i];

			if (sentence != NULL) {
				free(sentence);
				list[i] = NULL;
			}
		}

		free(list);
		sentences->list = NULL;
		sentences->size = 0;
	}

	free(sentences);
}

void __odds_deps_free(void* value) {
	if (value == NULL) {
		return;
	}

	owner HashMap* odds_deps = (HashMap*) value;
	hash_map_free(odds_deps, __odds_free);
	free(odds_deps);
}

void __odds_free(void* value) {
	if (value == NULL) {
		return;
	}

	owner Odds* odds = (Odds*) value;
	share Content* content = odds->content;

	if (content != NULL && odds->graph != NULL) {
		owner float** graph = odds->graph;
		int alphabet_size = content->alphabet_size;

		for (int i = 0; i < alphabet_size; ++i) {
			owner float* node = graph[i];

			if (node != NULL) {
				free(node);
				graph[i] = NULL;
			}
		}

		free(graph);
		odds->graph = NULL;
	}

	free(odds);
}
