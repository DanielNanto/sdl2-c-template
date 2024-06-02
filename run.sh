#!/bin/sh
# LINUX
if [ "$OSTYPE" == "linux-gnu"* ]; then
  clear &&
  echo '[o] Linux detected.' &&
  echo '[o] CMake:' &&
  cmake -B./build -H./ &&
  echo '[o] Make:' &&
  make -C ./build &&
  echo 'Launching program:' &&
  ./build/sdl2-c-template
# WINDOWS
elif [ "$OSTYPE" == "msys" ] || [ "$OSTYPE" == "win32" ]; then
  clear &&
  echo '[o] Windows detected.' &&
  echo '[o] CMake:' &&
  cmake -B./build -H./ &&
  echo '[o] Ninja:' &&
  ninja -C ./build &&
  echo '[o] Launching program:' &&
  ./build/sdl2-c-template.exe
# MACOS
elif [[ "$OSTYPE" == "darwin"* ]]; then
  clear &&
  echo '[o] MacOS detected.' &&
  echo '[o] CMake:' &&
  cmake -B./build -H./ -GXcode && 
  echo '[o] Make:' &&
  xcodebuild -project ./build/sdl2-c-template.xcodeproj -configuration Release &&
  echo 'Launching program:' &&
  ./build/Release/sdl2-c-template
fi