#!/bin/bash

OS="$(uname -s)"
if [ "$OS" = "Linux" ]; then
  NPROCS="$(nproc --all)"
elif [ "$OS" = "Darwin" ] || [ "$(echo "$OS" | grep -q BSD)" = "BSD" ]; then
  NPROCS="$(sysctl -n hw.ncpu)"
else
  NPROCS="$(getconf _NPROCESSORS_ONLN)"
fi


cmake -DCMAKE_BUILD_TYPE=Release .. && cmake --build . --parallel "$NPROCS"