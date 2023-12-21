#ifndef DCL_ERRORS_H_INCLUDED
#define DCL_ERRORS_H_INCLUDED

#include <string.h>
#include <errno.h>
#include "uc/errors.h"

#include "dcl/errors/base.h"
#include "dcl/errors/errno.h"
#include "dcl/errors/alloc.h"
#include "dcl/errors/index_out.h"
#include "dcl/errors/null.h"
#include "dcl/errors/not_found.h"

size_t dcl_err_strlen(c_err error);
errno_t dcl_err_strcpy_s(c_err error, char* message, rsize_t size);

#endif
