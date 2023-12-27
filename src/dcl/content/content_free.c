#include "dcl/content.h"
#include "uc/math_util.h"
#include <stdlib.h>

void __sentences_free(void* value);
void __odds_deps_free(void* value);
void __odds_free(void* value);

void dcl_content_free(DclContent* content) {
	uc_hash_map_free(&content->alphabet, __sentences_free);
	uc_hash_map_free(&content->odds_graph, __odds_deps_free);
}

void dcl_sentences_free(DclSentences* sentences) {
	if (sentences->array != NULL) {
		owner char** array = sentences->array;
		int size = MAX(sentences->size, 0);

		for (int i = 0; i < size; ++i) {
			owner char* sentence = array[i];

			if (sentence != NULL) {
				free(sentence);
				array[i] = NULL;
			}
		}

		free(array);
		sentences->array = NULL;
		sentences->size = 0;
	}

	free(sentences);
}

void __sentences_free(void* value) {
	if (value == NULL) {
		return;
	}

	owner DclSentences* sentences = (DclSentences*) value;
	dcl_sentences_free(sentences);
}

void __odds_deps_free(void* value) {
	if (value == NULL) {
		return;
	}

	owner UcHashMap* odds_deps = (UcHashMap*) value;
	uc_hash_map_free(odds_deps, __odds_free);
	free(odds_deps);
}

void __odds_free(void* value) {
	if (value == NULL) {
		return;
	}

	owner DclOdds* odds = (DclOdds*) value;
	share DclContent* content = odds->content;

	if (content != NULL && odds->graph != NULL) {
		owner DclOddsValue** graph = odds->graph;
		int alphabet_size = content->alphabet_size;

		for (int i = 0; i < alphabet_size; ++i) {
			owner DclOddsValue* node = graph[i];

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
