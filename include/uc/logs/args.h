#ifndef _UC_LOGS_CONFIG_H_INCLUDED_
#define _UC_LOGS_CONFIG_H_INCLUDED_

#define UC_LOG_TYPE_NONE    (0b0000)
#define UC_LOG_TYPE_INFO    (0b1000)
#define UC_LOG_TYPE_WARN    (0b0100)
#define UC_LOG_TYPE_ERR     (0b0010)
#define UC_LOG_TYPE_DEBUG   (0b0001)

#define UC_LOG_OPT_NONE       (0b0000)
#define UC_LOG_OPT_TIME       (0b1000)
#define UC_LOG_OPT_STDOUT     (0b0100)
#define UC_LOG_OPT_ERR_STDERR (0b0010)
#define UC_LOG_OPT_ERR_STDOUT (0b0001)

#endif
