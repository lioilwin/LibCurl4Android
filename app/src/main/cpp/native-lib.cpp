#include <jni.h>
#include <iostream>
#include <thread>
#include <sstream>
#include <unistd.h>
#include "logUtil.hpp"
#include "ftpUtil.hpp"

using namespace std;

size_t writeToString(void *buffer, size_t size, size_t nmemb, void *userp) {
    (*((string *) userp)).append((char *) buffer);
    return size * nmemb;
}

/**
 * 测试Http
 */
extern "C" JNIEXPORT jstring JNICALL
Java_com_example_libcurl4java_MainActivity_testHttpFromCurl(JNIEnv *env, jobject thiz) {
    string writeData;
    CURL *curl = curl_easy_init();
    curl_easy_setopt(curl, CURLOPT_URL, "https://www.baidu.com");
    curl_easy_setopt(curl, CURLOPT_PORT, "21");
    curl_easy_setopt(curl, CURLOPT_SSL_VERIFYPEER, 0);
    curl_easy_setopt(curl, CURLOPT_WRITEFUNCTION, writeToString);
    curl_easy_setopt(curl, CURLOPT_WRITEDATA, &writeData);
    CURLcode resultCode = curl_easy_perform(curl);
    curl_easy_cleanup(curl);
    const char *result = writeData.c_str();
    LOGD("version = %s", curl_version());
    LOGD("resultCode = %s", curl_easy_strerror(resultCode));
    LOGD("result = %s", result);
    return env->NewStringUTF(result);
}

/**
 * 测试Ftp
 */
extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_libcurl4java_MainActivity_testFtpFromCurl(JNIEnv *env, jobject thiz) {
//    FtpUpload("ftp://127.0.0.1:211/myfile/curl.zip", "/home/user/codetest/curl-7.62.0.zip", "user", "123", 1);
    int ret = FtpDownload("ftp://[240E:002F:8080:0020::9]:2021/test.txt", "/sdcard/1.txt", "zsy",
                          "Wxzx_Wellcell_zsy!@#2407");
    return env->NewStringUTF(ret > 0 ? "true" : "false");
}

/**
 * 测试调用Java
 */
extern "C" JNIEXPORT jstring JNICALL
Java_com_example_libcurl4java_MainActivity_testCallJava(JNIEnv *env, jobject thiz) {
    jclass processAn = env->FindClass("android/os/Process");
    jint myUid = env->CallStaticIntMethod(processAn,
                                          env->GetStaticMethodID(processAn, "myUid", "()I"));
    const char *result = ("myUid = " + to_string(myUid)).c_str();
    LOGD(result, NULL);
    return env->NewStringUTF(result);
}

string threadIdToStr(const thread::id &id) {
    std::stringstream sin;
    sin << id;
    return sin.str();
}

extern "C"
JNIEXPORT jstring JNICALL
Java_com_example_libcurl4java_MainActivity_testThread(JNIEnv *env, jobject thiz) {
    auto my_lam_thread = [] {
        LOGD("我的线程正在执行 tid = %d", gettid());
    };
    thread my_thread(my_lam_thread);
    my_thread.join();
    LOGD("主线程 uid = %d", getuid());
    LOGD("主线程 pid = %d", getpid());
    LOGD("主线程 tid = %d", gettid());
    return env->NewStringUTF(("currentThreadIdFromCpp = " + to_string(gettid())).c_str());
}