#include "dcl/content.h"
#include "uc/hash_map.h"
#include "uc/linked_list.h"
#include "uc/array.h"
#include "uc/quick_sort.h"
#include "uc/math_util.h"
#include <string.h>
#include <stdlib.h>
#include <limits.h>

c_err __gen_targets(const DclContent* content, borrow UcHashMap* dcl_sentences_result, const DclGenInput* gen_input);
c_err dcl_content_gen(const DclContent* content, borrow UcHashMap* dcl_sentences_result, const DclGenInput* gen_input) {
	return __gen_targets(content, dcl_sentences_result, gen_input);
}

typedef struct string_entry {
	borrow const char* value;
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

c_err __gen_dep(const DclContent* content, borrow UcHashMap* dcl_sentences_result, const DclGenInput* gen_input, const char* target_key, borrow StringEntry* target_sentence);
c_err __gen_targets(const DclContent* content, borrow UcHashMap* dcl_sentences_result, const DclGenInput* gen_input) {
	for (int k = 0; k < gen_input->target_keys_size; ++k) {
		const char* target_key = gen_input->target_keys[k];
		DclSentences* sentences = (DclSentences*) uc_hash_map_get(&content->alphabet, target_key);

		if (sentences == NULL) {
			return DCL_ERR_THROW_NOT_FOUND(DCL_ERR_ARG_NOT_FOUND_ALPHABET_KEY);
		}

		StringEntry sentences_entries[sentences->size];
		__string_entries(sentences_entries, (const char**) sentences->array, sentences->size);

		UcArray sentences_entries_array;
		__array_init_string_entry(&sentences_entries_array, sentences_entries, sentences->size);
		uc_array_shuffle(&sentences_entries_array);
		int sentences_size = MIN(sentences->size, gen_input->target_sentences_size);

		for (int s = 0; s < sentences_size; ++s) {
			c_err error = __gen_dep(content, dcl_sentences_result, gen_input, target_key, &sentences_entries[s]);

			if (error != C_OK) {
				return error;
			}
		}
	}

	return C_OK;
}

c_err __gen_required(const DclContent* content, UcLinkedList* dep_sentences, const char* dep_key, DclOddsValue* node);
c_err __gen_dep(const DclContent* content, borrow UcHashMap* dcl_sentences_result, const DclGenInput* gen_input, const char* target_key, borrow StringEntry* target_sentence) {
	for (int d = 0; d < gen_input->dep_keys_size; ++d) {
		const char* dep_key = gen_input->dep_keys[d];
		const UcHashMap* dep = (UcHashMap*) uc_hash_map_get(&content->odds_graph, target_key);

		if (dep == NULL) {
			return DCL_ERR_THROW_NOT_FOUND(DCL_ERR_ARG_NOT_FOUND_GRAPH_DEP);
		}

		const DclOdds* odds = (DclOdds*) uc_hash_map_get(dep, dep_key);

		if (odds == NULL) {
			return DCL_ERR_THROW_NOT_FOUND(DCL_ERR_ARG_NOT_FOUND_ODDS);
		}

		DclOddsValue* src_node = odds->graph[target_sentence->index];

		if (src_node == NULL) {
			return DCL_ERR_THROW_NOT_FOUND(DCL_ERR_ARG_NOT_FOUND_GRAPH_NODE);
		}

		DclOddsValue node[content->alphabet_size];
		memcpy(node, src_node, sizeof(DclOddsValue) * content->alphabet_size);

		UcLinkedList dep_sentences;
		c_err error = uc_linked_list_init(&dep_sentences);

		if (error != C_OK) {
			return error;
		}

		error = __gen_required(content, &dep_sentences, dep_key, node);

		if (error != C_OK) {
			uc_linked_list_free(&dep_sentences);
			return error;
		}

		OddsValueEntry node_entries[content->alphabet_size];
		__odds_value_entries(node_entries, node, content->alphabet_size);

		UcArray node_array;
		__array_init_odds_value_entry(&node_array, node_entries, content->alphabet_size);
		uc_array_quick_sort(&node_array, UC_DESC, 0, content->alphabet_size);

		// TODO
	}

	return C_OK;
}

c_err __gen_required(const DclContent* content, UcLinkedList* dep_sentences, const char* dep_key, DclOddsValue* node) {
	const DclSentences* sentences = (const DclSentences*) uc_hash_map_get(&content->alphabet, dep_key);

	if (sentences == NULL) {
		return DCL_ERR_THROW_NOT_FOUND(DCL_ERR_ARG_NOT_FOUND_ALPHABET_KEY);
	}

	for (int i = 0; i < content->alphabet_size; ++i) {
		DclOddsValue* odds_value = &node[i];

		if (odds_value->required > 0) {
			const char* sentence = sentences->array[i];
			c_err error = uc_linked_list_add_last(dep_sentences, (void*) sentence);

			if (error != C_OK) {
				return error;
			}

			odds_value->required -= 1;
			odds_value->factor -= 1;
		}
	}

	return C_OK;
}

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
