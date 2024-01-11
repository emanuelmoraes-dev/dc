#include "dcl/logs.h"

void dcl_log_info(const char* message) {
	uc_log(DCL_LOG_PREFIX, DCL_LOG_TYPES, DCL_LOG_OPTS, UC_LOG_TYPE_INFO, message);
}

void dcl_log_warn(const char* message) {
	uc_log(DCL_LOG_PREFIX, DCL_LOG_TYPES, DCL_LOG_OPTS, UC_LOG_TYPE_WARN, message);
}

void dcl_log_err(const char* message) {
	uc_log(DCL_LOG_PREFIX, DCL_LOG_TYPES, DCL_LOG_OPTS, UC_LOG_TYPE_ERR, message);
}

void dcl_log_debug(const char* message) {
	uc_log(DCL_LOG_PREFIX, DCL_LOG_TYPES, DCL_LOG_OPTS, UC_LOG_TYPE_DEBUG, message);
}
