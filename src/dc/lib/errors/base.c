#include "dc/lib/errors/base.h"

size_t __dc_lib_err_strlen(int arg, size_t error_message_len, size_t (*arg_strlen)(int)) {
	size_t arg_len = arg_strlen(arg);
	return error_message_len + arg_len + 2;
}

errno_t __dc_lib_err_strcpy_s(int arg, const char* error_message, errno_t (*arg_strcat_s)(int, char*, rsize_t), char* message, rsize_t size) {
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
