#ifndef DC_ERRORS_BASE_H_INCLUDED
#define DC_ERRORS_BASE_H_INCLUDED

#define DC_OK (0)

#define __DC_ERR_BASE (100)
#define __DC_ERR_THROW(error_id, arg) ((error_id) * __DC_ERR_BASE + (arg))
#define __DC_ERR_IS(error_id, error) ((error) / ((error_id) * __DC_ERR_BASE) == (error_id))
#define __DC_ERR_GET_ARG(error_id, error) ((error) % ((error_id) * __DC_ERR_BASE))

typedef int dc_error;

#endif