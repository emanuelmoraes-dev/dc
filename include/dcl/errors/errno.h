#ifndef DCL_ERRORS_ERRNO_H_INCLUDED
#define DCL_ERRORS_ERRNO_H_INCLUDED

#include <string.h>
#include <errno.h>
#include "dcl/errors/base.h"

#define DCL_ERR_ID_ERRNO (0)
#define DCL_ERR_THROW_ERRNO(arg) __DCL_ERR_THROW(DC_ERR_ID_ERRNO, arg)
#define DCL_ERR_IS_ERRNO(error) __DCL_ERR_IS(DC_ERR_ID_ERRNO, error)

#endif
