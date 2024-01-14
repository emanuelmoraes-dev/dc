#include "dcl/content.h"
#include "dcl/logs.h"
#include "uc/hash_map.h"
#include "uc/linked_list.h"
#include "uc/array.h"
#include "uc/quick_sort.h"
#include "uc/math_util.h"
#include <string.h>
#include <stdlib.h>
#include <limits.h>
#include <math.h>

c_err __gen_targets(const DclContent* content, UcHashMap* dcl_sentences_result, const DclGenInput* gen_input);
c_err dcl_content_gen(const DclContent* content, UcHashMap* dcl_sentences_result, const DclGenInput* gen_input) {
	return __gen_targets(content, dcl_sentences_result, gen_input);
}

typedef struct string_entry {
	const char* value;
	int index;
} StringEntry;

typedef struct odds_value_entry {
	const DclOddsValue* value;
	int index;
} OddsValueEntry;

void __string_entries(StringEntry* entries, const char** data, int size);
void __odds_value_entries(OddsValueEntry* entries, const DclOddsValue* data, int size);
void __array_init_string_entry(UcArray* array, const StringEntry* data, int size);
void __array_init_odds_value_entry(UcArray* array, const OddsValueEntry* data, int size);

c_err __gen_dep(const DclContent* content, UcHashMap* dcl_sentences_result, const DclGenInput* gen_input, const char* target_key, borrow StringEntry* target_sentence);
c_err __gen_targets(const DclContent* content, UcHashMap* dcl_sentences_result, const DclGenInput* gen_input) {
	DCL_LOG(INFO, "generating target sentences...");

	for (int k = 0; k < gen_input->target_keys_size; ++k) {
		const char* target_key = gen_input->target_keys[k];

		UC_LOG_BUFFER(logs1, format1, "getting sentences of %s", strlen(target_key));
		uc_log_format(logs1, sizeof(logs1), format1, target_key);
		DCL_LOG(INFO, logs1);

		DclSentences* sentences = (DclSentences*) uc_hash_map_get(&content->alphabet, target_key);

		if (sentences == NULL) {
			DCL_LOG(ERR, "sentences not found");
			return dcl_err_throw_not_found(DCL_ERR_ARG_NOT_FOUND_ALPHABET_KEY);
		}

		DCL_LOG(INFO, "generating senteces entries...");

		StringEntry sentences_entries[sentences->size];
		__string_entries(sentences_entries, (const char**) sentences->array, sentences->size);

		DCL_LOG(INFO, "shuffling sentences entries...");

		UcArray sentences_entries_array;
		__array_init_string_entry(&sentences_entries_array, sentences_entries, sentences->size);
		uc_array_shuffle(&sentences_entries_array);
		int sentences_size = MIN(sentences->size, gen_input->target_sentences_size);

		for (int s = 0; s < sentences_size; ++s) {
			StringEntry* entry_sentence = &sentences_entries[s];

			if (entry_sentence == NULL || entry_sentence->value == NULL) {
				DCL_LOG(ERR, "Sentence NULL");
				return dcl_err_throw_not_found(DCL_ERR_ARG_NOT_FOUND_ALPHABET_SENTENCE);
			}

			UC_LOG_BUFFER(logs2, format2, "generating sentence dependencies of target sentence '%s'...", strlen(entry_sentence->value));
			uc_log_format(logs2, sizeof(logs2), format2, entry_sentence->value);
			DCL_LOG(INFO, logs2);

			c_err error = __gen_dep(content, dcl_sentences_result, gen_input, target_key, entry_sentence);

			if (error != C_OK) {
				UC_LOG_BUFFER(logs, format, "error generating sentence dependences: %d", 10);
				uc_log_format(logs, sizeof(logs), format, error);
				DCL_LOG(ERR, logs);

				return error;
			}
		}
	}

	return C_OK;
}

c_err __gen_required(const DclContent* content, UcLinkedList* dep_sentences, const DclSentences* sentences, DclOddsValue* node);
c_err __gen_rand_factor(const DclContent* content, UcLinkedList* dep_sentences, const DclSentences* sentences, const OddsValueEntry* node_entries, int min_dep_sentences);
c_err __gen_result(const DclContent* content, UcHashMap* dcl_sentences_result, const char* target_key, const UcLinkedList* dep_sentences);
c_err __gen_dep(const DclContent* content, UcHashMap* dcl_sentences_result, const DclGenInput* gen_input, const char* target_key, borrow StringEntry* target_sentence) {
	DCL_LOG(INFO, "generating dependences sentences...");

	UcLinkedList dep_sentences;
	c_err error = uc_linked_list_init(&dep_sentences);

	if (error != C_OK) {
		UC_LOG_BUFFER(logs, format, "error initializing dependences sentences list: %d", 10);
		uc_log_format(logs, sizeof(logs), format, error);
		DCL_LOG(ERR, logs);
		return error;
	}

	DCL_LOG(INFO, "adding target sentence...");

	error = uc_linked_list_add_last(&dep_sentences, (void*) target_sentence->value);

	if (error != C_OK) {
		UC_LOG_BUFFER(logs, format, "error edding target sentence: %d", 10);
		uc_log_format(logs, sizeof(logs), format, error);
		DCL_LOG(ERR, logs);

		uc_linked_list_free(&dep_sentences);
		return error;
	}

	for (int d = 0; d < gen_input->dep_keys_size; ++d) {
		const char* dep_key = gen_input->dep_keys[d];

		UC_LOG_BUFFER(logs1, format1, "getting sentences of dependence sentence '%s'", strlen(dep_key));
		uc_log_format(logs1, sizeof(logs1), format1, dep_key);
		DCL_LOG(INFO, logs1);

		const DclSentences* sentences = (const DclSentences*) uc_hash_map_get(&content->alphabet, dep_key);

		if (sentences == NULL) {
			DCL_LOG(ERR, "sentences NULL");

			uc_linked_list_free(&dep_sentences);
			return dcl_err_throw_not_found(DCL_ERR_ARG_NOT_FOUND_ALPHABET_KEY);
		}

		DCL_LOG(INFO, "getting graph dependences of target key...");

		const UcHashMap* dep = (UcHashMap*) uc_hash_map_get(&content->odds_graph, target_key);

		if (dep == NULL) {
			DCL_LOG(ERR, "graph dependences NULL");

			uc_linked_list_free(&dep_sentences);
			return dcl_err_throw_not_found(DCL_ERR_ARG_NOT_FOUND_GRAPH_DEP_KEY);
		}

		DCL_LOG(INFO, "getting graph odds of dependence key...");

		const DclOdds* odds = (DclOdds*) uc_hash_map_get(dep, dep_key);

		if (odds == NULL) {
			DCL_LOG(ERR, "graph odds NULL");

			uc_linked_list_free(&dep_sentences);
			return dcl_err_throw_not_found(DCL_ERR_ARG_NOT_FOUND_ODDS);
		}

		UC_LOG_BUFFER(logs2, format2, "getting readonly odds value of target sentence index %d...", 10);
		uc_log_format(logs2, sizeof(logs2), format2, target_sentence->index);
		DCL_LOG(INFO, logs2);

		const DclOddsValue* src_node = odds->graph[target_sentence->index];

		if (src_node == NULL) {
			DCL_LOG(ERR, "odds value NULL");
			return dcl_err_throw_not_found(DCL_ERR_ARG_NOT_FOUND_GRAPH_NODE);
		}

		DCL_LOG(INFO, "copying odds value to modifiable memory...");

		DclOddsValue node[content->alphabet_size];
		void* copy_result = memcpy(node, src_node, sizeof(DclOddsValue) * content->alphabet_size);

		if (copy_result == NULL) {
			DCL_LOG(ERR, "modifiable odds value NULL");
			return dcl_err_throw_null(DCL_ERR_ARG_NULL_NODE);
		}

		DCL_LOG(INFO, "generating required dependence sentences...");

		error = __gen_required(content, &dep_sentences, sentences, node);

		if (error != C_OK) {
			UC_LOG_BUFFER(logs, format, "error generating required dependence sentences: %d", 10);
			uc_log_format(logs, sizeof(logs), format, error);
			DCL_LOG(ERR, logs);

			uc_linked_list_free(&dep_sentences);
			return error;
		}

		DCL_LOG(INFO, "generating node entries...");

		OddsValueEntry node_entries[content->alphabet_size];
		__odds_value_entries(node_entries, node, content->alphabet_size);

		DCL_LOG(INFO, "sorting node entries...");

		UcArray node_array;
		__array_init_odds_value_entry(&node_array, node_entries, content->alphabet_size);
		uc_array_quick_sort(&node_array, UC_DESC, 0, content->alphabet_size);

		DCL_LOG(INFO, "generating dependence sentences by rand factor...");

		error = __gen_rand_factor(content, &dep_sentences, sentences, node_entries, gen_input->min_dep_sentences);

		if (error != C_OK) {
			UC_LOG_BUFFER(logs, format, "error generating dependence sentences by rand factor: %d", 10);
			uc_log_format(logs, sizeof(logs), format, error);
			DCL_LOG(ERR, logs);

			uc_linked_list_free(&dep_sentences);
			return error;
		}
	}

	DCL_LOG(INFO, "generating results...");

	error = __gen_result(content, dcl_sentences_result, target_key, &dep_sentences);

	DCL_LOG(INFO, "clearing temporary memory after generating results...");

	uc_linked_list_free(&dep_sentences);

	if (error != C_OK) {
		UC_LOG_BUFFER(logs, format, "error generating results: %d", 10);
		uc_log_format(logs, sizeof(logs), format, error);
		DCL_LOG(ERR, logs);

		return error;
	}

	return C_OK;
}

c_err __gen_required(const DclContent* content, UcLinkedList* dep_sentences, const DclSentences* sentences, DclOddsValue* node) {
	for (int i = 0; i < content->alphabet_size;) {
		DclOddsValue* odds_value = &node[i];

		if (odds_value == NULL) {
			DCL_LOG(ERR, "odds value NULL");
			return dcl_err_throw_null(DCL_ERR_ARG_NULL_ODDS_VALUE);
		}

		if (odds_value->required > 0) {
			UC_LOG_BUFFER(logs1, format1, "odds value is required (%d times)", 10);
			uc_log_format(logs1, sizeof(logs1), format1, odds_value->required);
			DCL_LOG(INFO, logs1);

			const char* sentence = sentences->array[i];

			if (sentence == NULL) {
				DCL_LOG(ERR, "Sentence NULL");
				return dcl_err_throw_null(DCL_ERR_ARG_NULL_ALPHABET_SENTENCE);
			}

			UC_LOG_BUFFER(logs2, format2, "generating required dependence sentence '%s'...", strlen(sentence));
			uc_log_format(logs2, sizeof(logs2), format2, sentence);
			DCL_LOG(INFO, logs2);

			c_err error = uc_linked_list_add_last(dep_sentences, (void*) sentence);

			if (error != C_OK) {
				UC_LOG_BUFFER(logs, format, "error generating required dependence sentence: %d", 10);
				uc_log_format(logs, sizeof(logs), format, error);
				DCL_LOG(ERR, logs);

				return error;
			}

			odds_value->required -= 1;
			odds_value->factor -= 1;

			if (odds_value->required > 0) {
				continue;
			}
		}

		++i;
	}

	return C_OK;
}

c_err __gen_rand_factor(const DclContent* content, UcLinkedList* dep_sentences, const DclSentences* sentences, const OddsValueEntry* node_entries, int min_dep_sentences) {
	if (dep_sentences->size > min_dep_sentences) {
		DCL_LOG(INFO, "minimum number of sentences generated");
		return C_OK;
	}

	int sum_factor = 0;
	for (int i = 0; i < content->alphabet_size; ++i) {
		const DclOddsValue* odds_value = node_entries[i].value;
		if (odds_value->factor > 0) {
			sum_factor += odds_value->factor;
		}
	}

	UC_LOG_BUFFER(logs1, format1, "sum factor generated: %d", 10);
	uc_log_format(logs1, sizeof(logs1), format1, sum_factor);
	DCL_LOG(INFO, logs1);

	if (sum_factor == 0) {
		DCL_LOG(INFO, "the probability of any dependence sentence being generated is zero");
		return C_OK;
	}

	for (int i = 0; i < content->alphabet_size; ++i) {
		OddsValueEntry node_entry = node_entries[i];
		const DclOddsValue* odds_value = node_entry.value;

		if (odds_value == NULL) {
			DCL_LOG(ERR, "odds value NULL");
			return dcl_err_throw_null(DCL_ERR_ARG_NULL_ODDS_VALUE);
		}

		UC_LOG_BUFFER(logs2, format2, "calculating odds value probabilidade. Factor: %d", 10);
		uc_log_format(logs2, sizeof(logs2), format2, odds_value->factor);
		DCL_LOG(INFO, logs2);

		float percent = odds_value->factor/sum_factor;
		float rand_percent = (rand() % 100) / (float) 100;
		if (rand_percent < percent) {
			UC_LOG_BUFFER(logs3, format3, "dependence sentence index %d generated", 10);
			uc_log_format(logs3, sizeof(logs3), format3, node_entry.index);
			DCL_LOG(INFO, logs3);

			const char* sentence = sentences->array[node_entry.index];

			if (sentence == NULL) {
				DCL_LOG(ERR, "dependence sentence NULL");
				return dcl_err_throw_null(DCL_ERR_ARG_NULL_ALPHABET_SENTENCE);
			}

			UC_LOG_BUFFER(logs4, format4, "generating sentence '%s'...", strlen(sentence));
			uc_log_format(logs4, sizeof(logs4), format4, sentence);
			DCL_LOG(INFO, logs4);

			c_err error = uc_linked_list_add_last(dep_sentences, (void*) sentence);

			if (error != C_OK) {
				UC_LOG_BUFFER(logs, format, "error generating sentence: %d", 10);
				uc_log_format(logs, sizeof(logs), format, error);
				DCL_LOG(ERR, logs);

				return error;
			}

			if (dep_sentences->size > min_dep_sentences) {
				DCL_LOG(INFO, "minimum number of sentences generated");
				return C_OK;
			}
		}
	}

	return C_OK;
}

c_err __gen_result(const DclContent* content, UcHashMap* dcl_sentences_result, const char* target_key, const UcLinkedList* dep_sentences) {
	DCL_LOG(INFO, "allocating result sentences memory...");

	DclSentences* store_sentences = (DclSentences*) malloc(sizeof(DclSentences));

	if (store_sentences == NULL) {
		DCL_LOG(ERR, "error allocating result sentences memory");
		return dcl_err_throw_alloc(DCL_ERR_ARG_ALLOC_SENTENCES);
	}

	store_sentences->size = 0;
	store_sentences->array = (char**) malloc(sizeof(char*) * dep_sentences->size);

	if (store_sentences->array == NULL) {
		DCL_LOG(ERR, "error allocating result sentences data memory");

		free(store_sentences);
		return dcl_err_throw_alloc(DCL_ERR_ARG_ALLOC_SENTENCES);
	}

	for (int i = 0; i < dep_sentences->size; ++i) {
		store_sentences->array[i] = NULL;
	}

	int index = 0;
	UcLinkedListElement* it;
	UC_LINKED_LIST_FOR_EACH(it, dep_sentences) {
		DCL_LOG(INFO, "storing generated sentence...");

		if (it->value == NULL) {
			DCL_LOG(ERR, "generated sentence is NULL");
			return dcl_err_throw_null(DCL_ERR_ARG_NULL_RESULT_SENTENCE);
		}

		char* sentence = _strdup((const char*) it->value);

		if (sentence == NULL) {
			DCL_LOG(ERR, "error allocating sentence");

			dcl_sentences_free(store_sentences);
			return dcl_err_throw_alloc(DCL_ERR_ARG_ALLOC_RESULT_SENTENCE);
		}

		UC_LOG_BUFFER(logs1, format1, "storing sentence '%s': %d/%d", strlen(sentence) + 10 + 10);
		uc_log_format(logs1, sizeof(logs1), format1, sentence, index, dep_sentences->size);
		DCL_LOG(INFO, logs1);

		store_sentences->array[index++] = sentence;
	}

	DCL_LOG(INFO, "checking inicial result memory...");

	DclSentences* stored_value = (DclSentences*) uc_hash_map_get(dcl_sentences_result, target_key);

	if (stored_value != NULL) {
		DCL_LOG(INFO, "clearing inicial result memory...");
		dcl_sentences_free(stored_value);
		uc_hash_map_remove(dcl_sentences_result, target_key);
	}

	char* store_target_key = _strdup(target_key);

	if (store_target_key == NULL) {
		DCL_LOG(ERR, "error allocating target key");

		dcl_sentences_free(store_sentences);
		return dcl_err_throw_alloc(DCL_ERR_ARG_ALLOC_RESULT_KEY);
	}

	UC_LOG_BUFFER(logs2, format2, "storing generated sentences of target key '%s'...", strlen(store_target_key));
	uc_log_format(logs2, sizeof(logs2), format2, store_target_key);
	DCL_LOG(INFO, logs2);

	c_err error = uc_hash_map_insert(dcl_sentences_result, store_target_key, store_sentences);

	if (error != C_OK) {
		UC_LOG_BUFFER(logs, format, "error storing generated sentences of target key", 10);
		uc_log_format(logs, sizeof(logs), format, error);
		DCL_LOG(ERR, logs);

		free(store_target_key);
		dcl_sentences_free(store_sentences);
		return error;
	}

	return C_OK;
}

// entries

void __string_entries(StringEntry* entries, const char** data, int size) {
	for (int i = 0; i < size; ++i) {
		entries[i].value = data[i];
		entries[i].index = i;
	}
}

void __odds_value_entries(OddsValueEntry* entries, const DclOddsValue* data, int size) {
	for (int i = 0; i < size; ++i) {
		entries[i].value = &data[i];
		entries[i].index = i;
	}
}

int __array_cmp_by_idx_string_entry(void* data1, int idx1, void* data2, int idx2);
void __array_swp_by_idx_string_entry(void* data1, int idx1, void* data2, int idx2);
void __array_init_string_entry(UcArray* array, const StringEntry* data, int size) {
	array->data = (void*) data;
	array->size = size;
	array->element_size = sizeof(StringEntry);
	array->cmp_by_idx = __array_cmp_by_idx_string_entry;
	array->swp_by_idx = __array_swp_by_idx_string_entry;
}

int __array_cmp_by_idx_string_entry(void* data1, int idx1, void* data2, int idx2) {
	StringEntry* entries1 = (StringEntry*) data1;
	StringEntry* entries2 = (StringEntry*) data2;
	return strcmp(entries1->value, entries2->value);
}

void __array_swp_by_idx_string_entry(void* data1, int idx1, void* data2, int idx2) {
	StringEntry* entries1 = (StringEntry*) data1;
	StringEntry* entries2 = (StringEntry*) data2;
	StringEntry aux = entries1[idx1];
	entries1[idx1] = entries2[idx2];
	entries2[idx2] = aux;
}

int __array_cmp_by_idx_odds_value_entry(void* data1, int idx1, void* data2, int idx2);
void __array_swp_by_idx_odds_value_entry(void* data1, int idx1, void* data2, int idx2);
void __array_init_odds_value_entry(UcArray* array, const OddsValueEntry* data, int size) {
	array->data = (void*) data;
	array->size = size;
	array->element_size = sizeof(DclOddsValue);
	array->cmp_by_idx = __array_cmp_by_idx_odds_value_entry;
	array->swp_by_idx = __array_swp_by_idx_odds_value_entry;
}

int __array_cmp_by_idx_odds_value_entry(void* data1, int idx1, void* data2, int idx2) {
	OddsValueEntry* array1 = (OddsValueEntry*) data1;
	const DclOddsValue* value1 = array1[idx1].value;

	OddsValueEntry* array2 = (OddsValueEntry*) data2;
	const DclOddsValue* value2 = array2[idx2].value;

	return value1->factor < value2->factor ? -1 : 1;
}

void __array_swp_by_idx_odds_value_entry(void* data1, int idx1, void* data2, int idx2) {
	OddsValueEntry* array1 = (OddsValueEntry*) data1;
	OddsValueEntry* array2 = (OddsValueEntry*) data2;
	OddsValueEntry aux = array1[idx1];
	array1[idx1] = array2[idx2];
	array2[idx2] = aux;
}
