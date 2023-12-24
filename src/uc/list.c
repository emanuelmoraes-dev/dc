#include "uc/list.h"
#include <string.h>

#define __LIST_CMP_BY_IDX_NUM(type, data, idx1, idx2) (((type*)(data))[idx1] < ((type*)(data))[idx2] ? -1 : 1)
#define __LIST_SWP_BY_IDX(type, data, idx1, idx2, aux_var) \
	aux_var = ((type*)(data))[idx1];\
	((type*)(data))[idx1] = ((type*)(data))[idx2];\
	((type*)(data))[idx2] = aux_var

#define __DEF_LIST_CMP_BY_IDX_NUM(typename, type) \
	int __uc_list_cmp_by_idx_##typename(void* data, int idx1, int idx2) {\
		return __LIST_CMP_BY_IDX_NUM(type, data, idx1, idx2);\
	}

#define __DEF_LIST_SWP_BY_IDX(typename, type) \
	void __uc_list_swp_by_idx_##typename(void* data, int idx1, int idx2) {\
		type aux_var;\
		__LIST_SWP_BY_IDX(type, data, idx1, idx2, aux_var);\
	}

#define __LIST_INIT(typename, list, data, size) \
	list->data = (void*) data;\
	list->size = size;\
	list->cmp_by_idx = __uc_list_cmp_by_idx_##typename;\
	list->swp_by_idx = __uc_list_swp_by_idx_##typename

int __uc_list_cmp_by_idx_str(void* data, int idx1, int idx2) {
	const char** array = (const char**) data;
	const char* str1 = array[idx1];
	const char* str2 = array[idx2];
	return strcmp(str1, str2);
}
__DEF_LIST_SWP_BY_IDX(str, char*)

__DEF_LIST_CMP_BY_IDX_NUM(float, float)
__DEF_LIST_SWP_BY_IDX(float, float)

__DEF_LIST_CMP_BY_IDX_NUM(double, double)
__DEF_LIST_SWP_BY_IDX(double, double)

__DEF_LIST_CMP_BY_IDX_NUM(ldouble, long double)
__DEF_LIST_SWP_BY_IDX(ldouble, long double)

__DEF_LIST_CMP_BY_IDX_NUM(char, char)
__DEF_LIST_SWP_BY_IDX(char, char)

__DEF_LIST_CMP_BY_IDX_NUM(short, short)
__DEF_LIST_SWP_BY_IDX(short, short)

__DEF_LIST_CMP_BY_IDX_NUM(int, int)
__DEF_LIST_SWP_BY_IDX(int, int)

__DEF_LIST_CMP_BY_IDX_NUM(long, long)
__DEF_LIST_SWP_BY_IDX(long, long)

__DEF_LIST_CMP_BY_IDX_NUM(llong, long long)
__DEF_LIST_SWP_BY_IDX(llong, long long)

__DEF_LIST_CMP_BY_IDX_NUM(uchar, unsigned char)
__DEF_LIST_SWP_BY_IDX(uchar, unsigned char)

__DEF_LIST_CMP_BY_IDX_NUM(ushort, unsigned short)
__DEF_LIST_SWP_BY_IDX(ushort, unsigned short)

__DEF_LIST_CMP_BY_IDX_NUM(uint, unsigned int)
__DEF_LIST_SWP_BY_IDX(uint, unsigned int)

__DEF_LIST_CMP_BY_IDX_NUM(ulong, unsigned long)
__DEF_LIST_SWP_BY_IDX(ulong, unsigned long)

__DEF_LIST_CMP_BY_IDX_NUM(ullong, unsigned long long)
__DEF_LIST_SWP_BY_IDX(ullong, unsigned long long)


void uc_list_init_str(UcList* list, borrow char** data, int size) {
	__LIST_INIT(str, list, data, size);
}

void uc_list_init_float(UcList* list, borrow float* data, int size) {
	__LIST_INIT(float, list, data, size);
}

void uc_list_init_double(UcList* list, borrow double* data, int size) {
	__LIST_INIT(double, list, data, size);
}

void uc_list_init_ldouble(UcList* list, borrow long double* data, int size) {
	__LIST_INIT(ldouble, list, data, size);
}

void uc_list_init_char(UcList* list, borrow char* data, int size) {
	__LIST_INIT(char, list, data, size);
}

void uc_list_init_short(UcList* list, borrow short* data, int size) {
	__LIST_INIT(short, list, data, size);
}

void uc_list_init_int(UcList* list, borrow int* data, int size) {
	__LIST_INIT(int, list, data, size);
}

void uc_list_init_long(UcList* list, borrow long* data, int size) {
	__LIST_INIT(long, list, data, size);
}

void uc_list_init_llong(UcList* list, borrow long long* data, int size) {
	__LIST_INIT(llong, list, data, size);
}

void uc_list_init_uchar(UcList* list, borrow unsigned char* data, int size) {
	__LIST_INIT(uchar, list, data, size);
}

void uc_list_init_ushort(UcList* list, borrow unsigned short* data, int size) {
	__LIST_INIT(ushort, list, data, size);
}

void uc_list_init_uint(UcList* list, borrow unsigned int* data, int size) {
	__LIST_INIT(uint, list, data, size);
}

void uc_list_init_ulong(UcList* list, borrow unsigned long* data, int size) {
	__LIST_INIT(ulong, list, data, size);
}

void uc_list_init_ullong(UcList* list, borrow unsigned long long* data, int size) {
	__LIST_INIT(ullong, list, data, size);
}
