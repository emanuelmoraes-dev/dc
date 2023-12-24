#ifndef UC_LIST_H_INCLUDED
#define UC_LIST_H_INCLUDED

#include "uc/tags.h"

typedef struct list {
	borrow void* data;
	int size;
	int (*cmp_by_idx)(void*,int,int);
	void (*swp_by_idx)(void*,int,int);
} List;

void list_init_str(List* list, borrow char** data, int size);
void list_init_float(List* list, borrow float* data, int size);
void list_init_double(List* list, borrow double* data, int size);
void list_init_ldouble(List* list, borrow long double* data, int size);

void list_init_char(List* list, borrow char* data, int size);
void list_init_short(List* list, borrow short* data, int size);
void list_init_int(List* list, borrow int* data, int size);
void list_init_long(List* list, borrow long* data, int size);
void list_init_llong(List* list, borrow long long* data, int size);

void list_init_uchar(List* list, borrow unsigned char* data, int size);
void list_init_ushort(List* list, borrow unsigned short* data, int size);
void list_init_uint(List* list, borrow unsigned int* data, int size);
void list_init_ulong(List* list, borrow unsigned long* data, int size);
void list_init_ullong(List* list, borrow unsigned long long* data, int size);

#endif
