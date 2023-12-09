#ifndef DC_ERRORS_BASE_H_INCLUDED
#define DC_ERRORS_BASE_H_INCLUDED

#include <string.h>

typedef int dc_lib_err;

#define DC_LIB_OK (0)

#define __DC_LIB_ERR_BASE (100)
#define __DC_LIB_ERR_GET_ID(error) ((int)(error) / __DC_LIB_ERR_BASE)
#define __DC_LIB_ERR_THROW(error_id, arg) ((error_id) * __DC_LIB_ERR_BASE + (arg))
#define __DC_LIB_ERR_IS(error_id, error) (__DC_ERR_GET_ID(error) == (error_id))
#define __DC_LIB_ERR_STRLEN(error_message, arg_message) (strlen(error_message) + strlen(arg_message))
#define __DC_LIB_ERR_STRCPY(error_message, arg_message, message) (strcat(strcpy(message, error_message), arg_message))

#define DC_LIB_ERR_GET_ARG(error) ((error) % (__DC_LIB_ERR_GET_ID(error) * __DC_LIB_ERR_BASE))

#endif
