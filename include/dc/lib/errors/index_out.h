#ifndef DC_LIB_ERRORS_INDEX_OUT_H_INCLUDED
#define DC_LIB_ERRORS_INDEX_OUT_H_INCLUDED

#include "dc/lib/errors/base.h"

#define DC_LIB_ERR_ID_INDEX_OUT (2)
#define DC_LIB_ERR_THROW_INDEX_OUT(arg) __DC_LIB_ERR_THROW(DC_LIB_ERR_ID_INDEX_OUT, arg)
#define DC_LIB_ERR_IS_INDEX_OUT(error) __DC_LIB_ERR_IS(DC_LIB_ERR_ID_INDEX_OUT, error)

#define DC_LIB_ERR_MESSAGE_INDEX_OUT "Index Out Of Bounds"

#define DC_LIB_ERR_ARG_INDEX_OUT_ALPHABET (1)
#define DC_LIB_ERR_ARG_MESSAGE_INDEX_OUT_ALPHABET "Alphabet"

#define DC_LIB_ERR_ARG_INDEX_OUT_ODDS (2)
#define DC_LIB_ERR_ARG_MESSAGE_INDEX_OUT_ODDS "Odds"

size_t dc_lib_err_arg_strlen_index_out(int arg);
errno_t dc_lib_err_arg_strcat_s_index_out(int arg, char* message, rsize_t size);

int dc_lib_err_strlen_index_out(int arg);
errno_t dc_lib_err_strcpy_s_index_out(int arg, char* message, rsize_t size);

#endif
