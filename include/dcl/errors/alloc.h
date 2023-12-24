#ifndef DCL_ERRORS_ALLOC_H_INCLUDED
#define DCL_ERRORS_ALLOC_H_INCLUDED

#include "dcl/errors/base.h"

#define DCL_ERR_ID_ALLOC (1)
#define DCL_ERR_THROW_ALLOC(arg) __DCL_ERR_THROW(DCL_ERR_ID_ALLOC, arg)
#define DCL_ERR_IS_ALLOC(error) __DCL_ERR_IS(DCL_ERR_ID_ALLOC, error)

#define DCL_ERR_MESSAGE_ALLOC "Error When Allocating"

#define DCL_ERR_ARG_ALLOC_DEP_GRAPH (1)
#define DCL_ERR_ARG_MESSAGE_ALLOC_DEP_GRAPH "Dep Graph"

#define DCL_ERR_ARG_ALLOC_ODDS (2)
#define DCL_ERR_ARG_MESSAGE_ALLOC_ODDS "Odds"

#define DCL_ERR_ARG_ALLOC_ODDS_GRAPH (3)
#define DCL_ERR_ARG_MESSAGE_ALLOC_ODDS_GRAPH "Odds Graph"

#define DCL_ERR_ARG_ALLOC_ODDS_GRAPH_NODE (4)
#define DCL_ERR_ARG_MESSAGE_ALLOC_ODDS_GRAPH_NODE "Odds Graph Node"

#define DCL_ERR_ARG_ALLOC_SENTENCES (5)
#define DCL_ERR_ARG_MESSAGE_ALLOC_SENTENCES "Sentences"

#define DCL_ERR_ARG_ALLOC_CONTENT_GEN (6)
#define DCL_ERR_ARG_MESSAGE_ALLOC_CONTENT_GEN "Content Gen"

size_t dcl_err_arg_strlen_alloc(int arg);
errno_t dcl_err_arg_strcat_s_alloc(int arg, char* message, rsize_t size);

size_t dcl_err_strlen_alloc(int arg);
errno_t dcl_err_strcpy_s_alloc(int arg, char* message, rsize_t size);

#endif
