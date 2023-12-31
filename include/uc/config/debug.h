#ifndef UC_CONFIG_DEBUG_H_INCLUDED
#define UC_CONFIG_DEBUG_H_INCLUDED

#include "uc/logs/args.h"

#define UC_LOG_TYPE_DEFAULT UC_LOG_TYPE_INFO|UC_LOG_TYPE_WARN|UC_LOG_TYPE_ERR|UC_LOG_TYPE_DEBUG
#define UC_LOG_OPT_DEFAULT  UC_LOG_OPT_TIME
#define UC_LOG_TIME_FORMAT_DEFAULT  "%Y-%m-%d %H:%M:%S"

#endif
