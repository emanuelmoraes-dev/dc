#include "uc/errors/empty.h"

size_t uc_err_arg_strlen_empty(int arg) {
	switch(arg) {
	case UC_ERR_ARG_EMPTY_HASH_MAP: return strlen(UC_ERR_ARG_MESSAGE_EMPTY_HASH_MAP);
	default: return strlen("Unexpected");
	}
}

errno_t uc_err_arg_strcat_s_empty(int arg, char* message, rsize_t size) {
	switch(arg) {
	case UC_ERR_ARG_EMPTY_HASH_MAP: return strcpy_s(message, size, UC_ERR_ARG_MESSAGE_EMPTY_HASH_MAP);
	default: return strcpy_s(message, size, "Unexpected");
	}
}

size_t uc_err_strlen_empty(int arg) {
	return __uc_err_strlen(arg, strlen(UC_ERR_MESSAGE_EMPTY), uc_err_arg_strlen_empty);
}

errno_t uc_err_strcpy_s_empty(int arg, char* message, rsize_t size) {
	return __uc_err_strcpy_s(arg, UC_ERR_MESSAGE_EMPTY, uc_err_arg_strcat_s_empty, message, size);
}
