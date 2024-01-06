#ifndef UC_LOGS_H_INCLUDED
#define UC_LOGS_H_INCLUDED

#define UC_LOG_TYPE_NONE    (0b0000)
#define UC_LOG_TYPE_INFO    (0b1000)
#define UC_LOG_TYPE_WARN    (0b0100)
#define UC_LOG_TYPE_ERR     (0b0010)
#define UC_LOG_TYPE_DEBUG   (0b0001)
#define UC_LOG_TYPE_DEFAULT UC_LOG_TYPE_NONE

#define UC_LOG_OPT_NONE       (0b0000)
#define UC_LOG_OPT_TIME       (0b1000)
#define UC_LOG_OPT_STDOUT     (0b0100)
#define UC_LOG_OPT_ERR_STDOUT (0b0010)
#define UC_LOG_OPT_ERR_STDERR (0b0001)
#define UC_LOG_OPT_DEFAULT    UC_LOG_OPT_TIME

#if defined(UC_LOG_TYPES) && defined(UC_LOG_OPTS)

	#define UC_LOG(type_name, message) \
		uc_log(UC_LOG_TYPES, UC_LOG_OPTS, UC_LOG_TYPE_##type_name, message)

#elif defined(UC_LOG_TYPES)

	#define UC_LOG(type_name, message) \
		uc_log_env_opts(UC_LOG_TYPES, UC_LOG_TYPE_##type_name, message)

#elif defined(UC_LOG_OPTS)

	#define UC_LOG(type_name, message) \
		uc_log_env_verify(UC_LOG_OPTS, UC_LOG_TYPE_##type_name, message)

#else

	#define UC_LOG(type_name, message) \
		uc_log_env(UC_LOG_TYPE_##type_name, message)

#endif

void uc_log(int type_verify, int opts, int type, const char* message);
void uc_log_env_opts(int type_verify, int type, const char* message);
void uc_log_env_verify(int opts, int type, const char* message);
void uc_log_env(int type, const char* message);

#endif