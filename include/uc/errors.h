#ifndef UC_ERRORS_H_INCLUDED
#define UC_ERRORS_H_INCLUDED

#include "uc/errors/base.h"
#include "uc/errors/alloc.h"
#include "uc/errors/realloc.h"
#include "uc/errors/not_found.h"
#include "uc/errors/empty.h"

size_t uc_err_strlen(c_err error);
errno_t uc_err_strcpy_s(c_err error, char* message, rsize_t size);

#endif
