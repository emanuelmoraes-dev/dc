#ifndef DC_ERRORS_ALLOCATION_H_INCLUDED
#define DC_ERRORS_ALLOCATION_H_INCLUDED

#include "dc/errors/base.h"

#define DC_ERR_ID_ALLOC (2)
#define DC_ERR_THROW_ALLOC(arg) __DC_ERR_THROW(DC_ERR_ID_ALLOC, arg)
#define DC_ERR_IS_ALLOC(error) __DC_ERR_IS(DC_ERR_ID_ALLOC, error)

#define __DC_ERR_MESSAGE_ALLOC "Error When Allocating: "
#define DC_ERR_STRLEN_ALLOC(arg) __DC_ERR_STRLEN(__DC_ERR_MESSAGE_ALLOC, DC_ERR_ARG_STR_ALLOC(arg))
#define DC_ERR_STRCPY_ALLOC(arg, message) __DC_ERR_STRCPY(__DC_ERR_MESSAGE_ALLOC, DC_ERR_ARG_STR_ALLOC(arg), message)

#define DC_ERR_ARG_ALLOC_ALPHABET (1)
#define DC_ERR_ARG_ALLOC_ODDS_GRAPH (2)
#define DC_ERR_ARG_ALLOC_SENTENCE (3)

#define DC_ERR_ARG_STR_ALLOC(arg) (\
    (arg) == DC_ERR_ARG_ALLOC_ALPHABET ? "Alphabet" : (\
    (arg) == DC_ERR_ARG_ALLOC_ODDS_GRAPH ? "Odds Graph" : (\
    (arg) == DC_ERR_ARG_ALLOC_SENTENCE ? "Sentence" : (\
    "Unexpected")))\
)

#endif
