#ifndef DC_LIB_ERRORS_ERRNO_H_INCLUDED
#define DC_LIB_ERRORS_ERRNO_H_INCLUDED

#include <string.h>
#include <errno.h>
#include "dc/lib/errors/base.h"

#define DC_LIB_ERR_ID_ERRNO (0)
#define DC_LIB_ERR_THROW_ERRNO(arg) __DC_LIB_ERR_THROW(DC_ERR_ID_ERRNO, arg)
#define DC_LIB_ERR_IS_ERRNO(error) __DC_LIB_ERR_IS(DC_ERR_ID_ERRNO, error)

#endif
