#ifndef DC_ERRORS_INDEX_OUT_H_INCLUDED
#define DC_ERRORS_INDEX_OUT_H_INCLUDED

#include "dc/errors/base.h"

#define DC_ERR_ID_INDEX_OUT (3)
#define DC_ERR_THROW_INDEX_OUT(arg) __DC_ERR_THROW(DC_ERR_ID_INDEX_OUT, arg)
#define DC_ERR_IS_INDEX_OUT(error) __DC_ERR_IS(DC_ERR_ID_INDEX_OUT, error)

#define __DC_ERR_MESSAGE_INDEX_OUT "Index Out Of Bounds: "
#define DC_ERR_STRLEN_INDEX_OUT(arg) __DC_ERR_STRLEN(__DC_ERR_MESSAGE_INDEX_OUT, DC_ERR_ARG_STR_INDEX_OUT(arg))
#define DC_ERR_STRCPY_INDEX_OUT(arg, message) __DC_ERR_STRCPY(__DC_ERR_MESSAGE_INDEX_OUT, DC_ERR_ARG_STR_INDEX_OUT(arg), message)

#define DC_ERR_ARG_INDEX_OUT_ALPHABET (1)

#define DC_ERR_ARG_STR_INDEX_OUT(arg) (\
    (arg) == DC_ERR_ARG_INDEX_OUT_ALPHABET ? "Alphabet" :(\
    "Unexpected")\
)

#endif
