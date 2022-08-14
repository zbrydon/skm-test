#!/bin/bash

APP_PATH=`echo $0 | awk '{split($0,patharr,"/"); idx=1; while(patharr[idx+1] != "") { if (patharr[idx] != "/") {printf("%s/", patharr[idx]); idx++ }} }'`

echo APP_PATH: $APP_PATH

APP_PATH=`cd "$APP_PATH"; pwd`

echo APP_PATH: $APP_PATH

SKM_PATH=`cd "$APP_PATH/.."; pwd`

echo APP_PATH: $APP_PATH

source "${SKM_PATH}/tools/set_sk_env_vars.sh"

CPP_OPTIONS="-std=c++14 -g -Wall -Wno-sign-compare"

echo CPP_OPTIONS: $CPP_OPTIONS

if [ "$SK_OS" = "win32" ]; then
    g++ $CPP_OPTIONS -Wl,--as-needed -L"${APP_PATH}/lib/win32" -static-libstdc++ -static-libgcc -lSplashKit -Wl,-Bstatic -lstdc++ -lpthread -I "${APP_PATH}/include" -I "${APP_PATH}/../" -L "${SKM_PATH}/lib/win32" -I "$APP_PATH/src" -I "$APP_PATH/win_include" $* "${APP_PATH}/lib/win32/libSplashKitCpp.a"
elif [ "$SK_OS" = "win64" ]; then
    g++ $CPP_OPTIONS -Wl,--as-needed -L"${APP_PATH}/lib/win64" -static-libstdc++ -static-libgcc -lSplashKit -Wl,-Bstatic -lstdc++ -lpthread -I "${APP_PATH}/include" -I "${APP_PATH}/../" -L "${SKM_PATH}/lib/win64" -I "$APP_PATH/src" -I "$APP_PATH/win_include" $* "${APP_PATH}/lib/win64/libSplashKitCpp.a"
elif [ "$SK_OS" = "macos" ]; then
    clang++ $CPP_OPTIONS -L"$DYLIB_PATH" -lSplashKit -L"${APP_PATH}/lib/macos" -lSplashKitCpp -I "${APP_PATH}/include" -rpath @loader_path -rpath "$DYLIB_PATH" -rpath /usr/local/lib -arch x86_64 $*
elif [ "$SK_OS" = "linux" ]; then
    echo "linux"
    echo clang++ $CPP_OPTIONS -L"$DYLIB_PATH" -L"${APP_PATH}/lib/linux" -I "${APP_PATH}/include" -Wl,-rpath=$ORIGIN -Wl,-rpath="${DYLIB_PATH}" -Wl,-rpath=/usr/local/lib $* -lSplashKitCPP -lSplashKit ${LIBS}
    clang++ $CPP_OPTIONS -L"$DYLIB_PATH" -L"${APP_PATH}/lib/linux" -I "${APP_PATH}/include" -Wl,-rpath=$ORIGIN -Wl,-rpath="${DYLIB_PATH}" -Wl,-rpath=/usr/local/lib $* -lSplashKitCPP -lSplashKit ${LIBS}
else
    echo "Unable to detect operating system..."
    exit 1
fi
