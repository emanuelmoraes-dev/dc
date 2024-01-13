#ifndef _UC_ERRORS_BASE_H_INCLUDED_
#define _UC_ERRORS_BASE_H_INCLUDED_

#include <string.h>
#include <errno.h>
#include <stdbool.h>

typedef int c_err;

#define C_OK (0)

#define __UC_ERR_FACTOR (100)
#define __UC_ERR_BASE (10000)

#define UC_ERR_DEF(name) \
	c_err uc_err_throw_##name(int arg);\
	bool uc_err_is_##name(c_err error);

#define UC_ERR_IMPL(name, id) \
	c_err uc_err_throw_##name(int arg) {\
		return __uc_err_throw(id, arg);\
	}\
	bool uc_err_is_##name(c_err error) {\
		return __uc_err_is(id, error);\
	}

int uc_err_get_arg(c_err error);

int __uc_err_get_id(c_err error);
c_err __uc_err_throw(int error_id, int arg);
c_err __uc_err_is(int error_id, c_err error);
size_t __uc_err_strlen(int arg, size_t error_message_len, size_t (*arg_strlen)(int));
errno_t __uc_err_strcpy_s(int arg, const char* error_message, errno_t (*arg_strcat_s)(int, char*, rsize_t), char* message, rsize_t size);

#endif
