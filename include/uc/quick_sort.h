#ifndef _UC_QUICK_SORT_H_INCLUDED_
#define _UC_QUICK_SORT_H_INCLUDED_

#include "uc/array.h"

#define UC_ASC (1)
#define UC_DESC (-1)

typedef int uc_order;

void uc_array_quick_sort(UcArray* array, uc_order order, int idx_begin, int size);

#endif
