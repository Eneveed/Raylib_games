#include "raylib.h"
#include <iostream> 

int main() {
    const int screen_width = 640;
    const int screen_height = 480;

    InitWindow(screen_width, screen_height, "RaySnake");

    while (!WindowShouldClose()) {
        ClearBackground(BLACK);
        BeginDrawing();

        EndDrawing();
    }

    CloseWindow();
}