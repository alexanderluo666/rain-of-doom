#include "raylib.h"
#include <vector>

struct Player {
    int x;
    int y;
    int speed;
};

struct Obstacle {
    int x;
    int y;
    int speed;
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

    Player player = {375, 550, 5};

    std::vector<Obstacle> obstacles;
    int spawnTimer = 0;

    while (!WindowShouldClose()) {

        // =====================
        // INPUT + LOGIC
        // =====================

        if (gameState == START) {
	    DrawText("Play by pressing Enter",10,10,40,BLACK);
	    DrawText("Use Left and Right Arrow to move",10,50,40,BLACK);
	    DrawText("Try to avoid the obstacles",10,90,40,BLACK);
	    DrawText("Good Luck!",10,130,40,BLACK);
            if (IsKeyPressed(KEY_ENTER)) {
                gameState = PLAY;
            }
        }

        else if (gameState == PLAY) {

            // input
            if (IsKeyDown(KEY_LEFT)) player.x -= player.speed;
            if (IsKeyDown(KEY_RIGHT)) player.x += player.speed;

            if (player.x < 0) player.x = 0;
            if (player.x > 750) player.x = 750;

            // spawn
            spawnTimer++;
            if (spawnTimer > 30) {
                Obstacle o;
                o.x = GetRandomValue(0, 750);
                o.y = 0;
                o.speed = 5;
                obstacles.push_back(o);
                spawnTimer = 0;
            }

            // update obstacles
            for (auto &o : obstacles) {
                o.y += o.speed;
            }

            // collision
            for (auto &o : obstacles) {
                if (o.y > player.y - 20 &&
                    o.x > player.x - 25 &&
                    o.x < player.x + 50) {
                    gameState = GAME_OVER;
                }
            }

            // cleanup
            for (int i = 0; i < obstacles.size(); i++) {
                if (obstacles[i].y > 600) {
                    obstacles.erase(obstacles.begin() + i);
                    i--;
                }
            }
        }

        else if (gameState == GAME_OVER) {
	    DrawText("You failed!",10,10,40,BLACK);
	    DrawText("Press R to try again!",10,50,40,BLACK);
            if (IsKeyPressed(KEY_R)) {
                gameState = START;
                player.x = 375;
                obstacles.clear();
                spawnTimer = 0;
            }
        }

        // =====================
        // DRAW (ALWAYS LAST)
        // =====================

        BeginDrawing();
        ClearBackground(RAYWHITE);

        if (gameState == START) {
            // start screen (empty by request)
        }

        else if (gameState == PLAY) {

            DrawRectangle(player.x, player.y, 50, 50, BLUE);

            for (auto &o : obstacles) {
                DrawRectangle(o.x, o.y, 30, 30, RED);
            }
        }

        else if (gameState == GAME_OVER) {
            // game over screen (empty by request)
        }

        EndDrawing();
    }

    CloseWindow();
}


