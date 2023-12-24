#include "dcl/content.h"
#include "uc/hash_map.h"
#include "uc/quick_sort.h"
#include <stdlib.h>

typedef struct float_entry {
	float value;
	int index;
} FloatEntry;

c_err __float_entries(borrow FloatEntry** entries, float* data, int size);
void __list_init_float_entry(UcList* list, FloatEntry* data, int size);

c_err dcl_content_gen(const DclContent* content, borrow UcHashMap* dcl_sentences_by_keys1, DclGenInput* gen_input) {
	return C_OK;
}

c_err __float_entries(borrow FloatEntry** entries, float* data, int size) {
	*entries = (FloatEntry*) malloc(sizeof(FloatEntry) * size);

	if (*entries == NULL) {
		return DCL_ERR_THROW_ALLOC(DCL_ERR_ARG_ALLOC_CONTENT_GEN);
	}

	for (int i = 0; i < size; ++i) {
		(*entries)[i].value = data[i];
		(*entries)[i].index = i;
	}

	return C_OK;
}

int __list_cmp_by_idx_float_entry(void* data, int idx1, int idx2);
void __list_swp_by_idx_float_entry(void* data, int idx1, int idx2);

void __list_init_float_entry(UcList* list, FloatEntry* data, int size) {
	list->data = (void*) data;
	list->size = size;
	list->cmp_by_idx = __list_cmp_by_idx_float_entry;
	list->swp_by_idx = __list_swp_by_idx_float_entry;
}

int __list_cmp_by_idx_float_entry(void* data, int idx1, int idx2) {
	FloatEntry* entries = (FloatEntry*) data;
	return entries[idx1].value < entries[idx2].value ? -1 : 0;
}

void __list_swp_by_idx_float_entry(void* data, int idx1, int idx2) {
	FloatEntry* entries = (FloatEntry*) data;
	FloatEntry aux = entries[idx1];
	entries[idx1] = entries[idx2];
	entries[idx2] = aux;
}
