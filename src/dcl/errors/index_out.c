#include "dcl/errors/index_out.h"

size_t dcl_err_arg_strlen_index_out(int arg) {
	switch(arg) {
	case DCL_ERR_ARG_INDEX_OUT_ALPHABET: return strlen(DCL_ERR_ARG_MESSAGE_INDEX_OUT_ALPHABET);
	case DCL_ERR_ARG_INDEX_OUT_ODDS: return strlen(DCL_ERR_ARG_MESSAGE_INDEX_OUT_ODDS);
	default: return strlen("Unexpected");
	}
}

errno_t dcl_err_arg_strcat_s_index_out(int arg, char* message, rsize_t size) {
	switch(arg) {
	case DCL_ERR_ARG_INDEX_OUT_ALPHABET: return strcat_s(message, size, DCL_ERR_ARG_MESSAGE_INDEX_OUT_ALPHABET);
	case DCL_ERR_ARG_INDEX_OUT_ODDS: return strcat_s(message, size, DCL_ERR_ARG_MESSAGE_INDEX_OUT_ODDS);
	default: return strcat_s(message, size, "Unexpected");
	}
}

int dcl_err_strlen_index_out(int arg) {
	return __dcl_err_strlen(arg, strlen(DCL_ERR_MESSAGE_INDEX_OUT), dcl_err_arg_strlen_index_out);
}

errno_t dcl_err_strcpy_s_index_out(int arg, char* message, rsize_t size) {
	return __dcl_err_strcpy_s(arg, DCL_ERR_MESSAGE_INDEX_OUT, dcl_err_arg_strcat_s_index_out, message, size);
}
