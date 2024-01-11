#ifndef DCL_LOGS_H_INCLUDED
#define DCL_LOGS_H_INCLUDED

#include "config/dcl.h"
#include "uc/logs.h"

#if !defined(DCL_LOG_TYPES)
	#define DCL_LOG_TYPES DCL_LOG_TYPE_DEFAULT
#endif

#if !defined(DCL_LOG_OPTS)
	#define DCL_LOG_OPTS DCL_LOG_OPT_DEFAULT
#endif

#if !defined(DCL_LOG_PREFIX)
	#define DCL_LOG_PREFIX DCL_LOG_PREFIX_DEFAULT
#endif

void dcl_log_info(const char* message);
void dcl_log_warn(const char* message);
void dcl_log_err(const char* message);
void dcl_log_debug(const char* message);

#endif
