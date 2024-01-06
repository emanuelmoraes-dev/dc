#include "uc/logs.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>

#if defined(_WIN32) && defined(__cplusplus_winrt)
	#define __GETENV_S__(len, buff, buff_size, env_name) _dupenv_s(&buff, &buff_size, env_name)
#else
	#define __GETENV_S__(len, buff, buff_size, env_name) getenv_s(len, buff, buff_size, env_name)
#endif

errno_t __getenv_s(char* buff, rsize_t buff_size, const char* env_name) {
	size_t len;
	return __GETENV_S__(&len, buff, buff_size, env_name);
}

int __env_int(const char* env_name, int default_value, int buff_size);

void uc_log_env_opts(int type_verify, int type, const char* message) {
	int opts = __env_int("UC_LOG_OPTS", UC_LOG_OPT_DEFAULT, 10);
	return uc_log(type_verify, opts, type, message);
}

void uc_log_env_verify(int opts, int type, const char* message) {
	int type_verify = __env_int("UC_LOG_TYPES", UC_LOG_TYPE_DEFAULT, 10);
	return uc_log(type_verify, opts, type, message);
}

void uc_log_env(int type, const char* message) {
	int type_verify = __env_int("UC_LOG_TYPES", UC_LOG_TYPE_DEFAULT, 10);
	int opts = __env_int("UC_LOG_OPTS", UC_LOG_OPT_DEFAULT, 10);
	return uc_log(type_verify, opts, type, message);
}

void __time_message(unsigned long long* len, char* time_buff, size_t time_buff_size);
void __type_message(unsigned long long* len, char* type_buff, size_t type_buff_size, int type);
FILE* __file(int opts, int type);
void uc_log(int type_verify, int opts, int type, const char* message) {
	bool verify = !!(type&type_verify);
	if (!verify) {
		return;
	}

	const char endl[] = "\n";
	unsigned long long ends_len = 1;
	unsigned long long endl_len = strlen(endl);
	unsigned long long message_len = strlen(message);
	unsigned long long size = ends_len + endl_len + message_len;

	const char space[] = " ";
	unsigned long long space_len = strlen(space);

	bool opt_time = !!(opts&UC_LOG_OPT_TIME);
	char stime[64] = "";
	unsigned long long time_len = 0;
	if (opt_time) {
		__time_message(&time_len, stime, sizeof(stime));

		if (time_len > 0) {
			size += time_len + space_len;
		}
	}

	char stype[6] = "";
	unsigned long long type_len = 0;
	__type_message(&type_len, stype, sizeof(stype), type);
	if (type_len > 0) {
		size += type_len + space_len;
	}

	char output[size];
	size_t output_size = sizeof(char) * size;

	if (!output_size) {
		return;
	}

	*output = '\0';

	if (time_len > 0) {
		errno_t error = strcat_s(output, output_size, stime);
		if (error) {
			return;
		}
		error = strcat_s(output, output_size, space);
		if (error) {
			return;
		}
	}

	if (type_len > 0) {
		errno_t error = strcat_s(output, output_size, stype);
		if (error) {
			return;
		}
		error = strcat_s(output, output_size, space);
		if (error) {
			return;
		}
	}

	if (message_len > 0) {
		errno_t error = strcat_s(output, output_size, message);
		if (error) {
			return;
		}
		error = strcat_s(output, output_size, endl);
		if (error) {
			return;
		}
	}

	FILE* file = __file(opts, type);

	if (file == NULL) {
		return;
	}

	fprintf(file, "%s", output);
}

void __time_message(unsigned long long* len, char* time_buff, size_t time_buff_size) {
	if (time_buff_size < 1) {
		*len = 0;
		return;
	}

	time_t t = time(NULL);
	struct tm tm;
	errno_t error = localtime_s(&tm, &t);

	if (error) {
		*len = 0;
		if (time_buff_size > 0) {
			*time_buff = '\0';
		}
		return;
	}

	size_t size = strftime(time_buff, time_buff_size, "%c", &tm);

	if (!size) {
		*len = 0;
		if (time_buff_size > 0) {
			*time_buff = '\0';
		}
		return;
	}

	*len = size - 1;
}

void __type_message(unsigned long long* len, char* type_buff, size_t type_buff_size, int type) {
	if (type_buff_size < 1) {
		*len = 0;
		return;
	}

	bool tinfo = !!(type&UC_LOG_TYPE_INFO);
	bool twarn = !!(type&UC_LOG_TYPE_WARN);
	bool terr = !!(type&UC_LOG_TYPE_ERR);
	bool tdebug = !!(type&UC_LOG_TYPE_DEBUG);
	errno_t error = 0;
	if (tinfo) {
		const char stype[] = "[INFO]";
		error = strcpy_s(type_buff, type_buff_size, stype);
	} else if (twarn) {
		const char stype[] = "[WARN]";
		error = strcpy_s(type_buff, type_buff_size, stype);
	} else if (terr) {
		const char stype[] = "[ERROR]";
		error = strcpy_s(type_buff, type_buff_size, stype);
	} else if (tdebug) {
		const char stype[] = "[DEBUG]";
		error = strcpy_s(type_buff, type_buff_size, stype);
	}

	if (error) {
		*len = 0;
		if (type_buff_size > 0) {
			*type_buff = '\0';
		}
	}

	*len = strlen(type_buff);
}

FILE* __file(int opts, int type) {
	bool opt_stdout = !!(opts&UC_LOG_OPT_STDOUT);
	bool opt_err_stdout = !!(opts&UC_LOG_OPT_ERR_STDOUT);
	bool opt_err_stderr = !!(opts&UC_LOG_OPT_ERR_STDERR);
	bool type_err = !!(type&UC_LOG_TYPE_ERR);

	if (type_err && opt_err_stdout != opt_err_stderr) {
		opt_stdout = opt_err_stdout;
	}

	if (opt_stdout) {
		return stdout;
	}

	return stderr;
}

int __env_int(const char* env_name, int default_value, int buff_size) {
	if (buff_size < 1) {
		return default_value;
	}

	char str_env[buff_size];
	*str_env = '\0';
	errno_t error = __getenv_s(str_env, sizeof(str_env), env_name);
	if (error || strlen(str_env) == 0) {
		return default_value;
	}

	char* ends = NULL;
	int env_int = strtol(str_env, &ends, 0);
	if (ends == NULL || *ends != '\0') {
		return default_value;
	}

	return env_int;
}
