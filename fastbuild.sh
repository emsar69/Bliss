#!/bin/bash

# for merging newer versions:
# apkeditor m -i .

# I recommend using cmake instead. But this script also creates apk so I won't add this to .gitignore
C=/opt/android-ndk/toolchains/llvm/prebuilt/linux-x86_64/bin/aarch64-linux-android21-clang
CXX=/opt/android-ndk/toolchains/llvm/prebuilt/linux-x86_64/bin/aarch64-linux-android21-clang++
APK=build/apk
KEY_PASS=123456
ABI=arm64-v8a # 64bit=arm64-v8a | 32bit=armeabi-v7a

cmake -B build -G Ninja -DCMAKE_C_COMPILER=${C} -DCMAKE_CXX_COMPILER=${CXX} -DCMAKE_ANDROID_NDK=/opt/android-ndk -DANDROID_ABI=${ABI}

ninja -C build

cp build/libBliss.so base/lib/arm64-v8a/libbliss.so
mkdir -p ${APK}
rm -rf ${APK}/*

apktool b base -o ${APK}/amongus.apk
uber-apk-signer --apks ${APK}/amongus.apk --ks key.jks --ksAlias key --ksPass ${KEY_PASS} --ksKeyPass ${KEY_PASS} -o ${APK}
rm ${APK}/amongus.apk ${APK}/amongus-aligned-signed.apk.idsig

# If you don't have a key you can run:
# keytool -genkeypair -v -keystore key.jks -alias key -keyalg RSA -keysize 2048 -validity 10000 