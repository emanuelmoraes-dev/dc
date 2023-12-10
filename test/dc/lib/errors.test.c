#include <stdio.h>
#include "test/dc.test.h"
#include "dc/lib/errors.h"

void __test_dc_lib_errors_alloc();
void __test_dc_lib_errors_index_out();

void test_dc_lib_errors() {
	printf("===== test_dc_lib_errors =====\n");

    __test_dc_lib_errors_alloc();
    __test_dc_lib_errors_index_out();

    printf("----- test_dc_lib_errors -----\n");
}

void __test_dc_lib_errors_alloc() {
	c_err e1 = DC_LIB_ERR_THROW_ALLOC(DC_LIB_ERR_ARG_ALLOC_ALPHABET);
    size_t l1 = dc_lib_err_strlen(e1);

    if (l1 == 31) {
    	printf("Ok(l1)\n");
    } else {
    	printf("Fail(l1): Expected(l1) == 31; Received(l1) == %zu\n", l1);
    }

    char m1[l1 + 1];
    errno_t _error = dc_lib_err_strcpy_s(e1, m1, sizeof(m1));

    if (_error == 0 && strcmp(m1, "Error When Allocating: Alphabet") == 0) {
    	printf("Ok(m1)\n");
    } else if (_error == 0) {
    	printf("Fail(m1): Expected(m1) == 'Error When Allocating: Alphabet'; Received(m1) == '%s'\n", m1);
    } else {
    	printf("Fail(m1): Expected(errno_t) == 0; Received(errno_t) == %d\n", _error);
    }
}

void __test_dc_lib_errors_index_out() {
	c_err e2 = DC_LIB_ERR_THROW_INDEX_OUT(DC_LIB_ERR_ARG_INDEX_OUT_ALPHABET);
    size_t l2 = dc_lib_err_strlen(e2);

    if (l2 == 29) {
    	printf("Ok(l2)\n");
    } else {
    	printf("Fail(l2): Expected(l2) == 29; Received(l2) == %zu\n", l2);
    }

    char m2[l2 + 1];
    errno_t _error = dc_lib_err_strcpy_s(e2, m2, sizeof(m2));

    if (_error == 0 && strcmp(m2, "Index Out Of Bounds: Alphabet") == 0) {
    	printf("Ok(m2)\n");
    } else if (_error == 0) {
    	printf("Fail(m2): Expected(m2) == 'Index Out Of Bounds: Alphabet'; Received(m2) == '%s'\n", m2);
    } else {
    	printf("Fail(m2): Expected(errno_t) == 0; Expected(errno_t) == %d\n", _error);
    }
}
