#include "dcl/errors/alloc.h"

size_t dcl_err_arg_strlen_alloc(int arg) {
	switch(arg) {
	case DCL_ERR_ARG_ALLOC_DEP_GRAPH: return strlen(DCL_ERR_ARG_MESSAGE_ALLOC_DEP_GRAPH);
	case DCL_ERR_ARG_ALLOC_ODDS: return strlen(DCL_ERR_ARG_MESSAGE_ALLOC_ODDS);
	case DCL_ERR_ARG_ALLOC_ODDS_GRAPH: return strlen(DCL_ERR_ARG_MESSAGE_ALLOC_ODDS_GRAPH);
	case DCL_ERR_ARG_ALLOC_ODDS_GRAPH_NODE: return strlen(DCL_ERR_ARG_MESSAGE_ALLOC_ODDS_GRAPH_NODE);
	case DCL_ERR_ARG_ALLOC_SENTENCES: return strlen(DCL_ERR_ARG_MESSAGE_ALLOC_SENTENCES);
	case DCL_ERR_ARG_ALLOC_CONTENT_GEN: return strlen(DCL_ERR_ARG_MESSAGE_ALLOC_CONTENT_GEN);
	default: return strlen("Unexpected");
	}
}

errno_t dcl_err_arg_strcat_s_alloc(int arg, char* message, rsize_t size) {
	switch(arg) {
	case DCL_ERR_ARG_ALLOC_DEP_GRAPH: return strcat_s(message, size, DCL_ERR_ARG_MESSAGE_ALLOC_DEP_GRAPH);
	case DCL_ERR_ARG_ALLOC_ODDS: return strcat_s(message, size, DCL_ERR_ARG_MESSAGE_ALLOC_ODDS);
	case DCL_ERR_ARG_ALLOC_ODDS_GRAPH: return strcat_s(message, size, DCL_ERR_ARG_MESSAGE_ALLOC_ODDS_GRAPH);
	case DCL_ERR_ARG_ALLOC_ODDS_GRAPH_NODE: return strcat_s(message, size, DCL_ERR_ARG_MESSAGE_ALLOC_ODDS_GRAPH_NODE);
	case DCL_ERR_ARG_ALLOC_SENTENCES: return strcat_s(message, size, DCL_ERR_ARG_MESSAGE_ALLOC_SENTENCES);
	case DCL_ERR_ARG_ALLOC_CONTENT_GEN: return strcat_s(message, size, DCL_ERR_ARG_MESSAGE_ALLOC_CONTENT_GEN);
	default: return strcat_s(message, size, "Unexpected");
	}
}

size_t dcl_err_strlen_alloc(int arg) {
	return __dcl_err_strlen(arg, strlen(DCL_ERR_MESSAGE_ALLOC), dcl_err_arg_strlen_alloc);
}

errno_t dcl_err_strcpy_s_alloc(int arg, char* message, rsize_t size) {
	return __dcl_err_strcpy_s(arg, DCL_ERR_MESSAGE_ALLOC, dcl_err_arg_strcat_s_alloc, message, size);
}
