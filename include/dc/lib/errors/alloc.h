#ifndef DC_LIB_ERRORS_ALLOC_H_INCLUDED
#define DC_LIB_ERRORS_ALLOC_H_INCLUDED

#include "dc/lib/errors/base.h"

#define DC_LIB_ERR_ID_ALLOC (1)
#define DC_LIB_ERR_THROW_ALLOC(arg) __DC_LIB_ERR_THROW(DC_LIB_ERR_ID_ALLOC, arg)
#define DC_LIB_ERR_IS_ALLOC(error) __DC_LIB_ERR_IS(DC_LIB_ERR_ID_ALLOC, error)

#define DC_LIB_ERR_MESSAGE_ALLOC "Error When Allocating"

#define DC_LIB_ERR_ARG_ALLOC_ALPHABET (1)
#define DC_LIB_ERR_ARG_MESSAGE_ALLOC_ALPHABET "Alphabet"

#define DC_LIB_ERR_ARG_ALLOC_ODDS_GRAPH (2)
#define DC_LIB_ERR_ARG_MESSAGE_ALLOC_ODDS_GRAPH "Odds Graph"

#define DC_LIB_ERR_ARG_ALLOC_SENTENCE (3)
#define DC_LIB_ERR_ARG_MESSAGE_ALLOC_SENTENCE "Sentence"

size_t dc_lib_err_arg_strlen_alloc(int arg);
errno_t dc_lib_err_arg_strcat_s_alloc(int arg, char* message, rsize_t size);

size_t dc_lib_err_strlen_alloc(int arg);
errno_t dc_lib_err_strcpy_s_alloc(int arg, char* message, rsize_t size);

#endif
