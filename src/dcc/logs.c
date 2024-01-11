#include "dcc/logs.h"
#include "uc/logs.h"

void log_info(const char* message) {
	uc_log(DCC_LOG_PREFIX, DCC_LOG_TYPES, DCC_LOG_OPTS, UC_LOG_TYPE_INFO, message);
}

void log_warn(const char* message) {
	uc_log(DCC_LOG_PREFIX, DCC_LOG_TYPES, DCC_LOG_OPTS, UC_LOG_TYPE_WARN, message);
}

void log_err(const char* message) {
	uc_log(DCC_LOG_PREFIX, DCC_LOG_TYPES, DCC_LOG_OPTS, UC_LOG_TYPE_ERR, message);
}

void log_debug(const char* message) {
	uc_log(DCC_LOG_PREFIX, DCC_LOG_TYPES, DCC_LOG_OPTS, UC_LOG_TYPE_DEBUG, message);
}
