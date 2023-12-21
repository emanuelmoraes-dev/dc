#include "dcl/errors/null.h"

size_t dcl_err_arg_strlen_null(int arg) {
	switch(arg) {
	case DCL_ERR_ARG_NULL_ALPHABET_KEY: return strlen(DCL_ERR_ARG_MESSAGE_NULL_ALPHABET_KEY);
	case DCL_ERR_ARG_NULL_ALPHABET_SENTENCE: return strlen(DCL_ERR_ARG_MESSAGE_NULL_ALPHABET_SENTENCE);
	default: return strlen("Unexpected");
	}
}

errno_t dcl_err_arg_strcat_s_null(int arg, char* message, rsize_t size) {
	switch(arg) {
	case DCL_ERR_ARG_NULL_ALPHABET_KEY: return strcpy_s(message, size, DCL_ERR_ARG_MESSAGE_NULL_ALPHABET_KEY);
	case DCL_ERR_ARG_NULL_ALPHABET_SENTENCE: return strcpy_s(message, size, DCL_ERR_ARG_MESSAGE_NULL_ALPHABET_SENTENCE);
	default: return strcpy_s(message, size, "Unexpected");
	}
}

size_t dcl_err_strlen_null(int arg) {
	return __dcl_err_strlen(arg, strlen(DCL_ERR_MESSAGE_NULL), dcl_err_arg_strlen_null);
}

errno_t dcl_err_strcpy_s_null(int arg, char* message, rsize_t size) {
	return __dcl_err_strcpy_s(arg, DCL_ERR_MESSAGE_NULL, dcl_err_arg_strcat_s_null, message, size);
}
