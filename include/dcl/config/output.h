#ifndef _DCL_CONFIG_OUTPUT_H_INCLUDED_
#define _DCL_CONFIG_OUTPUT_H_INCLUDED_

// DCL TIME [stderr(INFO|WARN|ERR)] MESSAGE

#include "uc/logs/args.h"

// realtime config

#define DCL_LOG_TYPE_DEFAULT UC_LOG_TYPE_INFO|UC_LOG_TYPE_WARN|UC_LOG_TYPE_ERR
#define DCL_LOG_OPT_DEFAULT UC_LOG_OPT_TIME
#define DCL_LOG_PREFIX_DEFAULT "DCL"

#endif
