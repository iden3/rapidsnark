###

#Build targets
host:
	rm -rf build_prover && mkdir build_prover && cd build_prover && \
	cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../package && \
	make -j$(nproc) -vvv && make install

host_noasm:
	rm -rf build_prover_noasm && mkdir build_prover_noasm && cd build_prover_noasm && \
		cmake .. -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../package_noasm -DUSE_ASM=NO && \
		make -j$(nproc) -vvv && make install

host_arm64:
	rm -rf build_prover_arm64 && mkdir build_prover_arm64 && cd build_prover_arm64 && \
	cmake .. -DTARGET_PLATFORM=aarch64 -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../package_arm64 && \
	make -j$(nproc) -vvv && make install

android:
	rm -rf build_prover_android && mkdir build_prover_android && cd build_prover_android && \
	cmake .. -DTARGET_PLATFORM=ANDROID -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../package_android -DBUILD_TESTS=OFF -DUSE_OPENMP=OFF && \
	make -j$(nproc) -vvv && make install

android_openmp:
	rm -rf build_prover_android_openmp && mkdir build_prover_android_openmp && cd build_prover_android_openmp && \
	cmake .. -DTARGET_PLATFORM=ANDROID -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../package_android_openmp -DBUILD_TESTS=OFF -DUSE_OPENMP=ON && \
	make -j$(nproc) -vvv && make install

android_x86_64:
	rm -rf build_prover_android_x86_64 && mkdir build_prover_android_x86_64 && cd build_prover_android_x86_64 && \
	cmake .. -DTARGET_PLATFORM=ANDROID_x86_64 -DCMAKE_BUILD_TYPE=Release -DCMAKE_INSTALL_PREFIX=../package_android_x86_64 -DBUILD_TESTS=OFF -DUSE_OPENMP=OFF && \
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
		build_prover_macos_arm64 \
		build_prover_macos_x86_64 \
		build_prover_android \
		build_prover_android_x86_64 \
		build_prover_ios \
		build_prover_ios_simulator \
		package \
		package_macos_arm64 \
		package_macos_x86_64 \
		package_android \
		package_android_x86_64 \
		package_ios \
		package_ios_simulator \
		depends/gmp/package \
		depends/gmp/package_macos_arm64 \
		depends/gmp/package_macos_x86_64 \
		depends/gmp/package_android_arm64 \
		depends/gmp/package_android_x86_64 \
		depends/gmp/package_ios_arm64 \
		depends/gmp/package_iphone_simulator
