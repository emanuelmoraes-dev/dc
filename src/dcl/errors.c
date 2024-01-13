#include "dcl/errors.h"

size_t dcl_err_strlen(c_err error) {
	if (dcl_err_is_alloc(error)) {
		return dcl_err_strlen_alloc(dcl_err_get_arg(error));
	}
	if (dcl_err_is_index_out(error)) {
		return dcl_err_strlen_index_out(dcl_err_get_arg(error));
	}
	if (dcl_err_is_null(error)) {
		return dcl_err_strlen_null(dcl_err_get_arg(error));
	}
	if (dcl_err_is_not_found(error)) {
		return dcl_err_strlen_not_found(dcl_err_get_arg(error));
	}
	return uc_err_strlen(error);
}

errno_t dcl_err_strcpy_s(c_err error, char* message, rsize_t size) {
	if (dcl_err_is_alloc(error)) {
		return dcl_err_strcpy_s_alloc(dcl_err_get_arg(error), message, size);
	}
	if (dcl_err_is_index_out(error)) {
		return dcl_err_strcpy_s_index_out(dcl_err_get_arg(error), message, size);
	}
	if (dcl_err_is_null(error)) {
		return dcl_err_strcpy_s_null(dcl_err_get_arg(error), message, size);
	}
	if (dcl_err_is_not_found(error)) {
		return dcl_err_strcpy_s_not_found(dcl_err_get_arg(error), message, size);
	}
	return uc_err_strcpy_s(error, message, size);
}
