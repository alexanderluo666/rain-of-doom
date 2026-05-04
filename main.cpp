#include "raylib.h"

int main() {
    InitWindow(800, 600, "Dodge Game");

    int playerX = 375;

    SetTargetFPS(60);

    while (!WindowShouldClose()) {


        if (IsKeyDown(KEY_LEFT)) playerX -= 5;
        if (IsKeyDown(KEY_RIGHT)) playerX += 5;

        if (playerX < 0) playerX = 0;
        if (playerX > 750) playerX = 750;


        BeginDrawing();
        ClearBackground(RAYWHITE);

        DrawRectangle(playerX, 550, 50, 50, BLUE);

        EndDrawing();
    }

    CloseWindow();
}
