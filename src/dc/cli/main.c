#include <stdio.h>
#include "dc/lib/errors.h"
#include "dc/lib/content.h"

int main(int argc, const char* argv[]) {
    dc_lib_err e1 = DC_LIB_ERR_THROW_ALLOC(DC_LIB_ERR_ARG_ALLOC_ALPHABET);
    size_t l1 = dc_lib_err_strlen(e1);
    char m1[l1 + 1];
    dc_lib_err_strcpy_s(e1, m1, sizeof(m1));
    printf("(%zu) %s\n", l1, m1);

    dc_lib_err e2 = DC_LIB_ERR_THROW_INDEX_OUT(DC_LIB_ERR_ARG_INDEX_OUT_ALPHABET);
    size_t l2 = dc_lib_err_strlen(e2);
    char m2[l2 + 1];
    dc_lib_err_strcpy_s(e2, m2, sizeof(m2));
    printf("(%zu) %s\n", l2, m2);
    return 0;
}
