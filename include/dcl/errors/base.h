#ifndef DCL_ERRORS_BASE_H_INCLUDED
#define DCL_ERRORS_BASE_H_INCLUDED

#include <string.h>
#include <errno.h>
#include "uc/errors/base.h"

#define C_OK (0)

#define __DCL_ERR_FACTOR (100)
#define __DCL_ERR_BASE (100)
#define __DCL_ERR_GET_ID(error) ((int)((error) - __DCL_ERR_BASE) / __DCL_ERR_FACTOR)
#define __DCL_ERR_THROW(error_id, arg) ((error_id) * __DCL_ERR_FACTOR + (arg) + __DCL_ERR_BASE)
#define __DCL_ERR_IS(error_id, error) (__DCL_ERR_GET_ID(error) == (error_id))

#define DCL_ERR_GET_ARG(error) (((error) - __DCL_ERR_BASE) % (__DCL_ERR_GET_ID(error) * __DCL_ERR_FACTOR))

size_t __dcl_err_strlen(int arg, size_t error_message_len, size_t (*arg_strlen)(int));
errno_t __dcl_err_strcpy_s(int arg, const char* error_message, errno_t (*arg_strcat_s)(int, char*, rsize_t), char* message, rsize_t size);

#endif
