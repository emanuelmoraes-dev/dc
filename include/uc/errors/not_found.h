#ifndef UC_ERRORS_NOT_FOUND_H_INCLUDED
#define UC_ERRORS_NOT_FOUND_H_INCLUDED

#include "uc/errors/base.h"

#define UC_ERR_ID_NOT_FOUND (3)
#define UC_ERR_THROW_NOT_FOUND(args) __UC_ERR_THROW(UC_ERR_ID_NOT_FOUND, args)
#define UC_ERR_IS_NOT_FOUND(error) __UC_ERR_IS(UC_ERR_ID_NOT_FOUND, error)

#define UC_ERR_MESSAGE_NOT_FOUND "Not Found"

#define UC_ERR_ARG_NOT_FOUND_HASH_MAP_ITEM (1)
#define UC_ERR_ARG_MESSAGE_NOT_FOUND_HASH_MAP_ITEM "Hash Map Item"

size_t uc_err_arg_strlen_not_found(int arg);
errno_t uc_err_arg_strcat_s_not_found(int arg, char* message, rsize_t size);

size_t uc_err_strlen_not_found(int arg);
errno_t uc_err_strcpy_s_not_found(int arg, char* message, rsize_t size);

#endif
