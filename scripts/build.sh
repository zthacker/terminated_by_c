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
echo "📝 Configuring CMake..."
cmake -G "$GENERATOR" -DCMAKE_C_COMPILER="$COMPILER" -DCMAKE_BUILD_TYPE="$BUILD_TYPE" .. 2>&1 | tee cmake_config.log

# Build with verbose output
echo "🔨 Building..."
cmake --build . --verbose 2>&1 | tee cmake_build.log

# Check if executable exists
EXE_PATH=""
case "$BUILD_TYPE" in
    Debug) EXE_PATH="../bin/Debug/terminated_by_c.exe" ;;
    Release) EXE_PATH="../bin/Release/terminated_by_c.exe" ;;
    RelWithDebInfo) EXE_PATH="../bin/RelWithDebInfo/terminated_by_c.exe" ;;
    MinSizeRel) EXE_PATH="../bin/MinSizeRel/terminated_by_c.exe" ;;
esac

if [ -f "$EXE_PATH" ]; then
    echo "✅ Build complete."
    echo "Executable located at: $(realpath $EXE_PATH)"
else
    echo "❌ Build FAILED - executable not found at: $EXE_PATH"
    echo "Check cmake_build.log for errors"
    exit 1
fi