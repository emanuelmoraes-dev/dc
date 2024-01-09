#ifndef DCC_LOGS_H_INCLUDED
#define DCC_LOGS_H_INCLUDED

#include "config/dcc.h"
#include "uc/logs.h"

void log_info(const char* message);
void log_warn(const char* message);
void log_err(const char* message);
void log_debug(const char* message);

#if !defined(DCC_LOG_TYPES)
	#define DCC_LOG_TYPES DCC_LOG_TYPE_DEFAULT
#endif

#if !defined(DCC_LOG_OPTS)
	#define DCC_LOG_OPTS DCC_LOG_OPT_DEFAULT
#endif

#endif
