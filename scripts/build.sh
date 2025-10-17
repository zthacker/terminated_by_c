#!/usr/bin/env bash
set -e

# Default to Release if no argument given
BUILD_TYPE=${1:-Release}
BUILD_DIR="build_${BUILD_TYPE}"
GENERATOR="MinGW Makefiles"
COMPILER="gcc"

echo "🏗️ Building in ${BUILD_TYPE} mode..."

# Clean previous build folder for this type
if [ -d "$BUILD_DIR" ]; then
  echo "🧹 Cleaning previous ${BUILD_TYPE} build..."
  rm -rf "$BUILD_DIR"
fi

mkdir -p "$BUILD_DIR"
cd "$BUILD_DIR"

# Configure
cmake -G "$GENERATOR" -DCMAKE_C_COMPILER="$COMPILER" -DCMAKE_BUILD_TYPE="$BUILD_TYPE" ..

# Build
cmake --build .

# Figure out where the executable is
EXE_PATH=""
case "$BUILD_TYPE" in
    Debug) EXE_PATH="../bin/Debug/terminated_by_c.exe" ;;
    Release) EXE_PATH="../bin/Release/terminated_by_c.exe" ;;
    RelWithDebInfo) EXE_PATH="../bin/RelWithDebInfo/terminated_by_c.exe" ;;
    MinSizeRel) EXE_PATH="../bin/MinSizeRel/terminated_by_c.exe" ;;
esac

echo "✅ Build complete."
echo "Executable located at: $(realpath $EXE_PATH)"
