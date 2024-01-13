#ifndef _DCL_LOGS_H_INCLUDED_
#define _DCL_LOGS_H_INCLUDED_

#include "config/dcl.h"
#include "uc/logs.h"

#if !defined(DCL_LOG_PREFIX)
	#define DCL_LOG_PREFIX DCL_LOG_PREFIX_DEFAULT
#endif

#if !defined(DCL_LOG_TYPES)
	#define DCL_LOG_TYPES DCL_LOG_TYPE_DEFAULT
#endif

#if !defined(DCL_LOG_OPTS)
	#define DCL_LOG_OPTS DCL_LOG_OPT_DEFAULT
#endif

#define DCL_LOG(type_name, message) \
	uc_log(DCL_LOG_PREFIX, DCL_LOG_TYPES, DCL_LOG_OPTS, UC_LOG_TYPE_##type_name, message)

#endif
