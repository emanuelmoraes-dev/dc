#ifndef UC_ERRORS_EMPTY_H_INCLUDED
#define UC_ERRORS_EMPTY_H_INCLUDED

#include "uc/errors/base.h"

UC_ERR_DEF(empty)

#define UC_ERR_MESSAGE_EMPTY "Empty"

#define UC_ERR_ARG_EMPTY_HASH_MAP (1)
#define UC_ERR_ARG_MESSAGE_EMPTY_HASH_MAP "Hash Map"

size_t uc_err_arg_strlen_empty(int arg);
errno_t uc_err_arg_strcat_s_empty(int arg, char* message, rsize_t size);

size_t uc_err_strlen_empty(int arg);
errno_t uc_err_strcpy_s_empty(int arg, char* message, rsize_t size);

#endif
