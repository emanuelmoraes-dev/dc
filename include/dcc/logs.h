#ifndef _DCC_LOGS_H_INCLUDED_
#define _DCC_LOGS_H_INCLUDED_

#include "config/dcc.h"
#include "uc/logs.h"

#if !defined(DCC_LOG_PREFIX)
	#define DCC_LOG_PREFIX DCC_LOG_PREFIX_DEFAULT
#endif

#if !defined(DCC_LOG_TYPES)
	#define DCC_LOG_TYPES DCC_LOG_TYPE_DEFAULT
#endif

#if !defined(DCC_LOG_OPTS)
	#define DCC_LOG_OPTS DCC_LOG_OPT_DEFAULT
#endif

#define LOG(type_name, message) \
	uc_log(DCC_LOG_PREFIX, DCC_LOG_TYPES, DCC_LOG_OPTS, UC_LOG_TYPE_##type_name, message)

#endif
