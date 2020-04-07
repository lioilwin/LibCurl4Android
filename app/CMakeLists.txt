cmake_minimum_required(VERSION 3.4.1)

set(CPP_DIR ${CMAKE_SOURCE_DIR}/src/main/cpp) #源码目录(.h .c .cpp)
set(LIB_DIR ${CMAKE_SOURCE_DIR}/src/main/jniLibs/${CMAKE_ANDROID_ARCH_ABI}) #第三方库目录(.a .so)

add_library(
        native-lib
        SHARED
        ${CPP_DIR}/native-lib.cpp
)

target_link_libraries(
        native-lib
        log   # NDK自带的日志库
        z     # NDK自带的zlib库
        ${LIB_DIR}/libcurl.a  # libcurl静态库
)