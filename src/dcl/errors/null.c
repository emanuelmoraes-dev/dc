#include "dcl/errors/null.h"

DCL_ERR_IMPL(null, 5)

size_t dcl_err_arg_strlen_null(int arg) {
	switch(arg) {
	case DCL_ERR_ARG_NULL_ALPHABET_KEY: return strlen(DCL_ERR_ARG_MESSAGE_NULL_ALPHABET_KEY);
	case DCL_ERR_ARG_NULL_ALPHABET_SENTENCE: return strlen(DCL_ERR_ARG_MESSAGE_NULL_ALPHABET_SENTENCE);
	case DCL_ERR_ARG_NULL_GRAPH_KEY: return strlen(DCL_ERR_ARG_MESSAGE_NULL_GRAPH_KEY);
	case DCL_ERR_ARG_NULL_RESULT_KEY: return strlen(DCL_ERR_ARG_MESSAGE_NULL_RESULT_KEY);
	case DCL_ERR_ARG_NULL_RESULT_SENTENCES: return strlen(DCL_ERR_ARG_MESSAGE_NULL_RESULT_SENTENCES);
	case DCL_ERR_ARG_NULL_RESULT_SENTENCE: return strlen(DCL_ERR_ARG_MESSAGE_NULL_RESULT_SENTENCE);
	case DCL_ERR_ARG_NULL_NODE: return strlen(DCL_ERR_ARG_MESSAGE_NULL_NODE);
	case DCL_ERR_ARG_NULL_ODDS_VALUE: return strlen(DCL_ERR_ARG_MESSAGE_NULL_ODDS_VALUE);
	default: return strlen("Unexpected");
	}
}

errno_t dcl_err_arg_strcat_s_null(int arg, char* message, rsize_t size) {
	switch(arg) {
	case DCL_ERR_ARG_NULL_ALPHABET_KEY: return strcpy_s(message, size, DCL_ERR_ARG_MESSAGE_NULL_ALPHABET_KEY);
	case DCL_ERR_ARG_NULL_ALPHABET_SENTENCE: return strcpy_s(message, size, DCL_ERR_ARG_MESSAGE_NULL_ALPHABET_SENTENCE);
	case DCL_ERR_ARG_NULL_GRAPH_KEY: return strcpy_s(message, size, DCL_ERR_ARG_MESSAGE_NULL_GRAPH_KEY);
	case DCL_ERR_ARG_NULL_RESULT_KEY: return strcpy_s(message, size, DCL_ERR_ARG_MESSAGE_NULL_RESULT_KEY);
	case DCL_ERR_ARG_NULL_RESULT_SENTENCES: return strcpy_s(message, size, DCL_ERR_ARG_MESSAGE_NULL_RESULT_SENTENCES);
	case DCL_ERR_ARG_NULL_RESULT_SENTENCE: return strcpy_s(message, size, DCL_ERR_ARG_MESSAGE_NULL_RESULT_SENTENCE);
	case DCL_ERR_ARG_NULL_NODE: return strcpy_s(message, size, DCL_ERR_ARG_MESSAGE_NULL_NODE);
	case DCL_ERR_ARG_NULL_ODDS_VALUE: return strcpy_s(message, size, DCL_ERR_ARG_MESSAGE_NULL_ODDS_VALUE);
	default: return strcpy_s(message, size, "Unexpected");
	}
}

size_t dcl_err_strlen_null(int arg) {
	return __dcl_err_strlen(arg, strlen(DCL_ERR_MESSAGE_NULL), dcl_err_arg_strlen_null);
}

errno_t dcl_err_strcpy_s_null(int arg, char* message, rsize_t size) {
	return __dcl_err_strcpy_s(arg, DCL_ERR_MESSAGE_NULL, dcl_err_arg_strcat_s_null, message, size);
}
