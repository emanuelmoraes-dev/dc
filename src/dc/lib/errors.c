#include "dc/lib/errors.h"

size_t dc_lib_err_strlen(dc_lib_err error) {
	if (DC_LIB_ERR_IS_ALLOC(error)) {
		return dc_lib_err_strlen_alloc(DC_LIB_ERR_GET_ARG(error));
	}

	if (DC_LIB_ERR_IS_INDEX_OUT(error)) {
		return dc_lib_err_strlen_index_out(DC_LIB_ERR_GET_ARG(error));
	}

	return strlen("Unexpected");
}

errno_t dc_lib_err_strcpy_s(dc_lib_err error, char* message, rsize_t size) {
	if (DC_LIB_ERR_IS_ALLOC(error)) {
		return dc_lib_err_strcpy_s_alloc(DC_LIB_ERR_GET_ARG(error), message, size);
	}

	if (DC_LIB_ERR_IS_INDEX_OUT(error)) {
		return dc_lib_err_strcpy_s_index_out(DC_LIB_ERR_GET_ARG(error), message, size);
	}

	return strcpy_s(message, size, "Unexpected");
}
