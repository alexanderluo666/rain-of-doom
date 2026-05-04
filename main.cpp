#include "raylib.h"
#include <vector>
#include <iostream>

struct Player {
    float x;
    float y;
    float velocityX;
    float velocityY;
    float speed;
    bool onGround;
    int health;
};

struct Obstacle {
    float x;
    float y;
    float speed;
};

enum GameState {
    START,
    PLAY,
    GAME_OVER
};

int main() {
    InitWindow(800, 600, "Rain of Doom");
    SetTargetFPS(60);

    GameState gameState = START;

    Player player = {375, 550, 0, 0, 6, true, 3};

    std::vector<Obstacle> obstacles;
    int spawnTimer = 0;

    float score = 0;

    const float gravity = 0.6f;
    const float jumpPower = -12.0f;

    while (!WindowShouldClose()) {

        // =====================
        // INPUT + LOGIC
        // =====================

        if (gameState == START){
            DrawText("Press ENTER to Start", 200, 250, 20, BLACK);	
            if (IsKeyPressed(KEY_ENTER)) {
                gameState = PLAY;
                // reset everything
                player.x = 375;
                player.y = 550;
                player.velocityX = 0;
                player.velocityY = 0;
                player.health = 3;
                player.onGround = true;

                obstacles.clear();
                spawnTimer = 0;
                score = 0;
            }
        }

        else if (gameState == PLAY) {

            // =====================
            // INPUT (movement + jump)
            // =====================

            if (IsKeyDown(KEY_LEFT)) player.velocityX -= 0.5f;
            if (IsKeyDown(KEY_RIGHT)) player.velocityX += 0.5f;

            if (IsKeyPressed(KEY_SPACE) && player.onGround) {
                player.velocityY = jumpPower;
                player.onGround = false;
            }

            // friction
            player.velocityX *= 0.85f;

            if (player.velocityX > player.speed) player.velocityX = player.speed;
            if (player.velocityX < -player.speed) player.velocityX = -player.speed;

            player.x += player.velocityX;

            // =====================
            // GRAVITY + VERTICAL MOVE
            // =====================

            player.velocityY += gravity;
            player.y += player.velocityY;

            // ground collision
            if (player.y >= 550) {
                player.y = 550;
                player.velocityY = 0;
                player.onGround = true;
            }

            // boundaries
            if (player.x < 0) player.x = 0;
            if (player.x > 750) player.x = 750;

            // =====================
            // SCORE SYSTEM
            // =====================

            score += GetFrameTime();

            // =====================
            // DIFFICULTY
            // =====================

            float difficulty = 1.0f + score * 0.15f;

            float spawnRate = 30.0f / difficulty;

            // =====================
            // SPAWN
            // =====================

            spawnTimer++;
            if (spawnTimer > spawnRate) {
                Obstacle o;
                o.x = GetRandomValue(0, 750);
                o.y = 0;
                o.speed = 4.0f * difficulty;
                obstacles.push_back(o);
                spawnTimer = 0;
            }

            // =====================
            // UPDATE OBSTACLES
            // =====================

            for (auto &o : obstacles) {
                o.y += o.speed;
            }

            // =====================
            // COLLISION (AABB SIMPLE)
            // =====================

            for (auto &o : obstacles) {
                if (o.y > player.y - 20 &&
                    o.y < player.y + 50 &&
                    o.x > player.x - 25 &&
                    o.x < player.x + 50) {

                    player.health--;

                    o.y = 9999; // remove hit obstacle

                    if (player.health <= 0) {
                        gameState = GAME_OVER;
                    }
                }
            }

            // =====================
            // CLEANUP
            // =====================

            for (int i = 0; i < obstacles.size(); i++) {
                if (obstacles[i].y > 600) {
                    obstacles.erase(obstacles.begin() + i);
                    i--;
                }
            }
        }

        else if (gameState == GAME_OVER) {
            float difficulty = 1.0f + score * 0.15f;

            DrawText("GAME OVER", 280, 200, 30, RED);

    	    DrawText(TextFormat("Score: %.2f", score), 280, 260, 20, BLACK);

    	    DrawText(TextFormat("Difficulty: %.2f", difficulty), 280, 290, 20, BLACK);

   	    DrawText("Press R to Restart", 240, 340, 20, BLACK);

    	    if (IsKeyPressed(KEY_R)) {
                gameState = START;
            }
        }

        // =====================
        // DRAW
        // =====================

        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (gameState == PLAY) {

            DrawRectangle((int)player.x, (int)player.y, 50, 50, BLUE);

            for (auto &o : obstacles) {
                DrawRectangle((int)o.x, (int)o.y, 30, 30, RED);
            }
        }

        EndDrawing();
    }

    CloseWindow();
}

