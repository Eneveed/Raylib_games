#!/bin/bash
set -e

echo "=== Raylib Web Build ==="

# Go to repository root
cd "$(dirname "$0")"

# Loads emscripten env if not already loaded
if ! command -v emcc &>/dev/null; then
    echo "[INFO] Loading emscripten environment..."
    if [ -f "./emsdk/emsdk_env.sh" ]; then
        source ./emsdk/emsdk_env.sh
    else
        echo "[ERROR] emsdk_env.sh not found. Did you install emsdk in ./emsdk?"
        exit 1
    fi
fi

# Build raylib if libraylib.a is missing
if [ ! -f raylib/src/libraylib.web.a ]; then
    echo "[ERROR] raylib/src/libraylib.web.a not found!"
    echo "[INFO] Building raylib"
    cd raylib/src
    emmake make PLATFORM=PLATFORM_WEB -j$(nproc)
    cd ../../
fi

# Make build dir
mkdir -p build

# Compile your game
echo "[INFO] Compiling main.cpp..."
emcc main.cpp \
    -o build/index.html \
    -Iraylib/src raylib/src/libraylib.web.a \
    -s USE_GLFW=3 -s ASYNCIFY \
    -s FORCE_FILESYSTEM=1 -s ALLOW_MEMORY_GROWTH=1 \
    -DPLATFORM_WEB \
    -s INITIAL_MEMORY=67108864

echo "[INFO] Build finished"
echo "[INFO] Opening Emscriptem server..."

emrun --no_browser --port 8080 build/index.html