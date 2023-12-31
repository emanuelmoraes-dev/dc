#ifndef DCL_ERRORS_NULL_H_INCLUDED
#define DCL_ERRORS_NULL_H_INCLUDED

#include "dcl/errors/base.h"

#define DCL_ERR_ID_NULL (4)
#define DCL_ERR_THROW_NULL(arg) __DCL_ERR_THROW(DCL_ERR_ID_NULL, arg)
#define DCL_ERR_IS_NULL(error) __DCL_ERR_IS(DCL_ERR_ID_NULL, error)

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

size_t dcl_err_arg_strlen_null(int arg);
errno_t dcl_err_arg_strcat_s_null(int arg, char* message, rsize_t size);

size_t dcl_err_strlen_null(int arg);
errno_t dcl_err_strcpy_s_null(int arg, char* message, rsize_t size);

#endif
