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

#ifndef MAGE_COMMON_LOG_H
#define MAGE_COMMON_LOG_H

#include <stdio.h>
#include <stdarg.h>
#include <string.h>

#define ANDROID_NDK true

#if ANDROID_NDK
#include <jni.h>
#include <android/log.h>
#endif

// ----------------------------------------------------------

const int VERBOSE = 1;
const int DEBUG = 2;
const int INFO = 3;
const int WARN = 4;
const int ERROR = 5;

const int LEVEL = VERBOSE;

// ----------------------------------------------------------

void log_print_verbose(const char *TAG, const char *fmt, ...);
void log_print_debug(const char *TAG, const char *fmt, ...);
void log_print_info(const char *TAG, const char *fmt, ...);
void log_print_warn(const char *TAG, const char *fmt, ...);
void log_print_error(const char *TAG, const char *fmt, ...);

#if ANDROID_NDK
#define LOGV(TAG, ...) __android_log_print(ANDROID_LOG_VERBOSE, TAG, __VA_ARGS__)
#define LOGD(TAG, ...) __android_log_print(ANDROID_LOG_DEBUG, TAG, __VA_ARGS__)
#define LOGI(TAG, ...) __android_log_print(ANDROID_LOG_INFO, TAG, __VA_ARGS__)
#define LOGW(TAG, ...) __android_log_print(ANDROID_LOG_WARN, TAG, __VA_ARGS__)
#define LOGE(TAG, ...) __android_log_print(ANDROID_LOG_ERROR, TAG, __VA_ARGS__)
#else
#define LOGV(TAG, fmt, ...) log_print_verbose(TAG, fmt, ##__VA_ARGS__)
#define LOGD(TAG, fmt, ...) log_print_debug(TAG, fmt, ##__VA_ARGS__)
#define LOGI(TAG, fmt, ...) log_print_info(TAG, fmt, ##__VA_ARGS__)
#define LOGW(TAG, fmt, ...) log_print_warn(TAG, fmt, ##__VA_ARGS__)
#define LOGE(TAG, fmt, ...) log_print_error(TAG, fmt, ##__VA_ARGS__)
#endif

#endif // !MAGE_COMMON_LOG_H