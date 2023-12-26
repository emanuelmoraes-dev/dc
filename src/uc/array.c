#include "uc/array.h"
#include "uc/fisher_yates.h"
#include <string.h>

#define __ARRAY_CMP_BY_IDX_NUM(type, data1, idx1, data2, idx2) \
	(((type*)(data1))[idx1] < ((type*)(data2))[idx2] ? -1 : 1)
#define __ARRAY_SWP_BY_IDX(type, data1, idx1, data2, idx2, aux_var) \
	aux_var = ((type*)(data1))[idx1];\
	((type*)(data1))[idx1] = ((type*)(data2))[idx2];\
	((type*)(data2))[idx2] = aux_var

#define __DEF_ARRAY_CMP_BY_IDX_NUM(typename, type) \
	int __uc_array_cmp_by_idx_##typename(void* data1, int idx1, void* data2, int idx2) {\
		return __ARRAY_CMP_BY_IDX_NUM(type, data1, idx1, data2, idx2);\
	}
#define __DEF_ARRAY_SWP_BY_IDX(typename, type) \
	void __uc_array_swp_by_idx_##typename(void* data1, int idx1, void* data2, int idx2) {\
		type aux_var;\
		__ARRAY_SWP_BY_IDX(type, data1, idx1, data2, idx2, aux_var);\
	}

#define __ARRAY_INIT(typename, type, array, data, size) \
	array->data = (void*) data;\
	array->size = size;\
	array->element_size = sizeof(type);\
	array->cmp_by_idx = __uc_array_cmp_by_idx_##typename;\
	array->swp_by_idx = __uc_array_swp_by_idx_##typename

int __uc_array_cmp_by_idx_str(void* data1, int idx1, void* data2, int idx2) {
	const char** array1 = (const char**) data1;
	const char** array2 = (const char**) data2;
	const char* str1 = array1[idx1];
	const char* str2 = array2[idx2];
	return strcmp(str1, str2);
}
__DEF_ARRAY_SWP_BY_IDX(str, char*)

__DEF_ARRAY_CMP_BY_IDX_NUM(float, float)
__DEF_ARRAY_SWP_BY_IDX(float, float)

__DEF_ARRAY_CMP_BY_IDX_NUM(double, double)
__DEF_ARRAY_SWP_BY_IDX(double, double)

__DEF_ARRAY_CMP_BY_IDX_NUM(ldouble, long double)
__DEF_ARRAY_SWP_BY_IDX(ldouble, long double)

__DEF_ARRAY_CMP_BY_IDX_NUM(char, char)
__DEF_ARRAY_SWP_BY_IDX(char, char)

__DEF_ARRAY_CMP_BY_IDX_NUM(short, short)
__DEF_ARRAY_SWP_BY_IDX(short, short)

__DEF_ARRAY_CMP_BY_IDX_NUM(int, int)
__DEF_ARRAY_SWP_BY_IDX(int, int)

__DEF_ARRAY_CMP_BY_IDX_NUM(long, long)
__DEF_ARRAY_SWP_BY_IDX(long, long)

__DEF_ARRAY_CMP_BY_IDX_NUM(llong, long long)
__DEF_ARRAY_SWP_BY_IDX(llong, long long)

__DEF_ARRAY_CMP_BY_IDX_NUM(uchar, unsigned char)
__DEF_ARRAY_SWP_BY_IDX(uchar, unsigned char)

__DEF_ARRAY_CMP_BY_IDX_NUM(ushort, unsigned short)
__DEF_ARRAY_SWP_BY_IDX(ushort, unsigned short)

__DEF_ARRAY_CMP_BY_IDX_NUM(uint, unsigned int)
__DEF_ARRAY_SWP_BY_IDX(uint, unsigned int)

__DEF_ARRAY_CMP_BY_IDX_NUM(ulong, unsigned long)
__DEF_ARRAY_SWP_BY_IDX(ulong, unsigned long)

__DEF_ARRAY_CMP_BY_IDX_NUM(ullong, unsigned long long)
__DEF_ARRAY_SWP_BY_IDX(ullong, unsigned long long)


void uc_array_init_str(UcArray* array, borrow char** data, int size) {
	__ARRAY_INIT(str, char*, array, data, size);
}

void uc_array_init_float(UcArray* array, borrow float* data, int size) {
	__ARRAY_INIT(float, float, array, data, size);
}

void uc_array_init_double(UcArray* array, borrow double* data, int size) {
	__ARRAY_INIT(double, double, array, data, size);
}

void uc_array_init_ldouble(UcArray* array, borrow long double* data, int size) {
	__ARRAY_INIT(ldouble, long double, array, data, size);
}

void uc_array_init_char(UcArray* array, borrow char* data, int size) {
	__ARRAY_INIT(char, char, array, data, size);
}

void uc_array_init_short(UcArray* array, borrow short* data, int size) {
	__ARRAY_INIT(short, short, array, data, size);
}

void uc_array_init_int(UcArray* array, borrow int* data, int size) {
	__ARRAY_INIT(int, int, array, data, size);
}

void uc_array_init_long(UcArray* array, borrow long* data, int size) {
	__ARRAY_INIT(long, long, array, data, size);
}

void uc_array_init_llong(UcArray* array, borrow long long* data, int size) {
	__ARRAY_INIT(llong, long long, array, data, size);
}

void uc_array_init_uchar(UcArray* array, borrow unsigned char* data, int size) {
	__ARRAY_INIT(uchar, unsigned char, array, data, size);
}

void uc_array_init_ushort(UcArray* array, borrow unsigned short* data, int size) {
	__ARRAY_INIT(ushort, unsigned short, array, data, size);
}

void uc_array_init_uint(UcArray* array, borrow unsigned int* data, int size) {
	__ARRAY_INIT(uint, unsigned int, array, data, size);
}

void uc_array_init_ulong(UcArray* array, borrow unsigned long* data, int size) {
	__ARRAY_INIT(ulong, unsigned long, array, data, size);
}

void uc_array_init_ullong(UcArray* array, borrow unsigned long long* data, int size) {
	__ARRAY_INIT(ullong, unsigned long long, array, data, size);
}

void uc_array_shuffle(UcArray* array) {
	uc_array_shuffle_fisher_yates(array);
}
