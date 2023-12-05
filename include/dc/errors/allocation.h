#ifndef DC_ERRORS_ALLOCATION_H_INCLUDED
#define DC_ERRORS_ALLOCATION_H_INCLUDED

#include "dc/errors/base.h"

#define DC_ERR_THROW_ALLOC(arg) __DC_ERR_THROW(2, arg)
#define DC_ERR_IS_ALLOC(error) __DC_ERR_IS(2, error)
#define DC_ERR_GET_ARG_ALLOC(error) __DC_ERR_GET_ARG(2, error)

#define DC_ERR_ARG_ALLOC_ALPHABET 1
#define DC_ERR_ARG_ALLOC_ODDS_GRAPH 2
#define DC_ERR_ARG_ALLOC_SENTENCE 3

#endif
