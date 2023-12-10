#include "uc/errors/relocation.h"

size_t uc_err_arg_strlen_realloc(int arg) {
	switch(arg) {
	case UC_ERR_ARG_REALLOC_HASH_MAP_DATA: return strlen(UC_ERR_ARG_MESSAGE_REALLOC_HASH_MAP_DATA);
	default: return strlen("Unexpected");
	}
}

errno_t uc_err_arg_strcat_s_realloc(int arg, char* message, rsize_t size) {
	switch(arg) {
	case UC_ERR_ARG_REALLOC_HASH_MAP_DATA: return strcpy_s(message, size, UC_ERR_ARG_MESSAGE_REALLOC_HASH_MAP_DATA);
	default: return strcpy_s(message, size, "Unexpected");
	}
}

size_t uc_err_strlen_realloc(int arg) {
	return __uc_err_strlen(arg, strlen(UC_ERR_MESSAGE_REALLOC), uc_err_arg_strlen_realloc);
}

errno_t uc_err_strcpy_s_realloc(int arg, char* message, rsize_t size) {
	return __uc_err_strcpy_s(arg, UC_ERR_MESSAGE_REALLOC, uc_err_arg_strcat_s_realloc, message, size);
}
