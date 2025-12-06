## Important note 

**This is a new implementation of rapidsnark. The original (and now obsoleted) implementation is available here: [rapidsnark-old](https://github.com/iden3/rapidsnark-old).**

# rapidsnark

Rapidsnark is a zkSnark proof generation written in C++ and intel/arm assembly. That generates proofs created in [circom](https://github.com/iden3/circom) and [snarkjs](https://github.com/iden3/snarkjs) very fast.

## Dependencies

You should have installed gcc, cmake, libsodium, and gmp (development)

In ubuntu:

```
sudo apt-get install build-essential cmake libgmp-dev libsodium-dev nasm curl m4
```

On MacOS:

```
brew install cmake gmp libsodium nasm
```

## Compile prover in standalone mode

### Compile prover for x86_64 host machine

```sh
git submodule init
git submodule update
./build_gmp.sh host
make host
```

### Compile prover for macOS arm64 host machine

```sh
git submodule init
git submodule update
./build_gmp.sh macos_arm64
make macos_arm64
```

### Compile prover for linux arm64 host machine

```sh
git submodule init
git submodule update
./build_gmp.sh host
make host_arm64
```

### Compile prover for linux arm64 machine

```sh
git submodule init
git submodule update
./build_gmp.sh host
make arm64
```

### Compile prover for Android

Install Android NDK from https://developer.android.com/ndk or with help of "SDK Manager" in Android Studio.

Set the value of ANDROID_NDK environment variable to the absolute path of Android NDK root directory.

Examples:

```sh
export ANDROID_NDK=/home/test/Android/Sdk/ndk/23.1.7779620  # NDK is installed by "SDK Manager" in Android Studio.
export ANDROID_NDK=/home/test/android-ndk-r23b              # NDK is installed as a stand-alone package.
```

Prerequisites if build on Ubuntu:

```sh
apt-get install curl xz-utils build-essential cmake m4 nasm
```

Compilation:

```sh
git submodule init
git submodule update
./build_gmp.sh android
make android
```

### Compile prover for iOS

Install Xcode

```sh
git submodule init
git submodule update
./build_gmp.sh ios
make ios
```
Open generated Xcode project and compile prover.

## Build for iOS emulator

Install Xcode

```sh
git submodule init
git submodule update
./build_gmp.sh ios_simulator
make ios_simulator
```

Files that you need to copy to your XCode project to link against Rapidsnark:
* build_prover_ios_simulator/src/Debug-iphonesimulator/librapidsnark.a
* build_prover_ios_simulator/src/Debug-iphonesimulator/libfq.a
* build_prover_ios_simulator/src/Debug-iphonesimulator/libfr.a
* depends/gmp/package_iphone_simulator/lib/libgmp.a

## Building proof

You have a full prover compiled in the build directory.

So you can replace snarkjs command:

```sh
snarkjs groth16 prove <circuit.zkey> <witness.wtns> <proof.json> <public.json>
```

by this one
```sh
./package/bin/prover <circuit.zkey> <witness.wtns> <proof.json> <public.json>
```

## Compile prover in server mode

```sh
npm install
git submodule init
git submodule update
npx task buildPistache
npx task buildProverServer
```

## Launch prover in server mode
```sh
./build/proverServer  <port> <circuit1_zkey> <circuit2_zkey> ... <circuitN_zkey>
```

For every `circuit.circom` you have to generate with circom with --c option the `circuit_cpp` and after compilation you have to copy the executable into the `build` folder so the server can generate the witness and then the proof based on this witness.
You have an example of the usage calling the server endpoints to generate the proof with Nodejs in `/tools/request.js`.

To test a request you should pass an `input.json` as a parameter to the request call.
```sh
node tools/request.js <input.json> <circuit>
```

## Wrappers

Rapidsnark can be used with several programming languages and environments through wrappers that provide integration with the original library. Below is a list of available wrappers:

| Wrapper      | Repository Link                         |
| ------------ |-----------------------------------------|
| Go           | https://github.com/iden3/go-rapidsnark  |
| iOS          | https://github.com/iden3/ios-rapidsnark |
| Android      | https://github.com/iden3/android-rapidsnark |
| React Native | https://github.com/iden3/react-native-rapidsnark |
| Flutter      | https://github.com/iden3/flutter-rapidsnark |

## Benchmark

This prover parallelizes as much as it can the proof generation.

The prover is much faster than snarkjs and faster than bellman.

[TODO] Some comparative tests should be done.

## Run tests

You need to perform all the steps from the
[Compile prover in standalone mode](#compile-prover-in-standalone-mode) section.
After that you can run tests with the following command from the build
directory:

```sh
# Make sure you are in the build directory
# ./build_prover for linux, ./build_prover_macos_arm64 for macOS.
cmake --build . --parallel && ctest --rerun-failed --output-on-failure
```

To run just the `test_public_size` test for custom zkey to measure the
performance, you can run the following command from the build directory:

```sh
src/test_public_size ../testdata/circuit_final.zkey 86
```

## License

rapidsnark is part of the iden3 project copyright 2021 0KIMS association and published with LGPL-3 license. Please check the COPYING file for more details.
