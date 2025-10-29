// prevent player from exiting the roof and walls
// add collision to platforms
// prevent player from fusing into platforms at high speeds

// add guns
// add local multiplayer

#include "raylib.h"
#include "raymath.h"
#include <iostream>

const int SCREEN_WIDTH = 640;
const int SCREEN_HEIGHT = 480;
const double MAX_GRAVITY = 10;
double gravity = 0.1;

class Player {
public:
    int health;
    float x, y;
    float speed_x, speed_y;
    float size;
    bool isOnGround;

    void Draw() {
        DrawRectangle(x, y, size, size, BLACK);
    }

    void Update(double gravity) {
        y += gravity;
    }
};

int main() {

    Player player = Player();

    player.health = 100;
    player.x = SCREEN_WIDTH / 2 - player.size / 2;
    player.y = SCREEN_HEIGHT / 2 - player.size / 2;
    player.speed_x = 3;
    player.speed_y = 5;
    player.size = 20;
    player.isOnGround = false;

    InitWindow(SCREEN_WIDTH, SCREEN_HEIGHT, "platformer");
    SetTargetFPS(60);

    while (!WindowShouldClose()) {
        ClearBackground(LIGHTGRAY);
        BeginDrawing();

        if (CheckCollisionRecs(Rectangle {player.x, player.y, player.size, player.size}, Rectangle {0, SCREEN_HEIGHT - 80, SCREEN_WIDTH, SCREEN_HEIGHT}) || CheckCollisionRecs(Rectangle {player.x, player.y, player.size, player.size}, Rectangle {20, 360, 100, 10})) {
            player.isOnGround = true;
        } else {
            player.isOnGround = false;
        }

        if (player.isOnGround) {// if player is colliding with the floor rectangle gravity = 0, else increase gravity
            gravity = 0;
        } else if (gravity != MAX_GRAVITY) {
            gravity += 0.2;
        }
        

        // checks if the up arrow || w || or space is pressed, players y pos is less the top of the border, and if its colliding with floor
        if ((IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W) || IsKeyDown(KEY_SPACE)) && player.y > 0 && player.isOnGround) {
            gravity -= player.speed_y;
        }
        if ((IsKeyDown(KEY_LEFT) || IsKeyDown(KEY_A)) && player.x > 0) { // left
            player.x -= player.speed_x;
        }
        if ((IsKeyDown(KEY_RIGHT) || IsKeyDown(KEY_D)) && player.x + player.size != SCREEN_WIDTH) { // right
            player.x += player.speed_x;
        }
        
        
        player.Draw();
        player.Update(gravity);

        // floor
        DrawRectangle(0, SCREEN_HEIGHT - 80, SCREEN_WIDTH, SCREEN_HEIGHT, GRAY);
        // platform
        DrawRectangle(20, 360, 100, 10, GRAY);
        DrawRectangle(SCREEN_WIDTH - 120, 360, 100, 10, GRAY);
        DrawRectangle(SCREEN_WIDTH / 2 - 40, 360, 100, 10, GRAY);
        // Menu Seperator
        DrawLine(0, 20, SCREEN_WIDTH, 20, BLACK);
        // player health
        DrawText(TextFormat("%i", player.health), 5, 1, 19, BLACK);
        DrawText(TextFormat("%i", player.isOnGround), 20, 20, 19, BLACK);

        EndDrawing();
    }

    CloseWindow();

    return 0;
}