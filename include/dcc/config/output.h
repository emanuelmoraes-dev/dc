#ifndef _DCC_CONFIG_OUTPUT_H_INCLUDED_
#define _DCC_CONFIG_OUTPUT_H_INCLUDED_

// DCC TIME [stdout(INFO)|stderr(WARN|ERR)] MESSAGE

#include "uc/logs/args.h"

// realtime config

#define DCC_LOG_TYPE_DEFAULT UC_LOG_TYPE_INFO|UC_LOG_TYPE_WARN|UC_LOG_TYPE_ERR
#define DCC_LOG_OPT_DEFAULT UC_LOG_OPT_TIME|UC_LOG_OPT_INFO_STDOUT
#define DCC_LOG_PREFIX_DEFAULT "DCC"

#endif
