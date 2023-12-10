#ifndef DC_LIB_ERRORS_H_INCLUDED
#define DC_LIB_ERRORS_H_INCLUDED

#include <string.h>
#include <errno.h>

#include "dc/lib/errors/base.h"
#include "dc/lib/errors/errno.h"
#include "dc/lib/errors/alloc.h"
#include "dc/lib/errors/index_out.h"

size_t dc_lib_err_strlen(c_err error);
errno_t dc_lib_err_strcpy_s(c_err error, char* message, rsize_t size);

#endif
