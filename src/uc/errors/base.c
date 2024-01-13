#include "uc/errors/base.h"

int uc_err_get_arg(c_err error) {
	return (error - __UC_ERR_BASE) % (__uc_err_get_id(error) * __UC_ERR_FACTOR);
}

int __uc_err_get_id(c_err error) {
	return (error - __UC_ERR_BASE) / __UC_ERR_FACTOR;
}

c_err __uc_err_throw(int error_id, int arg) {
	return error_id * __UC_ERR_FACTOR + arg + __UC_ERR_BASE;
}

c_err __uc_err_is(int error_id, c_err error) {
	return __uc_err_get_id(error) == error_id;
}

size_t __uc_err_strlen(int arg, size_t error_message_len, size_t (*arg_strlen)(int)) {
	size_t arg_len = arg_strlen(arg);
	return error_message_len + arg_len + 2;
}

errno_t __uc_err_strcpy_s(int arg, const char* error_message, errno_t (*arg_strcat_s)(int, char*, rsize_t), char* message, rsize_t size) {
	errno_t error = strcpy_s(message, size, error_message);

	if (error != 0) {
		return error;
	}

	error = strcat_s(message, size, ": ");

	if (error != 0) {
		return error;
	}

	return arg_strcat_s(arg, message, size);
}
