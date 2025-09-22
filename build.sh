#!/bin/bash
set -e

PROJECT_ROOT="$(pwd)"
RAYLIB_DIR="$PROJECT_ROOT/raylib"
RAYLIB_SRC="$RAYLIB_DIR/src"
OUTPUT="$PROJECT_ROOT/index.html"

echo "=== RayPong Web Build ==="

# Step 1: Clone raylib if missing
if [ ! -d "$RAYLIB_DIR" ]; then
    echo "[INFO] Cloning raylib..."
    git clone https://github.com/raysan5/raylib.git "$RAYLIB_DIR"
fi

# Step 2: Build raylib for Web
cd "$RAYLIB_SRC"
if [ ! -f "$RAYLIB_SRC/libraylib.web.a" ]; then
    echo "[INFO] Building raylib for Web..."
    make clean
    make PLATFORM=PLATFORM_WEB
fi
cd "$PROJECT_ROOT"

# Step 3: Compile your project
echo "[INFO] Compiling main.cpp..."
emcc main.cpp -o "$OUTPUT" \
    -I"$RAYLIB_SRC" "$RAYLIB_SRC/libraylib.web.a" \
    -s USE_GLFW=3 -s ASYNCIFY \
    -s FORCE_FILESYSTEM=1 -s ALLOW_MEMORY_GROWTH=1 \
    -DPLATFORM_WEB \
    -s TOTAL_MEMORY=67108864

echo "[SUCCESS] Build finished: $OUTPUT"

# Step 4: Run a local webserver
echo "[INFO] Starting web server on http://localhost:8080 ..."
emrun --no_browser --port 8080 "$PROJECT_ROOT"
