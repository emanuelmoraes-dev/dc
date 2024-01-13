#ifndef UC_ERRORS_OVERFLOW_H_INCLUDED
#define UC_ERRORS_OVERFLOW_H_INCLUDED

#include "uc/errors/base.h"

UC_ERR_DEF(overflow)

#define UC_ERR_MESSAGE_OVERFLOW "Overflow Error"

#define UC_ERR_ARG_OVERFLOW_LARGE (1)
#define UC_ERR_ARG_MESSAGE_OVERFLOW_LARGE "Result of the operation is too large to fit in the variable."

#define UC_ERR_ARG_OVERFLOW_SMALL (2)
#define UC_ERR_ARG_MESSAGE_OVERFLOW_SMALL "Result of the operation is too small to be represented in the variable."

#define UC_ERR_ARG_OVERFLOW_LARGE_HASH_MAP_CAPACITY (3)
#define UC_ERR_ARG_MESSAGE_OVERFLOW_LARGE_HASH_MAP_CAPACITY "Hash Map capacity cannot be reallocated because the result is too large"

size_t uc_err_arg_strlen_overflow(int arg);
errno_t uc_err_arg_strcat_s_overflow(int arg, char* message, rsize_t size);

size_t uc_err_strlen_overflow(int arg);
errno_t uc_err_strcpy_s_overflow(int arg, char* message, rsize_t size);

#endif
