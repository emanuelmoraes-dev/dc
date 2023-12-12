#include "dcl/errors.h"

size_t dcl_err_strlen(c_err error) {
	if (DCL_ERR_IS_ALLOC(error)) {
		return dcl_err_strlen_alloc(DCL_ERR_GET_ARG(error));
	}

	if (DCL_ERR_IS_INDEX_OUT(error)) {
		return dcl_err_strlen_index_out(DCL_ERR_GET_ARG(error));
	}

	return uc_err_strlen(error);
}

errno_t dcl_err_strcpy_s(c_err error, char* message, rsize_t size) {
	if (DCL_ERR_IS_ALLOC(error)) {
		return dcl_err_strcpy_s_alloc(DCL_ERR_GET_ARG(error), message, size);
	}

	if (DCL_ERR_IS_INDEX_OUT(error)) {
		return dcl_err_strcpy_s_index_out(DCL_ERR_GET_ARG(error), message, size);
	}

	return uc_err_strcpy_s(error, message, size);
}
