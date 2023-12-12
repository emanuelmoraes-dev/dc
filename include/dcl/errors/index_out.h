#ifndef DCL_ERRORS_INDEX_OUT_H_INCLUDED
#define DCL_ERRORS_INDEX_OUT_H_INCLUDED

#include "dcl/errors/base.h"

#define DCL_ERR_ID_INDEX_OUT (2)
#define DCL_ERR_THROW_INDEX_OUT(arg) __DCL_ERR_THROW(DCL_ERR_ID_INDEX_OUT, arg)
#define DCL_ERR_IS_INDEX_OUT(error) __DCL_ERR_IS(DCL_ERR_ID_INDEX_OUT, error)

#define DCL_ERR_MESSAGE_INDEX_OUT "Index Out Of Bounds"

#define DCL_ERR_ARG_INDEX_OUT_ALPHABET (1)
#define DCL_ERR_ARG_MESSAGE_INDEX_OUT_ALPHABET "Alphabet"

#define DCL_ERR_ARG_INDEX_OUT_ODDS (2)
#define DCL_ERR_ARG_MESSAGE_INDEX_OUT_ODDS "Odds"

size_t dcl_err_arg_strlen_index_out(int arg);
errno_t dcl_err_arg_strcat_s_index_out(int arg, char* message, rsize_t size);

int dcl_err_strlen_index_out(int arg);
errno_t dcl_err_strcpy_s_index_out(int arg, char* message, rsize_t size);

#endif
