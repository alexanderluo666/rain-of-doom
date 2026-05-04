#include "raylib.h"

int main() {
    InitWindow(800, 600, "Dodge Game");

    int playerX = 375;

    while (!WindowShouldClose()) {
        // Input
        if (IsKeyDown(KEY_LEFT)) playerX -= 5;
        if (IsKeyDown(KEY_RIGHT)) playerX += 5;

        // Draw
        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawRectangle(playerX, 550, 50, 50, BLUE);

        EndDrawing();
    }

    CloseWindow();
}
