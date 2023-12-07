#ifndef DC_ERRORS_ERRNO_H_INCLUDED
#define DC_ERRORS_ERRNO_H_INCLUDED

#include <string.h>
#include <errno.h>
#include "dc/errors/base.h"

#define DC_ERR_ID_ERRNO (1)
#define DC_ERR_THROW_ERRNO(arg) __DC_ERR_THROW(DC_ERR_ID_ERRNO, arg)
#define DC_ERR_IS_ERRNO(error) __DC_ERR_IS(DC_ERR_ID_ERRNO, error)

#endif
