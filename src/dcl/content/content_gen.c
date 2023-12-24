#include "dcl/content.h"
#include "uc/hash_map.h"
#include "uc/quick_sort.h"
#include <stdlib.h>

typedef struct float_entry {
	float value;
	int index;
} FloatEntry;

c_err __float_entries(borrow FloatEntry** entries, float* data, int size);
void __array_init_float_entry(UcArray* array, FloatEntry* data, int size);

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

int __array_cmp_by_idx_float_entry(void* data1, int idx1, void* data2, int idx2);
void __array_swp_by_idx_float_entry(void* data1, int idx1, void* data2, int idx2);

void __array_init_float_entry(UcArray* array, FloatEntry* data, int size) {
	array->data = (void*) data;
	array->size = size;
	array->cmp_by_idx = __array_cmp_by_idx_float_entry;
	array->swp_by_idx = __array_swp_by_idx_float_entry;
}

int __array_cmp_by_idx_float_entry(void* data1, int idx1, void* data2, int idx2) {
	FloatEntry* entries1 = (FloatEntry*) data1;
	FloatEntry* entries2 = (FloatEntry*) data2;
	return entries1[idx1].value < entries2[idx2].value ? -1 : 0;
}

void __array_swp_by_idx_float_entry(void* data1, int idx1, void* data2, int idx2) {
	FloatEntry* entries1 = (FloatEntry*) data1;
	FloatEntry* entries2 = (FloatEntry*) data2;
	FloatEntry aux = entries1[idx1];
	entries1[idx1] = entries2[idx2];
	entries2[idx2] = aux;
}
