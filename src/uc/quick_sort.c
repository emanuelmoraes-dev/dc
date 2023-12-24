#include "uc/quick_sort.h"

void list_quick_sort(List* list, int begin, int size) {
	if (size < 2 || begin < 0 || begin >= size) {
		return;
	}

	if (size > list->size) {
		size = list->size;
	}

	int end = begin + size;
	int pv = (begin + end) / 2;
	list->swp_by_idx(list->data, pv, end - 1);
	pv = end - 1;

	int i = begin;
	while (i < pv) {
		if (list->cmp_by_idx(list->data, i, pv) > 0) {
			list->swp_by_idx(list->data, pv-1, pv);
			pv--;

			if (pv - i > 0) {
				list->swp_by_idx(list->data, i, pv+1);
			}

			continue;
		}

		i++;
	}

	list_quick_sort(list, begin, pv - begin);
	list_quick_sort(list, pv + 1, end - (pv + 1));
}
