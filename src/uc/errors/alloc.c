#include "uc/errors/alloc.h"

size_t uc_err_arg_strlen_alloc(int arg) {
	switch(arg) {
	case UC_ERR_ARG_ALLOC_HASH_MAP_DATA: return strlen(UC_ERR_ARG_MESSAGE_ALLOC_HASH_MAP_DATA);
	default: return strlen("Unexpected");
	}
}

errno_t uc_err_arg_strcat_s_alloc(int arg, char* message, rsize_t size) {
	switch(arg) {
	case UC_ERR_ARG_ALLOC_HASH_MAP_DATA: return strcpy_s(message, size, UC_ERR_ARG_MESSAGE_ALLOC_HASH_MAP_DATA);
	default: return strcpy_s(message, size, "Unexpected");
	}
}

size_t uc_err_strlen_alloc(int arg) {
	return __uc_err_strlen(arg, strlen(UC_ERR_MESSAGE_ALLOC), uc_err_arg_strlen_alloc);
}

errno_t uc_err_strcpy_s_alloc(int arg, char* message, rsize_t size) {
	return __uc_err_strcpy_s(arg, UC_ERR_MESSAGE_ALLOC, uc_err_arg_strcat_s_alloc, message, size);
}
