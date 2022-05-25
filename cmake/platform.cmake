cmake_minimum_required(VERSION 3.5)

string(TOLOWER "${TARGET_PLATFORM}" TARGET_PLATFORM)

message("Building for " ${TARGET_PLATFORM})

set(GMP_ROOT depends/gmp)

if(TARGET_PLATFORM MATCHES "android")

    if(NOT DEFINED ENV{ANDROID_NDK})
        message("ANDROID_NDK environment variable is not set.")
        message("It must be an absolute path to the root directory of Android NDK.")
        message(" For instance /home/test/Android/Sdk/ndk/23.1.7779620")
        message(FATAL_ERROR "Build failed.")
    else()
        message("Android NDK path is " $ENV{ANDROID_NDK})
    endif()

    set(CMAKE_SYSTEM_NAME Android)
    set(CMAKE_SYSTEM_VERSION 23) # API level
    set(CMAKE_ANDROID_ARCH_ABI arm64-v8a)

    message("CMAKE_ANDROID_ARCH_ABI=" ${CMAKE_ANDROID_ARCH_ABI})

    set(GMP_PREFIX ${GMP_ROOT}/package_android_arm64)

elseif(TARGET_PLATFORM MATCHES "ios")

    set(CMAKE_SYSTEM_NAME iOS)
    set(CMAKE_OSX_ARCHITECTURES arm64)

    set(GMP_PREFIX ${GMP_ROOT}/package_ios_arm64)

else()
    set(GMP_PREFIX ${GMP_ROOT}/package)

endif()


set(GMP_INCLUDE_DIR ${GMP_PREFIX}/include)
set(GMP_INCLUDE_FILE gmp.h)
set(GMP_LIB_DIR ${GMP_PREFIX}/lib)
set(GMP_LIB_FILE libgmp.a)

set(GMP_LIB_FILE_FULLPATH     ${CMAKE_SOURCE_DIR}/${GMP_LIB_DIR}/${GMP_LIB_FILE})
set(GMP_INCLUDE_FILE_FULLPATH ${CMAKE_SOURCE_DIR}/${GMP_INCLUDE_DIR}/${GMP_INCLUDE_FILE})

set(GMP_LIB ${GMP_LIB_FILE_FULLPATH})

message("CMAKE_SYSTEM_NAME=" ${CMAKE_SYSTEM_NAME})
