#!/usr/bin/env bash
# LINUX
if [[ $OSTYPE == "linux-gnu"* ]]; then
  clear &&
  echo '[o] Linux detected.' &&
  echo '[o] CMake:' &&
  cmake -B./build -H./ &&
  echo '[o] Make:' &&
  make -C ./build &&
  echo 'Launching program:' &&
  # To-Do: Create a shortcut in the parent directory.
  if [[ $1 == '-v' ]]; then
    echo '[o] Launching program with Valgrind'
    valgrind ./build/sdl2-c-template > log.txt 2>&1
  else
    echo '[o] Launching program:'
    ./build/sdl2-c-template
  fi
# WINDOWS
elif [[ $OSTYPE == "msys" ]] || [[ $OSTYPE == "win32" ]]; then
  clear
  echo '[o] Windows detected.'
  echo '[o] CMake:'
  cmake -B./build -H./
  if [[ $? -ne 0 ]]; then
    echo '[x] Cmake failed.'
    exit 1
  fi
  echo '[o] Ninja:'
  ninja -C ./build 
  if [[ $? -ne 0 ]]; then
    echo '[x] Build failed.'
    exit 1
  fi
  echo '[o] Copying DLLs:'
  cp dlls/* build/
  if [[ $? -ne 0 ]]; then
    echo '[x] Could not copy DLLs into the build folder.'
    exit 1
  fi
  echo '[o] Creating a shortcut in the project directory:'
  powershell '
    $WshShell = New-Object -comObject WScript.Shell
    $Shortcut = $WshShell.CreateShortcut("sdl2-c-template.lnk")
    $Shortcut.TargetPath = (Resolve-Path "build\sdl2-c-template.exe").Path
    $Shortcut.Save() '
  # Find a valgrind alternative for windows.
  # if [[ $1 == '-v' ]]; then 
    # echo '[o] Launching program with Valgrind'
    # valgrind ./build/sdl2-c-template.exe > log.txt 2>&1
  # else
  echo '[o] Launching program:'
  ./build/sdl2-c-template.exe
  # fi
# MACOS
elif [[ $OSTYPE == "darwin"* ]]; then
  clear &&
  echo '[o] MacOS detected.' &&
  echo '[o] CMake:' &&
  cmake -B./build -H./ -GXcode && 
  echo '[o] Make:' &&
  xcodebuild -project ./build/sdl2-c-template.xcodeproj -configuration Release &&
  echo 'Launching program:' &&
  # To-Do: Create a shortcut in the parent directory.
  ./build/Release/sdl2-c-template
fi

# Changed #!/bin/sh to #!/usr/bin/env bash
# Removed "" from $OSTYPE
