#ifndef UC_LIST_H_INCLUDED
#define UC_LIST_H_INCLUDED

#include "uc/tags.h"

typedef struct uc_list {
	borrow void* data;
	int size;
	int (*cmp_by_idx)(void*,int,int);
	void (*swp_by_idx)(void*,int,int);
} UcList;

void uc_list_init_str(UcList* list, borrow char** data, int size);
void uc_list_init_float(UcList* list, borrow float* data, int size);
void uc_list_init_double(UcList* list, borrow double* data, int size);
void uc_list_init_ldouble(UcList* list, borrow long double* data, int size);

void uc_list_init_char(UcList* list, borrow char* data, int size);
void uc_list_init_short(UcList* list, borrow short* data, int size);
void uc_list_init_int(UcList* list, borrow int* data, int size);
void uc_list_init_long(UcList* list, borrow long* data, int size);
void uc_list_init_llong(UcList* list, borrow long long* data, int size);

void uc_list_init_uchar(UcList* list, borrow unsigned char* data, int size);
void uc_list_init_ushort(UcList* list, borrow unsigned short* data, int size);
void uc_list_init_uint(UcList* list, borrow unsigned int* data, int size);
void uc_list_init_ulong(UcList* list, borrow unsigned long* data, int size);
void uc_list_init_ullong(UcList* list, borrow unsigned long long* data, int size);

#endif
