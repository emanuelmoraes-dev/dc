#ifndef _UC_CONFIG_TRACE_H_INCLUDED_
#define _UC_CONFIG_TRACE_H_INCLUDED_

#include "uc/logs/args.h"

#define UC_LOG_TYPE_DEFAULT UC_LOG_TYPE_INFO|UC_LOG_TYPE_WARN|UC_LOG_TYPE_ERR|UC_LOG_TYPE_DEBUG
#define UC_LOG_OPT_DEFAULT  UC_LOG_OPT_TIME
#define UC_LOG_TIME_FORMAT_DEFAULT  "%Y-%m-%d %H:%M:%S"
#define UC_LOG_TIME_BUFFSIZE_DEFAULT 64
#define UC_LOG_PREFIX_DEFAULT "UC(TRACE)"

#endif
