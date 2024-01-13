#ifndef UC_ERRORS_REALLOC_H_INCLUDED
#define UC_ERRORS_REALLOC_H_INCLUDED

#include "uc/errors/base.h"

UC_ERR_DEF(realloc)

#define UC_ERR_MESSAGE_REALLOC "Error When Relocating"

#define UC_ERR_ARG_REALLOC_HASH_MAP_DATA (1)
#define UC_ERR_ARG_MESSAGE_REALLOC_HASH_MAP_DATA "Hash Map Data"

size_t uc_err_arg_strlen_realloc(int arg);
errno_t uc_err_arg_strcat_s_realloc(int arg, char* message, rsize_t size);

size_t uc_err_strlen_realloc(int arg);
errno_t uc_err_strcpy_s_realloc(int arg, char* message, rsize_t size);

#endif
