#ifndef UC_LOGS_H_INCLUDED
#define UC_LOGS_H_INCLUDED

#include "config/uc.h"
#include <stddef.h>
#include <string.h>

#if !defined(UC_LOG_TYPES)
	#define UC_LOG_TYPES UC_LOG_TYPE_DEFAULT
#endif

#if !defined(UC_LOG_OPTS)
	#define UC_LOG_OPTS UC_LOG_OPT_DEFAULT
#endif

#if !defined(UC_LOG_TIME_FORMAT)
	#define UC_LOG_TIME_FORMAT UC_LOG_TIME_FORMAT_DEFAULT
#endif

#define UC_LOG_BUFFER(buff_name, format_name, format, args_buff_size) \
	char format_name[] = format;\
	char buff_name[strlen(format_name) + (args_buff_size) + 1]

void uc_log_format(char* buff, size_t buff_size, const char* format, ...);
void uc_log_info(const char* message);
void uc_log_warn(const char* message);
void uc_log_err(const char* message);
void uc_log_debug(const char* message);
void uc_log(int verify, int opts, int type, const char* message);
void uc_log_ostr(int verify, const char* opts_str, int type, const char* message);
void uc_log_vstr(const char* verify_str, int opts, int type, const char* message);
void uc_log_vostr(const char* verify_str, const char* opts_str, int type, const char* message);

#endif
