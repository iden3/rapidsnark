#!/bin/sh

usage()
{
    echo "USAGE: $0 <android|android_x86_64|ios|host>"
    echo "where"
    echo "    android:        build for Android arm64"
    echo "    android_x86_64: build for Android x86_64"
    echo "    ios:            build for iOS arm64"
    echo "    host:           build for this host"

    exit 1
}

get_gmp()
{
    GMP_NAME=gmp-6.2.1
    GMP_ARCHIVE=${GMP_NAME}.tar.xz

    if [ ! -f ${GMP_ARCHIVE} ]; then

        wget https://ftp.gnu.org/gnu/gmp/${GMP_ARCHIVE}
    fi


    if [ ! -d gmp ]; then

        tar -xvf ${GMP_ARCHIVE}
        mv ${GMP_NAME} gmp
    fi
}

build_host()
{
    PACKAGE_DIR="$GMP_DIR/package"
    BUILD_DIR=build

    if [ -d "$PACKAGE_DIR" ]; then
        echo "Host package is built already. See $PACKAGE_DIR"
        return 1
    fi

    rm -rf "$BUILD_DIR"
    mkdir "$BUILD_DIR"
    cd "$BUILD_DIR"

    ../configure --prefix="$PACKAGE_DIR" --with-pic &&
    make -j$(nproc) &&
    make install

    cd ..
}

build_android()
{
    PACKAGE_DIR="$GMP_DIR/package_android_arm64"
    BUILD_DIR=build_android_arm64

    if [ -d "$PACKAGE_DIR" ]; then
        echo "Android package is built already. See $PACKAGE_DIR"
        return 1
    fi

    if [ -z $ANDROID_NDK ]; then

        echo "ERROR: ANDROID_NDK environment variable is not set."
        echo "       It must be an absolute path to the root directory of Android NDK."
        echo "       For instance /home/test/Android/Sdk/ndk/23.1.7779620"
        return 1
    fi

    export TOOLCHAIN=$ANDROID_NDK/toolchains/llvm/prebuilt/linux-x86_64

    export TARGET=aarch64-linux-android
    export API=21

    export AR=$TOOLCHAIN/bin/llvm-ar
    export CC=$TOOLCHAIN/bin/$TARGET$API-clang
    export AS=$CC
    export CXX=$TOOLCHAIN/bin/$TARGET$API-clang++
    export LD=$TOOLCHAIN/bin/ld
    export RANLIB=$TOOLCHAIN/bin/llvm-ranlib
    export STRIP=$TOOLCHAIN/bin/llvm-strip

    echo $TOOLCHAIN
    echo $TARGET

    rm -rf "$BUILD_DIR"
    mkdir "$BUILD_DIR"
    cd "$BUILD_DIR"

    ../configure --host $TARGET --prefix="$PACKAGE_DIR" --with-pic --disable-fft &&
    make -j$(nproc) &&
    make install

    cd ..
}

build_android_x86_64()
{
    PACKAGE_DIR="$GMP_DIR/package_android_x86_64"
    BUILD_DIR=build_android_x86_64

    if [ -d "$PACKAGE_DIR" ]; then
        echo "Android package is built already. See $PACKAGE_DIR"
        return 1
    fi

    if [ -z $ANDROID_NDK ]; then

        echo "ERROR: ANDROID_NDK environment variable is not set."
        echo "       It must be an absolute path to the root directory of Android NDK."
        echo "       For instance /home/test/Android/Sdk/ndk/23.1.7779620"
        return 1
    fi

    export TOOLCHAIN=$ANDROID_NDK/toolchains/llvm/prebuilt/linux-x86_64

    export TARGET=x86_64-linux-android
    export API=21

    export AR=$TOOLCHAIN/bin/llvm-ar
    export CC=$TOOLCHAIN/bin/$TARGET$API-clang
    export AS=$CC
    export CXX=$TOOLCHAIN/bin/$TARGET$API-clang++
    export LD=$TOOLCHAIN/bin/ld
    export RANLIB=$TOOLCHAIN/bin/llvm-ranlib
    export STRIP=$TOOLCHAIN/bin/llvm-strip

    echo $TOOLCHAIN
    echo $TARGET

    rm -rf "$BUILD_DIR"
    mkdir "$BUILD_DIR"
    cd "$BUILD_DIR"

    ../configure --host $TARGET --prefix="$PACKAGE_DIR" --with-pic --disable-fft &&
    make -j$(nproc) &&
    make install

    cd ..
}

build_ios()
{
    PACKAGE_DIR="$GMP_DIR/package_ios_arm64"
    BUILD_DIR=build_ios_arm64

    if [ -d "$PACKAGE_DIR" ]; then
        echo "iOS package is built already. See $PACKAGE_DIR"
        return 1
    fi

    export SDK="iphoneos"
    export TARGET=arm-apple-darwin
    export MIN_IOS_VERSION=8.0

    export ARCH_FLAGS="-arch arm64 -arch arm64e"
    export OPT_FLAGS="-O3 -g3 -fembed-bitcode"
    export HOST_FLAGS="${ARCH_FLAGS} -miphoneos-version-min=${MIN_IOS_VERSION} -isysroot $(xcrun --sdk ${SDK} --show-sdk-path)"

    export CC=$(xcrun --find --sdk "${SDK}" clang)
    export CXX=$(xcrun --find --sdk "${SDK}" clang++)
    export CPP=$(xcrun --find --sdk "${SDK}" cpp)
    export CFLAGS="${HOST_FLAGS} ${OPT_FLAGS}"
    export CXXFLAGS="${HOST_FLAGS} ${OPT_FLAGS}"
    export LDFLAGS="${HOST_FLAGS}"

    echo $TARGET

    rm -rf "$BUILD_DIR"
    mkdir "$BUILD_DIR"
    cd "$BUILD_DIR"

    ../configure --host $TARGET --prefix="$PACKAGE_DIR" --with-pic --disable-fft --disable-assembly &&
    make -j$(nproc) &&
    make install

    cd ..
}


if [ $# -ne 1 ]; then
    usage
fi

TARGET_PLATFORM=`echo $1 | tr A-Z a-z`

cd depends

get_gmp

cd gmp

GMP_DIR=$PWD

case "$TARGET_PLATFORM" in

    "ios" )
        echo "Building for ios"
        build_ios
    ;;

    "android" )
        echo "Building for android"
        build_android
    ;;

    "android_x86_64" )
        echo "Building for android x86_64"
        build_android_x86_64
    ;;

    "host" )
        echo "Building for this host"
        build_host
    ;;

    * )
    usage

esac
