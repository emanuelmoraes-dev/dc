#ifndef DC_ERRORS_ERRNO_H_INCLUDED
#define DC_ERRORS_ERRNO_H_INCLUDED

#include "dc/errors/base.h"

#define DC_ERR_THROW_ERRNO(arg) __DC_ERR_THROW(1, arg)
#define DC_ERR_IS_ERRNO(error) __DC_ERR_IS(1, error)
#define DC_ERR_GET_ARG_ERRNO(error) __DC_ERR_GET_ARG(1, error)

#endif
