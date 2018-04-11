/******************************************************************************
|
| Copyright (c) 2018 streamingnology Inc (https://github.com/streamingnology)
|
| This file is part of HTTP Server
|
| Permission is hereby granted, free of charge, to any person obtaining a copy
| of this software and associated documentation files (the "Software"), to deal
| in the Software without restriction, including without limitation the rights
| to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
| copies of the Software, and to permit persons to whom the Software is
| furnished to do so, subject to the following conditions:
|
| The above copyright notice and this permission notice shall be included in all
| opies or substantial portions of the Software.
|
| THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
| MPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
| FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
| AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
| LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
| OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN THE
| OFTWARE.
 ******************************************************************************/

#include "log.h"

void log_print_verbose(const char *TAG, const char *fmt, ...) {
	if (LEVEL <= VERBOSE) {

		char printf_buf[1024];
		va_list args;

		va_start(args, fmt);
		vsprintf(printf_buf, fmt, args);
		va_end(args);

		// 判断是否有换行符
		bool flag = false;
		if (fmt[strlen(fmt)-1] == '\n')
			flag = true;

		if (flag) {
			printf("V/%s:  %s", TAG, printf_buf);
		} else {
			printf("V/%s:  %s\n", TAG, printf_buf);
		}
	}
}

void log_print_debug(const char *TAG, const char *fmt, ...) {
	if (LEVEL <= DEBUG) {

		char printf_buf[1024];
		va_list args;

		va_start(args, fmt);
		vsprintf(printf_buf, fmt, args);
		va_end(args);

		// 判断是否有换行符
		bool flag = false;
		if (fmt[strlen(fmt)-1] == '\n')
			flag = true;

		if (flag) {
			printf("D/%s:  %s", TAG, printf_buf);
		} else {
			printf("D/%s:  %s\n", TAG, printf_buf);
		}
	}
}

void log_print_info(const char *TAG, const char *fmt, ...) {
	if (LEVEL <= INFO) {

		char printf_buf[1024];
		va_list args;

		va_start(args, fmt);
		vsprintf(printf_buf, fmt, args);
		va_end(args);

		// 判断是否有换行符
		bool flag = false;
		if (fmt[strlen(fmt)-1] == '\n')
			flag = true;

		if (flag) {
			printf("I/%s:  %s", TAG, printf_buf);
		} else {
			printf("I/%s:  %s\n", TAG, printf_buf);
		}
	}
}

void log_print_warn(const char *TAG, const char *fmt, ...) {
	if (LEVEL <= WARN) {

		char printf_buf[1024];
		va_list args;

		va_start(args, fmt);
		vsprintf(printf_buf, fmt, args);
		va_end(args);

		// 判断是否有换行符
		bool flag = false;
		if (fmt[strlen(fmt)-1] == '\n')
			flag = true;

		if (flag) {
			printf("W/%s:  %s", TAG, printf_buf);
		} else {
			printf("W/%s:  %s\n", TAG, printf_buf);
		}
	}
}

void log_print_error(const char *TAG, const char *fmt, ...) {
	if (LEVEL <= ERROR) {

		char printf_buf[1024];
		va_list args;

		va_start(args, fmt);
		vsprintf(printf_buf, fmt, args);
		va_end(args);

		// 判断是否有换行符
		bool flag = false;
		if (fmt[strlen(fmt)-1] == '\n')
			flag = true;

		if (flag) {
			printf("E/%s:  %s", TAG, printf_buf);
		} else {
			printf("E/%s:  %s\n", TAG, printf_buf);
		}
	}
}