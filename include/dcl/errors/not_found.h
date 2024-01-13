#ifndef _DCL_ERRORS_NOT_FOUND_H_INCLUDED_
#define _DCL_ERRORS_NOT_FOUND_H_INCLUDED_

#include "dcl/errors/base.h"

DCL_ERR_DEF(not_found)

#define DCL_ERR_MESSAGE_NOT_FOUND "Not Found"

#define DCL_ERR_ARG_NOT_FOUND_ALPHABET_KEY (1)
#define DCL_ERR_ARG_MESSAGE_NOT_FOUND_ALPHABET_KEY "Alphabet Key"

#define DCL_ERR_ARG_NOT_FOUND_ALPHABET_SENTENCES (2)
#define DCL_ERR_ARG_MESSAGE_NOT_FOUND_ALPHABET_SENTENCES "Alphabet DclSentences"

#define DCL_ERR_ARG_NOT_FOUND_GRAPH_TARGET_KEY (3)
#define DCL_ERR_ARG_MESSAGE_NOT_FOUND_GRAPH_TARGET_KEY "Graph Target Key"

#define DCL_ERR_ARG_NOT_FOUND_GRAPH_DEP_KEY (4)
#define DCL_ERR_ARG_MESSAGE_NOT_FOUND_GRAPH_DEP_KEY "Graph Dep Key"

#define DCL_ERR_ARG_NOT_FOUND_ODDS (5)
#define DCL_ERR_ARG_MESSAGE_NOT_FOUND_ODDS "Odds"

#define DCL_ERR_ARG_NOT_FOUND_GRAPH (6)
#define DCL_ERR_ARG_MESSAGE_NOT_FOUND_GRAPH "Graph"

#define DCL_ERR_ARG_NOT_FOUND_GRAPH_NODE (7)
#define DCL_ERR_ARG_MESSAGE_NOT_FOUND_GRAPH_NODE "Graph Node"

#define DCL_ERR_ARG_NOT_FOUND_AVAILABLE_SENTENCE (8)
#define DCL_ERR_ARG_MESSAGE_NOT_FOUND_AVAILABLE_SENTENCE "Available Sentence"

size_t dcl_err_arg_strlen_not_found(int arg);
errno_t dcl_err_arg_strcat_s_not_found(int arg, char* message, rsize_t size);

size_t dcl_err_strlen_not_found(int arg);
errno_t dcl_err_strcpy_s_not_found(int arg, char* message, rsize_t size);

#endif
