#include "uc/errors.h"

size_t uc_err_strlen(c_err error) {
	if (UC_ERR_IS_ALLOC(error)) {
		return uc_err_strlen_alloc(UC_ERR_GET_ARG(error));
	}
	if (UC_ERR_IS_REALLOC(error)) {
		return uc_err_strlen_realloc(UC_ERR_GET_ARG(error));
	}
	if (UC_ERR_IS_NOT_FOUND(error)) {
		return uc_err_strlen_not_found(UC_ERR_GET_ARG(error));
	}
	if (UC_ERR_IS_EMPTY(error)) {
		return uc_err_strlen_empty(UC_ERR_GET_ARG(error));
	}
	return strlen("Unexpected");
}

errno_t uc_err_strcpy_s(c_err error, char* message, rsize_t size) {
	if (UC_ERR_IS_ALLOC(error)) {
		return uc_err_strcpy_s(UC_ERR_GET_ARG(error), message, size);
	}
	if (UC_ERR_IS_REALLOC(error)) {
		return uc_err_strcpy_s_realloc(UC_ERR_GET_ARG(error), message, size);
	}
	if (UC_ERR_IS_NOT_FOUND(error)) {
		return uc_err_strcpy_s_not_found(UC_ERR_GET_ARG(error), message, size);
	}
	if (UC_ERR_IS_EMPTY(error)) {
		return uc_err_strcpy_s_empty(UC_ERR_GET_ARG(error), message, size);
	}
	return strcpy_s(message, size, "Unexpected");
}
