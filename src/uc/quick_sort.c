#include "uc/quick_sort.h"

void uc_array_quick_sort(UcArray* array, uc_order order, int begin, int size) {
	if (size < 2 || begin < 0 || begin >= size) {
		return;
	}

	if (size > array->size) {
		size = array->size;
	}

	int end = begin + size;
	int pv = (begin + end) / 2;
	array->swp_by_idx(array->data, pv, array->data, end - 1);
	pv = end - 1;

	int i = begin;
	while (i < pv) {
		if (array->cmp_by_idx(array->data, i, array->data, pv) * order > 0) {
			array->swp_by_idx(array->data, pv-1, array->data, pv);
			pv--;

			if (pv - i > 0) {
				array->swp_by_idx(array->data, i, array->data, pv+1);
			}

			continue;
		}

		i++;
	}

	uc_array_quick_sort(array, order, begin, pv - begin);
	uc_array_quick_sort(array, order, pv + 1, end - (pv + 1));
}
