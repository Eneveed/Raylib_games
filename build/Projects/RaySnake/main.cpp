#include "raylib.h"
#include "raymath.h"
#include <iostream>
#include <deque>

int cellSize = 30;
int cellCount = 25;
double lastUpdate = 0;
bool run = true;

bool eventTriggered(double interval) {
    double currentTime = GetTime();

    if (currentTime - lastUpdate >= interval) {
        lastUpdate = currentTime;
        return true;
    }

    return false;
}

bool checkElementInDeque(Vector2 element, std::deque<Vector2> deque) {
    for (unsigned int i = 0; i < deque.size(); i++) {
        if (Vector2Equals(deque[i], element)) {
            return true;
        }
    }
    return false;
} 

class Snake {
public:
    std::deque<Vector2> body = {Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9}};
    Vector2 direction = {1, 0};
    bool addSeg = false;

    void Draw() {
        for (unsigned int i = 0; i < body.size(); i++) {
            int x = body[i].x;
            int y = body[i].y;
            DrawRectangle(x * cellSize, y * cellSize, cellSize, cellSize, GREEN);
        }
    }

    void Update() {
        body.push_front(Vector2Add(body[0], direction));
        if (addSeg) {
            addSeg = false;
        } else {
            body.pop_back();
            
        }
    }

    void Reset() {
        body = {Vector2{6, 9}, Vector2{5, 9}, Vector2{4, 9}};
        direction = {1, 0};
    }
};

class Food {
public:
    Vector2 position;
    Snake snake = Snake();

    Food(std::deque<Vector2> body) {
        position = genRandomPos(snake.body);
    }

    void Draw() {
        DrawRectangle(position.x * cellSize, position.y * cellSize, cellSize, cellSize, RED);
    }

    Vector2 genRandomCell() {
        float y = GetRandomValue(0, cellCount - 1);
        float x = GetRandomValue(0, cellCount - 1);
        return Vector2{x, y};
    }

    Vector2 genRandomPos(std::deque<Vector2> snakeBody) {
        Vector2 position = genRandomCell();
        while (checkElementInDeque(position, snakeBody)) {
            position = genRandomCell();
        }
        return position;
    }
};

class Game {
public:
    Snake snake = Snake();
    Food food = Food(snake.body);

    bool running = true;

    void Draw() {
        food.Draw();
        snake.Draw();
        DrawText(TextFormat("%i", snake.body.size()), cellSize * cellCount / 2, 10, 24, WHITE);
    }

    void Update() {
        if (running) {
            snake.Update();
            checkCollisonWithFood(snake.body);
            checkCollisonWithEdges(snake.body);
            checkCollisionWithTail(snake.body);
        }
    }

    void checkCollisonWithFood(std::deque<Vector2> body) {
        if (Vector2Equals(snake.body[0], food.position)) {
            food.position = food.genRandomPos(snake.body);
            snake.addSeg = true;
        }
    }

    void checkCollisonWithEdges(std::deque<Vector2> body) {
        if (snake.body[0].x == cellCount || snake.body[0].x == -1) {
            GameOver();
        }
        if (snake.body[0].y == cellCount || snake.body[0].y == -1) {
            GameOver();
        }
    }

    void checkCollisionWithTail(std::deque<Vector2> body) {
        std::deque<Vector2> headlessBody = snake.body;
        headlessBody.pop_front();
        if (checkElementInDeque(snake.body[0], headlessBody)) {
            GameOver();
        }
    }

    void GameOver() {
        snake.Reset();
        food.genRandomPos(snake.body);
        running = false;
    }
};

int main() {    
    Game game = Game();

    InitWindow(cellSize * cellCount, cellSize * cellCount, "Snake");
    SetTargetFPS(60);

    while (!WindowShouldClose() && run) {
        ClearBackground(BLACK);

        BeginDrawing();

        if (eventTriggered(0.2)) {
            game.Update();
        }

        if ((IsKeyPressed(KEY_UP) || IsKeyPressed(KEY_W)) && game.snake.direction.y != 1) {
            game.running = true;
            game.snake.direction = {0, -1};
        }
        if ((IsKeyPressed(KEY_DOWN) || IsKeyPressed(KEY_S)) && game.snake.direction.y != -1) {
            game.running = true;
            game.snake.direction = {0, 1};
        }
        if ((IsKeyPressed(KEY_LEFT) || IsKeyPressed(KEY_A)) && game.snake.direction.x != 1) {
            game.running = true;
            game.snake.direction = {-1, 0};
        }
        if ((IsKeyPressed(KEY_RIGHT) || IsKeyPressed(KEY_D)) && game.snake.direction.x != -1) {
            game.running = true;
            game.snake.direction = {1, 0};
        }
        if (IsKeyPressed(KEY_P)) {
            switch (game.running) {
                case false: game.running = true; break;
                case true: game.running = false; break;
            }
        }

        game.Draw();

        EndDrawing();
    }

    CloseWindow();

    return 0;
}