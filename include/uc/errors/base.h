#ifndef UC_ERRORS_BASE_H_INCLUDED
#define UC_ERRORS_BASE_H_INCLUDED

#include <string.h>
#include <errno.h>

typedef int c_err;

#define C_OK (0)

#define __UC_ERR_FACTOR (100)
#define __UC_ERR_BASE (10000)
#define __UC_ERR_GET_ID(error) ((int)((error) - __UC_ERR_BASE) / __UC_ERR_FACTOR)
#define __UC_ERR_THROW(error_id, arg) ((error_id) * __UC_ERR_FACTOR + (arg) + __UC_ERR_BASE)
#define __UC_ERR_IS(error_id, error) (__UC_ERR_GET_ID(error) == (error_id))

#define UC_ERR_GET_ARG(error) (((error) - __UC_ERR_BASE) % (__UC_ERR_GET_ID(error) * __UC_ERR_FACTOR))

size_t __uc_err_strlen(int arg, size_t error_message_len, size_t (*arg_strlen)(int));
errno_t __uc_err_strcpy_s(int arg, const char* error_message, errno_t (*arg_strcat_s)(int, char*, rsize_t), char* message, rsize_t size);

#endif
