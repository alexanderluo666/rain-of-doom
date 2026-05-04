#include "raylib.h"
#include <vector>
#include <random>

struct Obstacle {
    int x;
    int y;
};

int randomInt(int min, int max) {
    static std::random_device rd;
    static std::mt19937 gen(rd());
    std::uniform_int_distribution<> dist(min, max);
    return dist(gen);
}

int main() {
    InitWindow(800, 600, "Rain of Doom");

    SetTargetFPS(60);

    int playerX = 375;
    int spawnTimer = 0;

    std::vector<Obstacle> obstacles;

    while (!WindowShouldClose()) {

        // =====================
        // 1. INPUT
        // =====================
        if (IsKeyDown(KEY_LEFT)) playerX -= 5;
        if (IsKeyDown(KEY_RIGHT)) playerX += 5;

        if (playerX < 0) playerX = 0;
        if (playerX > 750) playerX = 750;

        // =====================
        // 2. SPAWN
        // =====================
        spawnTimer++;
        if (spawnTimer > 30) {
            Obstacle o;
            o.x = randomInt(0, 750);
            o.y = 0;
            obstacles.push_back(o);
            spawnTimer = 0;
        }

        // =====================
        // 3. UPDATE
        // =====================
        for (auto &o : obstacles) {
            o.y += 5;
        }

        // =====================
        // 4. CLEANUP
        // =====================
        for (int i = 0; i < obstacles.size(); i++) {
            if (obstacles[i].y > 600) {
                obstacles.erase(obstacles.begin() + i);
                i--;
            }
        }

        // =====================
        // 5. DRAW
        // =====================
        BeginDrawing();
        ClearBackground(RAYWHITE);

        // player
        DrawRectangle(playerX, 550, 50, 50, BLUE);

        // obstacles
        for (auto &o : obstacles) {
            DrawRectangle(o.x, o.y, 30, 30, RED);
        }

        EndDrawing();
    }

    CloseWindow();
}
