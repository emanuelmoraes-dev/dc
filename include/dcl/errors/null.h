#ifndef _DCL_ERRORS_NULL_H_INCLUDED_
#define _DCL_ERRORS_NULL_H_INCLUDED_

#include "dcl/errors/base.h"

DCL_ERR_DEF(null)

#define DCL_ERR_MESSAGE_NULL "Null Pointer"

#define DCL_ERR_ARG_NULL_ALPHABET_KEY (1)
#define DCL_ERR_ARG_MESSAGE_NULL_ALPHABET_KEY "Alphabet Key"

#define DCL_ERR_ARG_NULL_ALPHABET_SENTENCE (2)
#define DCL_ERR_ARG_MESSAGE_NULL_ALPHABET_SENTENCE "Alphabet Sentence"

#define DCL_ERR_ARG_NULL_GRAPH_KEY (3)
#define DCL_ERR_ARG_MESSAGE_NULL_GRAPH_KEY "Graph Key"

#define DCL_ERR_ARG_NULL_RESULT_KEY (4)
#define DCL_ERR_ARG_MESSAGE_NULL_RESULT_KEY "Result Key"

#define DCL_ERR_ARG_NULL_RESULT_SENTENCES (5)
#define DCL_ERR_ARG_MESSAGE_NULL_RESULT_SENTENCES "Result Sentences"

#define DCL_ERR_ARG_NULL_RESULT_SENTENCE (6)
#define DCL_ERR_ARG_MESSAGE_NULL_RESULT_SENTENCE "Result Sentence"

#define DCL_ERR_ARG_NULL_NODE (7)
#define DCL_ERR_ARG_MESSAGE_NULL_NODE "Node"

#define DCL_ERR_ARG_NULL_ODDS_VALUE (8)
#define DCL_ERR_ARG_MESSAGE_NULL_ODDS_VALUE "Odds Value"

size_t dcl_err_arg_strlen_null(int arg);
errno_t dcl_err_arg_strcat_s_null(int arg, char* message, rsize_t size);

size_t dcl_err_strlen_null(int arg);
errno_t dcl_err_strcpy_s_null(int arg, char* message, rsize_t size);

#endif
