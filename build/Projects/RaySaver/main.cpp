#include "raylib.h"
#include "iostream"

int screen_width = 640;
int screen_height = 480;

class Ball {
public:
    int speed_x, speed_y;
    int x, y;
    int radius;

    void Draw() {
        DrawCircle(x, y, radius, WHITE);
    }

    void Update() {
        x += speed_x;
        y += speed_y;

        if (y + radius >= GetScreenHeight() || y - radius <= 0) {
            speed_y *= -1;
        }
        if (x + radius >= GetScreenWidth() || x - radius <= 0) {
            speed_x *= -1;
        }
    }
};

Ball ball = Ball();

int main() {

    InitWindow(screen_width, screen_height, "RaySaver");
    SetTargetFPS(60);

    ball.speed_x = 10;
    ball.speed_y = 10;
    ball.x = screen_width / 2;
    ball.y = screen_height / 2;
    ball.radius = 20;

    while (!WindowShouldClose()) {
        ClearBackground(BLACK);
        BeginDrawing();

        
        if (IsWindowMaximized()) {
            screen_height = 1517;
            screen_width = 852;
            InitWindow(screen_width, screen_height, "RaySave");
        }
        
        ball.Draw();
        ball.Update();
       
        EndDrawing();
    }

    CloseWindow();

    return 0;
}