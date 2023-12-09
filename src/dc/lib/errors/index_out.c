#include "dc/lib/errors/index_out.h"

size_t dc_lib_err_arg_strlen_index_out(int arg) {
	switch(arg) {
	case DC_LIB_ERR_ARG_INDEX_OUT_ALPHABET: return strlen(DC_LIB_ERR_ARG_MESSAGE_INDEX_OUT_ALPHABET);
	case DC_LIB_ERR_ARG_INDEX_OUT_ODDS: return strlen(DC_LIB_ERR_ARG_MESSAGE_INDEX_OUT_ODDS);
	default: return strlen("Unexpected");
	}
}

errno_t dc_lib_err_arg_strcat_s_index_out(int arg, char* message, rsize_t size) {
	switch(arg) {
	case DC_LIB_ERR_ARG_INDEX_OUT_ALPHABET: return strcat_s(message, size, DC_LIB_ERR_ARG_MESSAGE_INDEX_OUT_ALPHABET);
	case DC_LIB_ERR_ARG_INDEX_OUT_ODDS: return strcat_s(message, size, DC_LIB_ERR_ARG_MESSAGE_INDEX_OUT_ODDS);
	default: return strcat_s(message, size, "Unexpected");
	}
}

int dc_lib_err_strlen_index_out(int arg) {
	return __dc_lib_err_strlen(arg, strlen(DC_LIB_ERR_MESSAGE_INDEX_OUT), dc_lib_err_arg_strlen_index_out);
}

errno_t dc_lib_err_strcpy_s_index_out(int arg, char* message, rsize_t size) {
	return __dc_lib_err_strcpy_s(arg, DC_LIB_ERR_MESSAGE_INDEX_OUT, dc_lib_err_arg_strcat_s_index_out, message, size);
}
