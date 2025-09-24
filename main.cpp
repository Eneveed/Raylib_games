#include "raylib.h"
#include <iostream> 
#include <deque>
#include <utility>

int cellSize = 20;
int gridWidth = 35;
int gridHeight = 35;
int screen_width = cellSize * gridWidth;
int screen_height = cellSize * gridHeight;

class snake {
public:
    std::deque<std::pair< int, int >> body = {{4, 2}, {3, 2}, {2, 2}};

    void Draw() {
        for (int i = 0; i < body.size(); i ++) {
            DrawRectangle(body[i].first, body[i].second, cellSize, cellSize, GREEN);
        }
    }

    void Update() {
        body.pop_back();
        body.push_front({});
    }
};

snake player = snake();

int main() {
    

    InitWindow(cellSize * gridWidth, cellSize * gridHeight, "RaySnake");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        ClearBackground(BLACK);
        BeginDrawing();

        player.Draw();

        EndDrawing();
    }

    CloseWindow();
}