#ifndef DC_LIB_ERRORS_ALLOCATION_H_INCLUDED
#define DC_LIB_ERRORS_ALLOCATION_H_INCLUDED

#include "dc/lib/errors/base.h"

#define DC_LIB_ERR_ID_ALLOC (2)
#define DC_LIB_ERR_THROW_ALLOC(arg) __DC_LIB_ERR_THROW(DC_LIB_ERR_ID_ALLOC, arg)
#define DC_LIB_ERR_IS_ALLOC(error) __DC_LIB_ERR_IS(DC_LIB_ERR_ID_ALLOC, error)

#define __DC_LIB_ERR_MESSAGE_ALLOC "Error When Allocating: "
#define DC_LIB_ERR_STRLEN_ALLOC(arg) __DC_LIB_ERR_STRLEN(__DC_LIB_ERR_MESSAGE_ALLOC, DC_LIB_ERR_ARG_STR_ALLOC(arg))
#define DC_LIB_ERR_STRCPY_ALLOC(arg, message) __DC_LIB_ERR_STRCPY(__DC_LIB_ERR_MESSAGE_ALLOC, DC_LIB_ERR_ARG_STR_ALLOC(arg), message)

#define DC_LIB_ERR_ARG_ALLOC_ALPHABET (1)
#define DC_LIB_ERR_ARG_ALLOC_ODDS_GRAPH (2)
#define DC_LIB_ERR_ARG_ALLOC_SENTENCE (3)

#define DC_LIB_ERR_ARG_STR_ALLOC(arg) (\
    (arg) == DC_LIB_ERR_ARG_ALLOC_ALPHABET ? "Alphabet" : (\
    (arg) == DC_LIB_ERR_ARG_ALLOC_ODDS_GRAPH ? "Odds Graph" : (\
    (arg) == DC_LIB_ERR_ARG_ALLOC_SENTENCE ? "Sentence" : (\
    "Unexpected")))\
)

#endif
