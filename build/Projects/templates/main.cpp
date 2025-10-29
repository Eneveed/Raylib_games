#include "raylib.h"
#include "raymath.h"

int screen_width = 640;
int screen_height = 480;

int main() {

    InitWindow(screen_width, screen_height, "");

    while (!WindowShouldClose()) {
        ClearBackground(BLACK);
        BeginDrawing();
        
        EndDrawing();
    }

    return 0;
}