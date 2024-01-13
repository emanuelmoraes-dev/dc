#ifndef UC_ERRORS_ALLOC_H_INCLUDED
#define UC_ERRORS_ALLOC_H_INCLUDED

#include "uc/errors/base.h"

UC_ERR_DEF(alloc)

#define UC_ERR_MESSAGE_ALLOC "Error When Allocating"

#define UC_ERR_ARG_ALLOC_HASH_MAP_DATA (1)
#define UC_ERR_ARG_MESSAGE_ALLOC_HASH_MAP_DATA "Hash Map Data"

#define UC_ERR_ARG_ALLOC_LINKED_LIST_HEAD (2)
#define UC_ERR_ARG_MESSAGE_ALLOC_LINKED_LIST_HEAD "Linked List Head"

#define UC_ERR_ARG_ALLOC_LINKED_LIST_NEW_ELEMENT (3)
#define UC_ERR_ARG_MESSAGE_ALLOC_LINKED_LIST_NEW_ELEMENT "Linked List New Element"

size_t uc_err_arg_strlen_alloc(int arg);
errno_t uc_err_arg_strcat_s_alloc(int arg, char* message, rsize_t size);

size_t uc_err_strlen_alloc(int arg);
errno_t uc_err_strcpy_s_alloc(int arg, char* message, rsize_t size);

#endif
