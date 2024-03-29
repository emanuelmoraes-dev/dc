#ifndef _UC_CONFIG_OUTPUT_H_INCLUDED_
#define _UC_CONFIG_OUTPUT_H_INCLUDED_

// DCC TIME [stderr(stderr(INFO|WARN|ERR)] MESSAGE

#include "uc/logs/args.h"

// realtime config

#define UC_LOG_TYPE_DEFAULT UC_LOG_TYPE_INFO|UC_LOG_TYPE_WARN|UC_LOG_TYPE_ERR
#define UC_LOG_OPT_DEFAULT UC_LOG_OPT_TIME
#define UC_LOG_PREFIX_DEFAULT "UC"

// compile config

#define UC_LOG_TIME_FORMAT_DEFAULT "%Y-%m-%d %H:%M:%S"
#define UC_LOG_TIME_BUFFSIZE_DEFAULT 64

#endif
