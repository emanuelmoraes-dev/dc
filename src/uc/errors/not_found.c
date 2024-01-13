#include "uc/errors/not_found.h"

UC_ERR_IMPL(not_found, 3)

size_t uc_err_arg_strlen_not_found(int arg) {
	switch(arg) {
	case UC_ERR_ARG_NOT_FOUND_HASH_MAP_ITEM: return strlen(UC_ERR_ARG_MESSAGE_NOT_FOUND_HASH_MAP_ITEM);
	default: return strlen("Unexpected");
	}
}

errno_t uc_err_arg_strcat_s_not_found(int arg, char* message, rsize_t size) {
	switch(arg) {
	case UC_ERR_ARG_NOT_FOUND_HASH_MAP_ITEM: return strcat_s(message, size, UC_ERR_ARG_MESSAGE_NOT_FOUND_HASH_MAP_ITEM);
	default: return strcat_s(message, size, "Unexpected");
	}
}

size_t uc_err_strlen_not_found(int arg) {
	return __uc_err_strlen(arg, strlen(UC_ERR_MESSAGE_NOT_FOUND), uc_err_arg_strlen_not_found);
}

errno_t uc_err_strcpy_s_not_found(int arg, char* message, rsize_t size) {
	return __uc_err_strcpy_s(arg, UC_ERR_MESSAGE_NOT_FOUND, uc_err_arg_strcat_s_not_found, message, size);
}
