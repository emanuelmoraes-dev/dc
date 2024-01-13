#ifndef DCL_ERRORS_BASE_H_INCLUDED
#define DCL_ERRORS_BASE_H_INCLUDED

#include <string.h>
#include <errno.h>
#include "uc/errors/base.h"

#define __DCL_ERR_FACTOR (100)
#define __DCL_ERR_BASE (100)

#define DCL_ERR_DEF(name) \
	c_err dcl_err_throw_##name(int arg);\
	bool dcl_err_is_##name(c_err error);

#define DCL_ERR_IMPL(name, id) \
	c_err dcl_err_throw_##name(int arg) {\
		return __dcl_err_throw(id, arg);\
	}\
	bool dcl_err_is_##name(c_err error) {\
		return __dcl_err_is(id, error);\
	}

int dcl_err_get_arg(c_err error);

int __dcl_err_get_id(c_err error);
c_err __dcl_err_throw(int error_id, int arg);
c_err __dcl_err_is(int error_id, c_err error);
size_t __dcl_err_strlen(int arg, size_t error_message_len, size_t (*arg_strlen)(int));
errno_t __dcl_err_strcpy_s(int arg, const char* error_message, errno_t (*arg_strcat_s)(int, char*, rsize_t), char* message, rsize_t size);

#endif
