#include "dcl/errors/not_found.h"

size_t dcl_err_arg_strlen_not_found(int arg) {
	switch(arg) {
	case DCL_ERR_ARG_NOT_FOUND_ALPHABET_KEY: return strlen(DCL_ERR_ARG_MESSAGE_NOT_FOUND_ALPHABET_KEY);
	case DCL_ERR_ARG_NOT_FOUND_ALPHABET_SENTENCES: return strlen(DCL_ERR_ARG_MESSAGE_NOT_FOUND_ALPHABET_SENTENCES);
	case DCL_ERR_ARG_NOT_FOUND_GRAPH_TARGET_KEY: return strlen(DCL_ERR_ARG_MESSAGE_NOT_FOUND_GRAPH_TARGET_KEY);
	case DCL_ERR_ARG_NOT_FOUND_GRAPH_DEP_KEY: return strlen(DCL_ERR_ARG_MESSAGE_NOT_FOUND_GRAPH_DEP_KEY);
	case DCL_ERR_ARG_NOT_FOUND_ODDS: return strlen(DCL_ERR_ARG_MESSAGE_NOT_FOUND_ODDS);
	case DCL_ERR_ARG_NOT_FOUND_GRAPH: return strlen(DCL_ERR_ARG_MESSAGE_NOT_FOUND_GRAPH);
	case DCL_ERR_ARG_NOT_FOUND_GRAPH_NODE: return strlen(DCL_ERR_ARG_MESSAGE_NOT_FOUND_GRAPH_NODE);
	case DCL_ERR_ARG_NOT_FOUND_AVAILABLE_SENTENCE: return strlen(DCL_ERR_ARG_MESSAGE_NOT_FOUND_AVAILABLE_SENTENCE);
	default: return strlen("Unexpected");
	}
}

errno_t dcl_err_arg_strcat_s_not_found(int arg, char* message, rsize_t size) {
	switch(arg) {
	case DCL_ERR_ARG_NOT_FOUND_ALPHABET_KEY: return strcat_s(message, size, DCL_ERR_ARG_MESSAGE_NOT_FOUND_ALPHABET_KEY);
	case DCL_ERR_ARG_NOT_FOUND_ALPHABET_SENTENCES: return strcat_s(message, size, DCL_ERR_ARG_MESSAGE_NOT_FOUND_ALPHABET_SENTENCES);
	case DCL_ERR_ARG_NOT_FOUND_GRAPH_TARGET_KEY: return strcat_s(message, size, DCL_ERR_ARG_MESSAGE_NOT_FOUND_GRAPH_TARGET_KEY);
	case DCL_ERR_ARG_NOT_FOUND_GRAPH_DEP_KEY: return strcat_s(message, size, DCL_ERR_ARG_MESSAGE_NOT_FOUND_GRAPH_DEP_KEY);
	case DCL_ERR_ARG_NOT_FOUND_ODDS: return strcat_s(message, size, DCL_ERR_ARG_MESSAGE_NOT_FOUND_ODDS);
	case DCL_ERR_ARG_NOT_FOUND_GRAPH: return strcat_s(message, size, DCL_ERR_ARG_MESSAGE_NOT_FOUND_GRAPH);
	case DCL_ERR_ARG_NOT_FOUND_GRAPH_NODE: return strcat_s(message, size, DCL_ERR_ARG_MESSAGE_NOT_FOUND_GRAPH_NODE);
	case DCL_ERR_ARG_NOT_FOUND_AVAILABLE_SENTENCE: return strcat_s(message, size, DCL_ERR_ARG_MESSAGE_NOT_FOUND_AVAILABLE_SENTENCE);
	default: return strcat_s(message, size, "Unexpected");
	}
}

size_t dcl_err_strlen_not_found(int arg) {
	return __dcl_err_strlen(arg, strlen(DCL_ERR_MESSAGE_NOT_FOUND), dcl_err_arg_strlen_not_found);
}

errno_t dcl_err_strcpy_s_not_found(int arg, char* message, rsize_t size) {
	return __dcl_err_strcpy_s(arg, DCL_ERR_MESSAGE_NOT_FOUND, dcl_err_arg_strcat_s_not_found, message, size);
}
