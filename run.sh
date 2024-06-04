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
  ./build/sdl2-c-template
# WINDOWS
elif [[ $OSTYPE == "msys" ]] || [[ $OSTYPE == "win32" ]]; then
  clear &&
  echo '[o] Windows detected.' &&
  echo '[o] CMake:' &&
  cmake -B./build -H./ &&
  echo '[o] Ninja:' &&
  ninja -C ./build &&
  echo '[o] Copying DLLs:' &&
  cp dlls/* build/ && 
  echo '[o] Creating a shortcut in the project directory:' &&
  powershell '
    $WshShell = New-Object -comObject WScript.Shell
    $Shortcut = $WshShell.CreateShortcut("sdl2-c-template.lnk")
    $Shortcut.TargetPath = (Resolve-Path "build\sdl2-c-template.exe").Path
    $Shortcut.Save() '
  echo '[o] Launching program:' &&
  ./build/sdl2-c-template.exe
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
