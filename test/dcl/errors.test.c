#include <stdio.h>
#include "test/dcl.test.h"
#include "dcl/errors.h"

void __test_dcl_errors_alloc();
void __test_dcl_errors_index_out();

void test_dcl_errors() {
	printf("===== test_dcl_errors =====\n");

    __test_dcl_errors_alloc();
    __test_dcl_errors_index_out();

    printf("----- test_dcl_errors -----\n");
}

void __test_dcl_errors_alloc() {
	c_err e1 = dcl_err_throw_alloc(DCL_ERR_ARG_ALLOC_ODDS);
    size_t l1 = dcl_err_strlen(e1);

    if (l1 == 27) {
    	printf("Ok(l1)\n");
    } else {
    	printf("Fail(l1): Expected(l1) == 27; Received(l1) == %zu\n", l1);
    }

    char m1[l1 + 1];
    errno_t _error = dcl_err_strcpy_s(e1, m1, sizeof(m1));

    if (_error == 0 && strcmp(m1, "Error When Allocating: Odds") == 0) {
    	printf("Ok(m1)\n");
    } else if (_error == 0) {
    	printf("Fail(m1): Expected(m1) == 'Error When Allocating: Odds'; Received(m1) == '%s'\n", m1);
    } else {
    	printf("Fail(m1): Expected(errno_t) == 0; Received(errno_t) == %d\n", _error);
    }
}

void __test_dcl_errors_index_out() {
	c_err e2 = dcl_err_throw_index_out(DCL_ERR_ARG_INDEX_OUT_ALPHABET);
    size_t l2 = dcl_err_strlen(e2);

    if (l2 == 34) {
    	printf("Ok(l2)\n");
    } else {
    	printf("Fail(l2): Expected(l2) == 34; Received(l2) == %zu\n", l2);
    }

    char m2[l2 + 1];
    errno_t _error = dcl_err_strcpy_s(e2, m2, sizeof(m2));

    if (_error == 0 && strcmp(m2, "Index Out Of Bounds: Alphabet Size") == 0) {
    	printf("Ok(m2)\n");
    } else if (_error == 0) {
    	printf("Fail(m2): Expected(m2) == 'Index Out Of Bounds: Alphabet Size'; Received(m2) == '%s'\n", m2);
    } else {
    	printf("Fail(m2): Expected(errno_t) == 0; Expected(errno_t) == %d\n", _error);
    }
}
