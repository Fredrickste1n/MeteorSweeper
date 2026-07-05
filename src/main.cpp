#include <iostream>
#include <vector>
#include <raylib.h>
#include "cell.h"
#include "grid.h"

using namespace std;

// Game Attributes
bool isGameStart = false;
bool playerLose = false;
int gameTime = 0;
const Color textColor = Color{123, 31, 162, 255};
bool firstClick = true;

// Screen Parameters
const int screenWidth = 800;
const int screenHeight = 672;



int main() {
    InitWindow(screenWidth, screenHeight, "MeteorSweeper");
    SetTargetFPS(60);

    // Screen Textures
    //---------------------------------------------------------------
    Texture2D mainMenu = LoadTexture("textures/mainMenu.png");
    Texture2D topBanner = LoadTexture("textures/topBanner.png");

    // Grid Declaration and initilization
    //---------------------------------------------------------------
    Grid grid(0, 64, 32);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);


// Updating
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        if(isGameStart) {
            if(firstClick) {
                if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    grid.FirstClick();
                    firstClick = false;
                }
            } else if(!playerLose){
                gameTime++;
            }

            if(!playerLose) {
                grid.Update(playerLose);
            }

            if(IsKeyPressed(KEY_ENTER)) {
                grid.grid.clear();
                grid.FillGrid();
                firstClick = true;
                gameTime = 0;
                playerLose = false;
            }

            if(IsKeyPressed(KEY_BACKSPACE)) {
                isGameStart = false;
            }

        } else {
            if(IsKeyPressed(KEY_ENTER)) {
                isGameStart = true;
                grid.grid.clear();
                grid.FillGrid();
                firstClick = true;
                gameTime = 0;
                playerLose = false;
            }
        }

// Drawing
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        if(isGameStart) {
            DrawTexture(topBanner, 0, 0, WHITE);
            DrawText(TextFormat("%04i", gameTime / 60), screenWidth - 112, 16, 40, textColor);

            grid.Draw();
        } else {
            DrawTexture(mainMenu, 0, 0, WHITE);
        }

        EndDrawing();
    }

    CloseWindow();
}