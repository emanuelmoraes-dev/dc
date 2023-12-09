#ifndef UC_ERRORS_H_INCLUDED
#define UC_ERRORS_H_INCLUDED

#include "uc/errors/base.h"

size_t uc_err_strlen(uc_err error);
errno_t uc_err_strcpy_s(uc_err error, char* message, rsize_t size);

#endif
