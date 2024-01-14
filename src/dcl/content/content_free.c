#include "dcl/content.h"
#include "dcl/logs.h"
#include <stdlib.h>

void __odds_deps_free(void* value);
void __odds_free(void* value);

void dcl_content_free(DclContent* content) {
	DCL_LOG(INFO, "clearing alphabet content...");
	uc_hash_map_free(&content->alphabet, dcl_sentences_free);

	DCL_LOG(INFO, "clearing odds graph content...");
	uc_hash_map_free(&content->odds_graph, __odds_deps_free);

	DCL_LOG(INFO, "content freed from memory");
}

void dcl_sentences_free(void* value) {
	if (value == NULL) {
		return;
	}

	DclSentences* sentences = (DclSentences*) value;

	if (sentences->array != NULL) {
		DCL_LOG(DEBUG, "clearing sentences data...");

		owner char** array = sentences->array;
		int size = sentences->size;

		for (int i = 0; i < size; ++i) {
			owner char* sentence = array[i];

			if (sentence != NULL) {
				UC_LOG_BUFFER(logs, format, "clearing sentence '%s'...", strlen(sentence));
				uc_log_format(logs, sizeof(logs), format, sentence);
				DCL_LOG(DEBUG, logs);

				free(sentence);
				array[i] = NULL;
			}
		}

		DCL_LOG(DEBUG, "clearing sentences data...");

		free(array);
		sentences->array = NULL;
		sentences->size = 0;
	}

	DCL_LOG(DEBUG, "clearing sentences...");

	free(sentences);
}

void __odds_deps_free(void* value) {
	if (value == NULL) {
		return;
	}

	owner UcHashMap* odds_deps = (UcHashMap*) value;

	DCL_LOG(DEBUG, "clearing odds dep data...");
	uc_hash_map_free(odds_deps, __odds_free);

	DCL_LOG(DEBUG, "clearing odds dep...");
	free(odds_deps);
}

void __odds_free(void* value) {
	if (value == NULL) {
		return;
	}

	owner DclOdds* odds = (DclOdds*) value;
	share DclContent* content = odds->content;

	if (content != NULL && odds->graph != NULL) {
		DCL_LOG(DEBUG, "clearing odds graph value data...");

		owner DclOddsValue** graph = odds->graph;
		int alphabet_size = content->alphabet_size;

		for (int i = 0; i < alphabet_size; ++i) {
			owner DclOddsValue* node = graph[i];

			if (node != NULL) {
				DCL_LOG(DEBUG, "clearing odds graph node...");

				free(node);
				graph[i] = NULL;
			}
		}

		DCL_LOG(DEBUG, "clearing odds graph value...");

		free(graph);
		odds->graph = NULL;
	}

	DCL_LOG(DEBUG, "clearing odds graph...");
	free(odds);
}
