#ifndef DC_ERRORS_H_INCLUDED
#define DC_ERRORS_H_INCLUDED

#include <string.h>

#include "dc/errors/base.h"
#include "dc/errors/errno.h"
#include "dc/errors/allocation.h"
#include "dc/errors/index_out.h"

#define __DC_ERR_STRLEN_ARG(error, arg) (\
    DC_ERR_IS_ALLOC(error) ? DC_ERR_STRLEN_ALLOC(arg) : (\
    DC_ERR_IS_INDEX_OUT(error) ? DC_ERR_STRLEN_INDEX_OUT(arg) : (\
    strlen("Unexpected")))\
)

#define __DC_ERR_STRCPY_ARG(error, arg, message) (\
    DC_ERR_IS_ALLOC(error) ? DC_ERR_STRCPY_ALLOC(arg, message) : (\
    DC_ERR_IS_INDEX_OUT(error) ? DC_ERR_STRCPY_INDEX_OUT(arg, message) : (\
    strcpy(message, "Unexpected")))\
)

#define DC_ERR_STRLEN(error) __DC_ERR_STRLEN_ARG(error, DC_ERR_GET_ARG(error))
#define DC_ERR_STRCPY(error, message) __DC_ERR_STRCPY_ARG(error, DC_ERR_GET_ARG(error), message)

#endif
