#include <raylib.h>
#include <iostream>

class ball {
public:
    float x, y;
    int speed_x, speed_y;
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

class paddle {
public:
    float x, y;
    float width, height;
    int speed;

    void Draw() {
        DrawRectangle(x, y, width, height, WHITE);
    }

    void Update() {
        if (IsKeyDown(KEY_UP)) {
            y -= speed;
        }
        if (IsKeyDown(KEY_DOWN)) {
            y += speed;
        }

        if (y <= 0) {
            y = 0;
        }
        if (y + height >= GetScreenHeight()) {
            y = GetScreenHeight() - height;
        }
    }
}; 

class aiPaddle: public paddle {
public:
    void Update(int ball_y) {
        if (y + height / 2 > ball_y) {
            y = y - speed;
        }

        if (y + height / 2 <= ball_y) {
            y -= speed;
        }
    }
};

int main() {
    ball ball;
    paddle player;
    aiPaddle ai;

    std::cout << "booting" << '\n';

    const int screen_width = 1280;
    const int screen_height = 800;

    ball.radius = 20;
    ball.x = screen_width / 2;
    ball.y = screen_height / 2;
    ball.speed_x = 7;
    ball.speed_y = 7;

    player.width = 25;
    player.height = 120;
    player.x = screen_width - player.width - 10;
    player.y = screen_height / 2 - player.height / 2;
    player.speed = 6;

    ai.width = 25;
    ai.height = 120;
    ai.x = 10;
    ai.y = screen_height / 2 - ai.height / 2;
    ai.speed = 6;

    InitWindow(screen_width, screen_height, "raypong"); // initializes window
    SetTargetFPS(60); // sets game speed and fps

    while (!WindowShouldClose()) {
        BeginDrawing();

        // Update
        ball.Update();
        player.Update();

        // Clear Background
        ClearBackground(BLACK);
        // draw middle line
        DrawLine(screen_width / 2, 0, screen_width / 2, screen_height, WHITE);
        // draw ball
        ball.Draw();
        // draw ai
        ai.Draw();
        // draw player 
        player.Draw();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}