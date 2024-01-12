#include "uc/logs.h"
#include <stdio.h>
#include <string.h>
#include <stdbool.h>
#include <time.h>
#include <stdlib.h>
#include <stdarg.h>
#include <errno.h>

void uc_log_format(char* buff, size_t buff_size, const char* format, ...) {
	va_list args;
	va_start(args, format);
	vsnprintf(buff, buff_size, format, args);
	va_end(args);
}

int __str_to_int(const char* str, int default_value);

void uc_log_ostr(const char* prefix, int verify, const char* opts_str, int type, const char* message) {
	int opts = __str_to_int(opts_str, UC_LOG_OPTS);
	return uc_log(prefix, verify, opts, type, message);
}

void uc_log_vstr(const char* prefix, const char* verify_str, int opts, int type, const char* message) {
	int verify = __str_to_int(verify_str, UC_LOG_TYPES);
	return uc_log(prefix, verify, opts, type, message);
}

void uc_log_vostr(const char* prefix, const char* verify_str, const char* opts_str, int type, const char* message) {
	int verify = __str_to_int(verify_str, UC_LOG_TYPES);
	int opts = __str_to_int(opts_str, UC_LOG_OPTS);
	return uc_log(prefix, verify, opts, type, message);
}

void __time_message(unsigned long long* len, char* time_buff, size_t time_buff_size);
void __type_message(unsigned long long* len, char* type_buff, size_t type_buff_size, int type);
FILE* __file(int opts, int type);
void uc_log(const char* prefix, int verify, int opts, int type, const char* message) {
	bool type_verify = !!(type&verify);
	if (!type_verify) {
		return;
	}

	unsigned long long ends_len = 1;
	unsigned long long message_len = strlen(message);
	unsigned long long size = ends_len + message_len;

	const char space[] = " ";
	unsigned long long space_len = strlen(space);

	if (prefix != NULL && *prefix != '\0') {
		size += strlen(prefix) + space_len;
	}

	bool opt_time = !!(opts&UC_LOG_OPT_TIME);
	char stime[UC_LOG_TIME_BUFFSIZE] = "";
	unsigned long long time_len = 0;
	if (opt_time) {
		__time_message(&time_len, stime, sizeof(stime));

		if (time_len > 0) {
			size += time_len + space_len;
		}
	}

	char stype[8] = "";
	unsigned long long type_len = 0;
	__type_message(&type_len, stype, sizeof(stype), type);
	if (type_len > 0) {
		size += type_len + space_len;
	}

	char output[size];
	size_t output_size = sizeof(char) * size;

	FILE* file = __file(opts, type);

	if (file == NULL) {
		file = stderr;
	}

	if (!output_size) {
		fprintf(stderr, "%s\n", message);
		return;
	}

	*output = '\0';

	if (prefix != NULL && *prefix != '\0') {
		errno_t error = strcat_s(output, output_size, prefix);
		if (error) {
			fprintf(file, "%s\n", message);
			return;
		}
		error = strcat_s(output, output_size, space);
		if (error) {
			fprintf(file, "%s\n", message);
			return;
		}
	}

	if (time_len > 0) {
		errno_t error = strcat_s(output, output_size, stime);
		if (error) {
			fprintf(file, "%s\n", message);
			return;
		}
		error = strcat_s(output, output_size, space);
		if (error) {
			fprintf(file, "%s\n", message);
			return;
		}
	}

	if (type_len > 0) {
		errno_t error = strcat_s(output, output_size, stype);
		if (error) {
			fprintf(file, "%s\n", message);
			return;
		}
		error = strcat_s(output, output_size, space);
		if (error) {
			fprintf(file, "%s\n", message);
			return;
		}
	}

	if (message_len > 0) {
		errno_t error = strcat_s(output, output_size, message);
		if (error) {
			fprintf(file, "%s\n", message);
			return;
		}
	}

	fprintf(file, "%s\n", output);
}

int __str_to_int(const char* str, int default_value) {
	if (str == NULL || *str == '\0') {
		return default_value;
	}

	char* ends = NULL;
	int value = strtol(str, &ends, 0);
	if (ends == NULL || *ends != '\0') {
		return default_value;
	}

	return value;
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

	size_t size = strftime(time_buff, time_buff_size, UC_LOG_TIME_FORMAT, &tm);

	if (!size) {
		*len = 0;
		if (time_buff_size > 0) {
			*time_buff = '\0';
		}
		return;
	}

	*len = strlen(time_buff);
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
