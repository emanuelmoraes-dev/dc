#ifndef UC_ARRAY_H_INCLUDED
#define UC_ARRAY_H_INCLUDED

#include "uc/tags.h"
#include <stdlib.h>

typedef struct uc_array {
	borrow void* data;
	int size;
	size_t element_size;
	int (*cmp_by_idx)(void*,int, void*,int);
	void (*swp_by_idx)(void*,int, void*,int);
} UcArray;

void uc_array_init_str(UcArray* array, borrow char** data, int size);
void uc_array_init_float(UcArray* array, borrow float* data, int size);
void uc_array_init_double(UcArray* array, borrow double* data, int size);
void uc_array_init_ldouble(UcArray* array, borrow long double* data, int size);

void uc_array_init_char(UcArray* array, borrow char* data, int size);
void uc_array_init_short(UcArray* array, borrow short* data, int size);
void uc_array_init_int(UcArray* array, borrow int* data, int size);
void uc_array_init_long(UcArray* array, borrow long* data, int size);
void uc_array_init_llong(UcArray* array, borrow long long* data, int size);

void uc_array_init_uchar(UcArray* array, borrow unsigned char* data, int size);
void uc_array_init_ushort(UcArray* array, borrow unsigned short* data, int size);
void uc_array_init_uint(UcArray* array, borrow unsigned int* data, int size);
void uc_array_init_ulong(UcArray* array, borrow unsigned long* data, int size);
void uc_array_init_ullong(UcArray* array, borrow unsigned long long* data, int size);

void uc_array_shuffle(UcArray* array);

#endif
