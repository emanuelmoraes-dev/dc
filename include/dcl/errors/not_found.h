#ifndef DCL_ERRORS_NOT_FOUND_H_INCLUDED
#define DCL_ERRORS_NOT_FOUND_H_INCLUDED

#include "dcl/errors/base.h"

#define DCL_ERR_ID_NOT_FOUND (3)
#define DCL_ERR_THROW_NOT_FOUND(args) __DCL_ERR_THROW(DCL_ERR_ID_NOT_FOUND, args)
#define DCL_ERR_IS_NOT_FOUND(error) __DCL_ERR_IS(DCL_ERR_ID_NOT_FOUND, error)

#define DCL_ERR_MESSAGE_NOT_FOUND "Not Found"

#define DCL_ERR_ARG_NOT_FOUND_ALPHABET_KEY (1)
#define DCL_ERR_ARG_MESSAGE_NOT_FOUND_ALPHABET_KEY "Alphabet Key"

#define DCL_ERR_ARG_NOT_FOUND_ALPHABET_SENTENCES (2)
#define DCL_ERR_ARG_MESSAGE_NOT_FOUND_ALPHABET_SENTENCES "Alphabet Sentences"

size_t dcl_err_arg_strlen_not_found(int arg);
errno_t dcl_err_arg_strcat_s_not_found(int arg, char* message, rsize_t size);

size_t dcl_err_strlen_not_found(int arg);
errno_t dcl_err_strcpy_s_not_found(int arg, char* message, rsize_t size);

#endif
