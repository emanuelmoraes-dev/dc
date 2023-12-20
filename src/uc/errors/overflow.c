#include "uc/errors/overflow.h"

size_t uc_err_arg_strlen_overflow(int arg) {
	switch(arg) {
	case UC_ERR_ARG_OVERFLOW_LARGE: return strlen(UC_ERR_ARG_MESSAGE_OVERFLOW_LARGE);
	case UC_ERR_ARG_OVERFLOW_SMALL: return strlen(UC_ERR_ARG_MESSAGE_OVERFLOW_SMALL);
	case UC_ERR_ARG_OVERFLOW_LARGE_HASH_MAP_CAPACITY: return strlen(UC_ERR_ARG_MESSAGE_OVERFLOW_LARGE_HASH_MAP_CAPACITY);
	default: return strlen("Unexpected");
	}
}

errno_t uc_err_arg_strcat_s_overflow(int arg, char* message, rsize_t size) {
	switch(arg) {
	case UC_ERR_ARG_OVERFLOW_LARGE: return strcat_s(message, size, UC_ERR_ARG_MESSAGE_OVERFLOW_LARGE);
	case UC_ERR_ARG_OVERFLOW_SMALL: return strcat_s(message, size, UC_ERR_ARG_MESSAGE_OVERFLOW_SMALL);
	case UC_ERR_ARG_OVERFLOW_LARGE_HASH_MAP_CAPACITY: return strcat_s(message, size, UC_ERR_ARG_MESSAGE_OVERFLOW_LARGE_HASH_MAP_CAPACITY);
	default: return strcat_s(message, size, "Unexpected");
	}
}

size_t uc_err_strlen_overflow(int arg) {
	return __uc_err_strlen(arg, strlen(UC_ERR_MESSAGE_OVERFLOW), uc_err_arg_strlen_overflow);
}

errno_t uc_err_strcpy_s_overflow(int arg, char* message, rsize_t size) {
	return __uc_err_strcpy_s(arg, UC_ERR_MESSAGE_OVERFLOW, uc_err_arg_strcat_s_overflow, message, size);
}
