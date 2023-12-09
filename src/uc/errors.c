#include "uc/errors.h"

size_t uc_err_strlen(uc_err error) {
	return strlen("Unexpected");
}

errno_t uc_err_strcpy_s(uc_err error, char* message, rsize_t size) {
	return strcpy_s(message, size, "Unexpected");
}
