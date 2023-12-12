#include "dcl/errors/alloc.h"

size_t dcl_err_arg_strlen_alloc(int arg) {
	switch(arg) {
	case DCL_ERR_ARG_ALLOC_ALPHABET: return strlen(DCL_ERR_ARG_MESSAGE_ALLOC_ALPHABET);
	case DCL_ERR_ARG_ALLOC_ODDS_GRAPH: return strlen(DCL_ERR_ARG_MESSAGE_ALLOC_ODDS_GRAPH);
	case DCL_ERR_ARG_ALLOC_SENTENCE: return strlen(DCL_ERR_ARG_MESSAGE_ALLOC_SENTENCE);
	default: return strlen("Unexpected");
	}
}

errno_t dcl_err_arg_strcat_s_alloc(int arg, char* message, rsize_t size) {
	switch(arg) {
	case DCL_ERR_ARG_ALLOC_ALPHABET: return strcat_s(message, size, DCL_ERR_ARG_MESSAGE_ALLOC_ALPHABET);
	case DCL_ERR_ARG_ALLOC_ODDS_GRAPH: return strcat_s(message, size, DCL_ERR_ARG_MESSAGE_ALLOC_ODDS_GRAPH);
	case DCL_ERR_ARG_ALLOC_SENTENCE: return strcat_s(message, size, DCL_ERR_ARG_MESSAGE_ALLOC_SENTENCE);
	default: return strcat_s(message, size, "Unexpected");
	}
}

size_t dcl_err_strlen_alloc(int arg) {
	return __dcl_err_strlen(arg, strlen(DCL_ERR_MESSAGE_ALLOC), dcl_err_arg_strlen_alloc);
}

errno_t dcl_err_strcpy_s_alloc(int arg, char* message, rsize_t size) {
	return __dcl_err_strcpy_s(arg, DCL_ERR_MESSAGE_ALLOC, dcl_err_arg_strcat_s_alloc, message, size);
}
