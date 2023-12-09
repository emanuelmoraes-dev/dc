#ifndef DC_LIB_ERRORS_BASE_H_INCLUDED
#define DC_LIB_ERRORS_BASE_H_INCLUDED

#include <string.h>
#include <errno.h>

typedef int dc_lib_err;

#define DC_LIB_OK (0)

#define __DC_LIB_ERR_FACTOR (100)
#define __DC_LIB_ERR_BASE (100)
#define __DC_LIB_ERR_GET_ID(error) ((int)((error) - __DC_LIB_ERR_BASE) / __DC_LIB_ERR_FACTOR)
#define __DC_LIB_ERR_THROW(error_id, arg) ((error_id) * __DC_LIB_ERR_FACTOR + (arg) + __DC_LIB_ERR_BASE)
#define __DC_LIB_ERR_IS(error_id, error) (__DC_LIB_ERR_GET_ID(error) == (error_id))

#define DC_LIB_ERR_GET_ARG(error) (((error) - __DC_LIB_ERR_BASE) % (__DC_LIB_ERR_GET_ID(error) * __DC_LIB_ERR_FACTOR))

size_t __dc_lib_err_strlen(int arg, size_t error_message_len, size_t (*arg_strlen)(int));
errno_t __dc_lib_err_strcpy_s(int arg, const char* error_message, errno_t (*arg_strcat_s)(int, char*, rsize_t), char* message, rsize_t size);

#endif
