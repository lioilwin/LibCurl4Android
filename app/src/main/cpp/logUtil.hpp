#ifndef _LOGUTIL_HPP
#define _LOGUTIL_HPP

#define NDK_LOG 1

#if NDK_LOG

#include <android/log.h>
#include <jni.h>

#define TAG "logUtil"
#define LOGV(fmt, ...) __android_log_print(ANDROID_LOG_VERBOSE, TAG, fmt, __VA_ARGS__)
#define LOGD(fmt, ...) __android_log_print(ANDROID_LOG_DEBUG, TAG, fmt, __VA_ARGS__)
#define LOGI(fmt, ...) __android_log_print(ANDROID_LOG_INFO, TAG, fmt, __VA_ARGS__)
#define LOGW(fmt, ...) __android_log_print(ANDROID_LOG_WARN, TAG, fmt, __VA_ARGS__)
#define LOGE(fmt, ...) __android_log_print(ANROID_LOG_ERROR, TAG, fmt, __VA_ARGS__)
#else
#define LOGV(...)
#define LOGD(...)
#define LOGI(...)
#define LOGW(...)
#define LOGE(...)
#endif

#endif // _LOGUTIL_HPP