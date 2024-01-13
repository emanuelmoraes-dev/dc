#include "uc/errors.h"

size_t uc_err_strlen(c_err error) {
	if (uc_err_is_alloc(error)) {
		return uc_err_strlen_alloc(uc_err_get_arg(error));
	}
	if (uc_err_is_realloc(error)) {
		return uc_err_strlen_realloc(uc_err_get_arg(error));
	}
	if (uc_err_is_not_found(error)) {
		return uc_err_strlen_not_found(uc_err_get_arg(error));
	}
	if (uc_err_is_empty(error)) {
		return uc_err_strlen_empty(uc_err_get_arg(error));
	}
	if (uc_err_is_overflow(error)) {
		return uc_err_strlen_overflow(uc_err_get_arg(error));
	}
	return strlen("Unexpected");
}

errno_t uc_err_strcpy_s(c_err error, char* message, rsize_t size) {
	if (uc_err_is_alloc(error)) {
		return uc_err_strcpy_s(uc_err_get_arg(error), message, size);
	}
	if (uc_err_is_realloc(error)) {
		return uc_err_strcpy_s_realloc(uc_err_get_arg(error), message, size);
	}
	if (uc_err_is_not_found(error)) {
		return uc_err_strcpy_s_not_found(uc_err_get_arg(error), message, size);
	}
	if (uc_err_is_empty(error)) {
		return uc_err_strcpy_s_empty(uc_err_get_arg(error), message, size);
	}
	if (uc_err_is_overflow(error)) {
		return uc_err_strcpy_s_overflow(uc_err_get_arg(error), message, size);
	}
	return strcpy_s(message, size, "Unexpected");
}
