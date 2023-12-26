#include "uc/fisher_yates.h"

void uc_array_shuffle_fisher_yates(UcArray* array) {
	for (int i = array->size; i > 0; i--) {
        int j = rand() % (i + 1);
        array->swp_by_idx(array->data, i, array->data, j);
    }
}
