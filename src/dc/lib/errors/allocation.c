#include "dc/lib/errors/allocation.h"

size_t dc_lib_err_arg_strlen_alloc(int arg) {
	switch(arg) {
	case DC_LIB_ERR_ARG_ALLOC_ALPHABET: return strlen(DC_LIB_ERR_ARG_MESSAGE_ALLOC_ALPHABET);
	case DC_LIB_ERR_ARG_ALLOC_ODDS_GRAPH: return strlen(DC_LIB_ERR_ARG_MESSAGE_ALLOC_ODDS_GRAPH);
	case DC_LIB_ERR_ARG_ALLOC_SENTENCE: return strlen(DC_LIB_ERR_ARG_MESSAGE_ALLOC_SENTENCE);
	default: return strlen("Unexpected");
	}
}

errno_t dc_lib_err_arg_strcat_s_alloc(int arg, char* message, rsize_t size) {
	switch(arg) {
	case DC_LIB_ERR_ARG_ALLOC_ALPHABET: return strcat_s(message, size, DC_LIB_ERR_ARG_MESSAGE_ALLOC_ALPHABET);
	case DC_LIB_ERR_ARG_ALLOC_ODDS_GRAPH: return strcat_s(message, size, DC_LIB_ERR_ARG_MESSAGE_ALLOC_ODDS_GRAPH);
	case DC_LIB_ERR_ARG_ALLOC_SENTENCE: return strcat_s(message, size, DC_LIB_ERR_ARG_MESSAGE_ALLOC_SENTENCE);
	default: return strcat_s(message, size, "Unexpected");
	}
}

size_t dc_lib_err_strlen_alloc(int arg) {
	return __dc_lib_err_strlen(arg, strlen(DC_LIB_ERR_MESSAGE_ALLOC), dc_lib_err_arg_strlen_alloc);
}

errno_t dc_lib_err_strcpy_s_alloc(int arg, char* message, rsize_t size) {
	return __dc_lib_err_strcpy_s(arg, DC_LIB_ERR_MESSAGE_ALLOC, dc_lib_err_arg_strcat_s_alloc, message, size);
}
