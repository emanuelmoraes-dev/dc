#ifndef DC_LIB_ERRORS_H_INCLUDED
#define DC_LIB_ERRORS_H_INCLUDED

#include <string.h>

#include "dc/lib/errors/base.h"
#include "dc/lib/errors/errno.h"
#include "dc/lib/errors/allocation.h"
#include "dc/lib/errors/index_out.h"

#define __DC_LIB_ERR_STRLEN_ARG(error, arg) (\
    DC_LIB_ERR_IS_ALLOC(error) ? DC_LIB_ERR_STRLEN_ALLOC(arg) : (\
    DC_LIB_ERR_IS_INDEX_OUT(error) ? DC_LIB_ERR_STRLEN_INDEX_OUT(arg) : (\
    strlen("Unexpected")))\
)

#define __DC_LIB_ERR_STRCPY_ARG(error, arg, message) (\
    DC_LIB_ERR_IS_ALLOC(error) ? DC_LIB_ERR_STRCPY_ALLOC(arg, message) : (\
    DC_LIB_ERR_IS_INDEX_OUT(error) ? DC_LIB_ERR_STRCPY_INDEX_OUT(arg, message) : (\
    strcpy(message, "Unexpected")))\
)

#define DC_LIB_ERR_STRLEN(error) __DC_LIB_ERR_STRLEN_ARG(error, DC_LIB_ERR_GET_ARG(error))
#define DC_LIB_ERR_STRCPY(error, message) __DC_LIB_ERR_STRCPY_ARG(error, DC_LIB_ERR_GET_ARG(error), message)

#endif
