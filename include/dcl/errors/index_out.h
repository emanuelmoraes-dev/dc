#ifndef DCL_ERRORS_INDEX_OUT_H_INCLUDED
#define DCL_ERRORS_INDEX_OUT_H_INCLUDED

#include "dcl/errors/base.h"

DCL_ERR_DEF(index_out)

#define DCL_ERR_MESSAGE_INDEX_OUT "Index Out Of Bounds"

#define DCL_ERR_ARG_INDEX_OUT_ALPHABET (1)
#define DCL_ERR_ARG_MESSAGE_INDEX_OUT_ALPHABET "Alphabet Size"

#define DCL_ERR_ARG_INDEX_OUT_ODDS (2)
#define DCL_ERR_ARG_MESSAGE_INDEX_OUT_ODDS "Odds"

size_t dcl_err_arg_strlen_index_out(int arg);
errno_t dcl_err_arg_strcat_s_index_out(int arg, char* message, rsize_t size);

int dcl_err_strlen_index_out(int arg);
errno_t dcl_err_strcpy_s_index_out(int arg, char* message, rsize_t size);

#endif
