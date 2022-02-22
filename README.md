# rapidsnark

rapid snark is a zkSnark proof generation written in C++. That generates proofs created in [circom](https://github.com/iden3/snarkjs) and [snarkjs](https://github.com/iden3/circom) very fast.

## dependencies

You should have installed gcc and cmake

In ubuntu:

````
sudo apt install build-essential
sudo apt install cmake
````

## compile prover for local host

````sh
git submodule init
git submodule update
./build_gmp.sh host
mkdir build_prover && cd build_prover
cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../package
make -j$(nproc) && make install
````

## compile prover for Android

Install Android NDK from https://developer.android.com/ndk or with help of "SDK Manager" in Android Studio.

Set the value of ANDROID_NDK environment variable to the absolute path of Android NDK root directory.

Examples:

````sh
export ANDROID_NDK=/home/test/Android/Sdk/ndk/23.1.7779620  # NDK is installed by "SDK Manager" in Android Studio.
export ANDROID_NDK=/home/test/android-ndk-r23b              # NDK is installed as a stand-alone package.
````

Compilation:

````sh
git submodule init
git submodule update
./build_gmp.sh android
mkdir build_prover_android && cd build_prover_android
cmake .. -DTARGET_PLATFORM=ANDROID -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../package_android
make -j$(nproc) && make install
````

## compile prover for iOS

Install Xcode.

````sh
git submodule init
git submodule update
./build_gmp.sh ios
mkdir build_prover_ios && cd build_prover_ios
cmake .. -GXcode -DTARGET_PLATFORM=IOS -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../package_ios
make -j$(nproc) && make install
````

## Building proof

You have a full prover compiled in the build directory.

So you can replace snarkjs command:

````sh
snarkjs groth16 prove <circuit.zkey> <witness.wtns> <proof.json> <public.json>
````

by this one
````sh
./package/bin/prover <circuit.zkey> <witness.wtns> <proof.json> <public.json>
````

## Benchmark

This prover parallelizes as much as it can the proof generation.

The prover is much faster that snarkjs and faster than bellman.

[TODO] Some comparation tests should be done.


## License

rapidsnark is part of the iden3 project copyright 2021 0KIMS association and published with GPL-3 license. Please check the COPYING file for more details.
