#include <raylib.h>
#include <iostream>

Color Green = Color{38, 185, 150, 255};
Color Dark_Green = Color{20, 160, 133, 255};
Color Light_Green = Color{129, 204, 184, 255};
Color Yellow = Color{243, 213, 91, 255};

int player_score = 0;
int ai_score = 0;

class ball {
public:
    float x, y;
    int speed_x, speed_y;
    int radius;

    void Draw() {
        DrawCircle(x, y, radius, Yellow);
    }

    void Update() {
        x += speed_x;
        y += speed_y;

        if (y + radius >= GetScreenHeight() || y - radius <= 0) {
            speed_y *= -1;
        }

        if (x + radius >= GetScreenWidth()) {
            ai_score++;
            reset();
        }
        if (x - radius <= 0) {
            player_score++;
            reset();
        }
    }

    void reset() {
        x = GetScreenWidth() / 2;
        y = GetScreenHeight() / 2;
    
        int speed_choices[2] = {-1, 1};
        speed_x *= speed_choices[GetRandomValue(0, 1)];
        speed_y *= speed_choices[GetRandomValue(0, 1)];
    }
};

class paddle {
protected:
    void LimitMovement() {
        if (y <= 0) {
            y = 0;
        }
        if (y + height >= GetScreenHeight()) {
            y = GetScreenHeight() - height;
        }
    }
public:
    float x, y;
    float width, height;
    int speed;

    void Draw() {
        DrawRectangleRounded(Rectangle{x, y, width, height}, 0.8, 0, WHITE);
    }

    void Update() {
        if (IsKeyDown(KEY_UP)) {
            y -= speed;
        }
        if (IsKeyDown(KEY_DOWN)) {
            y += speed;
        }

        LimitMovement();
    }
}; 

class aiPaddle: public paddle {
public:
    void Update(int ball_y) {
        if (y + height / 2 > ball_y) {
            y -= speed;
        }

        if (y + height / 2 <= ball_y) {
            y += speed;
        }

        LimitMovement();
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

        // Clear Background
        ClearBackground(Dark_Green);

        // Update
        ball.Update();
        player.Update();
        ai.Update(ball.y);

        if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{player.x, player.y, player.width, player.height})) {
            ball.speed_x *= -1;
        }

        if (CheckCollisionCircleRec(Vector2{ball.x, ball.y}, ball.radius, Rectangle{ai.x, ai.y, ai.width, ai.height})) {
            ball.speed_x *= -1;
        }

        // Decor, makes ai side darker
        DrawRectangle(screen_width / 2, 0, screen_width / 2, screen_height, Green); 
        // Decor, middle circle
        DrawCircle(screen_width / 2, screen_height / 2, 150, Light_Green);
        // Decor, middle line
        DrawLine(screen_width / 2, 0, screen_width / 2, screen_height, WHITE);
        // draw ball
        ball.Draw();
        // draw ai
        ai.Draw();
        // draw player 
        player.Draw();
        // draw ai score
        DrawText(TextFormat("%i", ai_score), screen_width / 4, 20, 80, WHITE);
        // draw player score
        DrawText(TextFormat("%i", player_score), 3 * screen_width / 4, 20, 80, WHITE);
        
        EndDrawing();
    }

    CloseWindow();

    return 0;
}
