###

# Build targets
host:
	rm -rf build_prover && mkdir build_prover && cd build_prover && \
	cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../package && \
	make -j$(nproc) -vvv && make install

host_noasm:
	rm -rf build_prover_noasm && mkdir build_prover_noasm && cd build_prover_noasm && \
		cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../package_noasm -DUSE_ASM=NO && \
		make -j$(nproc) -vvv && make install

host_march:
	rm -rf build_prover_march && mkdir build_prover_march && cd build_prover_march && \
		cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../package_march -DUSE_MARCH_NATIVE=ON && \
		make -j$(nproc) -vvv && make install

host_lto:
	rm -rf build_prover_lto && mkdir build_prover_lto && cd build_prover_lto && \
		cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../package_lto -DUSE_LTO=ON && \
		make -j$(nproc) -vvv && make install

host_march_lto:
	rm -rf build_prover_march_lto && mkdir build_prover_march_lto && cd build_prover_march_lto && \
		cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../package_march_lto -DUSE_MARCH_NATIVE=ON -DUSE_LTO=ON && \
		make -j$(nproc) -vvv && make install

# Profile-Guided Optimization on top of LTO. Two-phase: build an instrumented
# prover, run it on a TRAINING circuit to collect profiles, then rebuild using
# them. The training circuit should resemble your production workload -- a tiny
# circuit produces a profile that can pessimize large-circuit proving. Override:
#   make host_pgo PGO_ZKEY=/path/circuit_final.zkey PGO_WTNS=/path/witness.wtns
# Multiple training runs accumulate (.gcda counters sum), improving coverage.
PGO_ZKEY ?= testdata/circuit_final.zkey
PGO_WTNS ?= testdata/witness.wtns
host_pgo:
	rm -rf build_prover_pgo && mkdir build_prover_pgo
	@echo "=== PGO phase 1/2: instrumented build (LTO on) ==="
	cd build_prover_pgo && \
		cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../package_pgo \
			-DUSE_LTO=ON -DPGO=generate && \
		make -j$(nproc)
	@echo "=== PGO training run on $(PGO_ZKEY) ==="
	./build_prover_pgo/src/prover $(PGO_ZKEY) $(PGO_WTNS) /tmp/pgo_train_proof.json /tmp/pgo_train_public.json
	@echo "=== PGO phase 2/2: rebuild using collected profiles ==="
	cd build_prover_pgo && \
		cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../package_pgo \
			-DUSE_LTO=ON -DPGO=use && \
		make -j$(nproc) && make install

host_arm64:
	rm -rf build_prover_arm64 && mkdir build_prover_arm64 && cd build_prover_arm64 && \
	cmake .. -DTARGET_PLATFORM=aarch64 -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../package_arm64 && \
	make -j$(nproc) -vvv && make install

android:
	rm -rf build_prover_android && mkdir build_prover_android && cd build_prover_android && \
	cmake .. -DTARGET_PLATFORM=ANDROID -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../package_android -DBUILD_TESTS=OFF -DUSE_OPENMP=OFF && \
	make -j$(nproc) -vvv && make install

# LTO variant. On arm64 only the innermost limb multiply is ASM; the rest of the
# field layer plus curve/FFT/MSM glue is C++, so LTO's cross-TU inlining has more
# to work on than on x86. Portable (unlike -march=native). Slower/heavier link.
android_lto:
	rm -rf build_prover_android_lto && mkdir build_prover_android_lto && cd build_prover_android_lto && \
	cmake .. -DTARGET_PLATFORM=ANDROID -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../package_android_lto -DBUILD_TESTS=OFF -DUSE_OPENMP=OFF -DUSE_LTO=ON && \
	make -j$(nproc) -vvv && make install

android_openmp:
	rm -rf build_prover_android_openmp && mkdir build_prover_android_openmp && cd build_prover_android_openmp && \
	cmake .. -DTARGET_PLATFORM=ANDROID -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../package_android_openmp -DBUILD_TESTS=OFF -DUSE_OPENMP=ON && \
	make -j$(nproc) -vvv && make install

android_x86_64:
	rm -rf build_prover_android_x86_64 && mkdir build_prover_android_x86_64 && cd build_prover_android_x86_64 && \
	cmake .. -DTARGET_PLATFORM=ANDROID_x86_64 -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../package_android_x86_64 -DBUILD_TESTS=OFF -DUSE_OPENMP=OFF && \
	make -j$(nproc) -vvv && make install

# LTO variant for x86_64 Android (emulator / x86 devices). Same portable LTO
# path as android_lto; useful for benchmarking LTO on the emulator.
android_x86_64_lto:
	rm -rf build_prover_android_x86_64_lto && mkdir build_prover_android_x86_64_lto && cd build_prover_android_x86_64_lto && \
	cmake .. -DTARGET_PLATFORM=ANDROID_x86_64 -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../package_android_x86_64_lto -DBUILD_TESTS=OFF -DUSE_OPENMP=OFF -DUSE_LTO=ON && \
	make -j$(nproc) -vvv && make install

android_openmp_x86_64:
	rm -rf build_prover_android_openmp_x86_64 && mkdir build_prover_android_openmp_x86_64 && cd build_prover_android_openmp_x86_64 && \
	cmake .. -DTARGET_PLATFORM=ANDROID_x86_64 -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../package_android_openmp_x86_64 -DBUILD_TESTS=OFF -DUSE_OPENMP=ON && \
	make -j$(nproc) -vvv && make install

ios:
	@if [ ! -d "./depends/gmp/package_ios_arm64" ]; then echo "Looks like gmp lib is not built. Run './build_gmp.sh ios' first." && exit 1; fi
	rm -rf build_prover_ios && mkdir build_prover_ios && cd build_prover_ios && \
		cmake .. -GXcode -DTARGET_PLATFORM=IOS -DCMAKE_INSTALL_PREFIX=../package_ios && \
		xcodebuild -destination 'generic/platform=iOS' -scheme rapidsnarkStatic -project rapidsnark.xcodeproj -configuration Release && \
		xcodebuild -destination 'generic/platform=iOS' -scheme rapidsnark -project rapidsnark.xcodeproj -configuration Release CODE_SIGNING_ALLOWED=NO && \
		cp ../depends/gmp/package_ios_arm64/lib/libgmp.a src/Release-iphoneos && \
		echo "" && echo "iOS Simulator artifacts built in build_prover_ios/src/Release-iphoneos" && echo ""

# LTO variant for iOS. -DUSE_LTO=ON maps to the LLVM_LTO Xcode setting via
# CMAKE_INTERPROCEDURAL_OPTIMIZATION. Same rationale as android_lto (mostly-C++
# field/curve layer on arm64). Portable; slower/heavier link.
ios_lto:
	@if [ ! -d "./depends/gmp/package_ios_arm64" ]; then echo "Looks like gmp lib is not built. Run './build_gmp.sh ios' first." && exit 1; fi
	rm -rf build_prover_ios_lto && mkdir build_prover_ios_lto && cd build_prover_ios_lto && \
		cmake .. -GXcode -DTARGET_PLATFORM=IOS -DCMAKE_INSTALL_PREFIX=../package_ios_lto -DUSE_LTO=ON && \
		xcodebuild -destination 'generic/platform=iOS' -scheme rapidsnarkStatic -project rapidsnark.xcodeproj -configuration Release && \
		xcodebuild -destination 'generic/platform=iOS' -scheme rapidsnark -project rapidsnark.xcodeproj -configuration Release CODE_SIGNING_ALLOWED=NO && \
		cp ../depends/gmp/package_ios_arm64/lib/libgmp.a src/Release-iphoneos && \
		echo "" && echo "iOS LTO artifacts built in build_prover_ios_lto/src/Release-iphoneos" && echo ""

ios_simulator:
	@if [ ! -d "./depends/gmp/package_iphone_simulator" ]; then echo "Looks like gmp lib is not built. Run './build_gmp.sh ios_simulator' first." && exit 1; fi
	rm -rf build_prover_ios_simulator && mkdir build_prover_ios_simulator && cd build_prover_ios_simulator && \
		cmake .. -GXcode -DTARGET_PLATFORM=IOS_SIMULATOR -DCMAKE_INSTALL_PREFIX=../package_ios_simulator -DUSE_ASM=NO && \
		xcodebuild -destination 'generic/platform=iOS Simulator' -scheme rapidsnarkStatic -project rapidsnark.xcodeproj && \
		xcodebuild -destination 'generic/platform=iOS Simulator' -scheme rapidsnark -project rapidsnark.xcodeproj CODE_SIGNING_ALLOWED=NO ARCHS=arm64 && \
		cp ../depends/gmp/package_iphone_simulator/lib/libgmp.a src/Debug-iphonesimulator && \
		echo "" && echo "iOS Simulator artifacts built in build_prover_ios_simulator/src/Debug-iphonesimulator" && echo ""

macos_arm64:
	@if [ ! -d "./depends/gmp/package_macos_arm64" ]; then echo "Looks like gmp lib is not built. Run './build_gmp.sh macos_arm64' first." && exit 1; fi
	rm -rf build_prover_macos_arm64 && mkdir build_prover_macos_arm64 && cd build_prover_macos_arm64 && \
		cmake .. -DTARGET_PLATFORM=macos_arm64 -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../package_macos_arm64 && \
		make -j$(nproc) -vvv && make install

macos_x86_64:
	@if [ ! -d "./depends/gmp/package_macos_x86_64" ]; then echo "Looks like gmp lib is not built. Run './build_gmp.sh macos_x86_64' first." && exit 1; fi
	rm -rf build_prover_macos_x86_64 && mkdir build_prover_macos_x86_64 && cd build_prover_macos_x86_64 && \
		cmake .. -DTARGET_PLATFORM=macos_x86_64 -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../package_macos_x86_64 && \
		make -j$(nproc) -vvv && make install

clean:
	rm -rf build_prover \
		build_prover_noasm \
		build_prover_lto \
		build_prover_march \
		build_prover_march_lto \
		build_prover_pgo \
		build_prover_macos_arm64 \
		build_prover_macos_x86_64 \
		build_prover_android \
		build_prover_android_lto \
		build_prover_android_x86_64 \
		build_prover_android_x86_64_lto \
		build_prover_ios \
		build_prover_ios_lto \
		build_prover_ios_simulator \
		package \
		package_noasm \
		package_lto \
		package_march \
		package_march_lto \
		package_pgo \
		package_macos_arm64 \
		package_macos_x86_64 \
		package_android \
		package_android_lto \
		package_android_x86_64 \
		package_android_x86_64_lto \
		package_ios \
		package_ios_lto \
		package_ios_simulator \
		depends/gmp/package \
		depends/gmp/package_macos_arm64 \
		depends/gmp/package_macos_x86_64 \
		depends/gmp/package_android_arm64 \
		depends/gmp/package_android_x86_64 \
		depends/gmp/package_ios_arm64 \
		depends/gmp/package_iphone_simulator
