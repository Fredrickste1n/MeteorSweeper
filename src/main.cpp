#include <iostream>
#include <vector>
#include <raylib.h>
#include "cell.h"
#include "grid.h"

using namespace std;

// Game Attributes
bool isGameStart = false;
bool isPlayerLose = false;
bool isPlayerWin = false;
bool isShowControls = false;
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
    Texture2D gameWonBox = LoadTexture("textures/gameWonBox.png");
    Texture2D controlsPage = LoadTexture("textures/controlsPage.png");

    // Grid Declaration and initilization
    //---------------------------------------------------------------
    Grid grid(0, 64, 32);

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);


// Updating
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        // Starting game from main menue
        if(isGameStart) {
            // When player does first click
            if(firstClick) {
                if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                    grid.FirstClick();
                    firstClick = false;
                }
            } else if(!isPlayerLose && !isPlayerWin){ // Update gameTime after first click and while game is running
                gameTime++;
            }

            // Update grid while game is running
            if(!isPlayerLose && !isPlayerWin) {
                grid.Update(isPlayerLose, isPlayerWin);
            }

            // Checks for restart keystroke (SPACE)
            if(IsKeyPressed(KEY_SPACE)) {
                grid.grid.clear();
                grid.FillGrid();
                firstClick = true;
                gameTime = 0;
                isPlayerLose = false;
                isPlayerWin = false;
            }

            // Checks for return to homescreen keystroke (BACKSPACE)
            if(IsKeyPressed(KEY_BACKSPACE)) {
                isGameStart = false;
            }

        } else {    // Checks for start game keystroke (ENTER)
            if(IsKeyPressed(KEY_ENTER) && !isShowControls) {
                isGameStart = true;
                grid.grid.clear();
                grid.FillGrid();
                firstClick = true;
                gameTime = 0;
                isPlayerLose = false;
                isPlayerWin = false;
            }

            // Shows player's controls screen
            if(IsKeyPressed(KEY_RIGHT_SHIFT) || IsKeyPressed(KEY_LEFT_SHIFT)) {
                isShowControls = true;
            } else if(isShowControls && IsKeyPressed(KEY_BACKSPACE)) {
                isShowControls = false;
            }
        }

// Drawing
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        if(isGameStart) {
            DrawTexture(topBanner, 0, 0, WHITE);
            DrawText(TextFormat("%04i", gameTime / 60), screenWidth - 112, 16, 40, textColor);

            grid.Draw();

            if(isPlayerWin) {
                DrawTexture(gameWonBox, 272, 272, WHITE);
                DrawText(TextFormat("You won in \n %i seconds", gameTime / 60), 336, 312, 20, textColor);
            }
        } else {
            DrawTexture(mainMenu, 0, 0, WHITE);
            DrawText("Press ENTER to play", 64, 512, 45, Color{230, 190, 231, 255});
            DrawText("Press SHIFT to see controls", 64, 552, 45, Color{230, 190, 231, 255});

            if(isShowControls) {
                DrawTexture(controlsPage, 0, 0, WHITE);
                DrawText("ENTER: Start game", 64, 64, 45, Color{230, 190, 231, 255});
                DrawText("BACKSPACE: Go back", 64, 112, 45, Color{230, 190, 231, 255});
                DrawText("SPACE: Restart", 64, 160, 45, Color{230, 190, 231, 255});
                DrawText("SHIFT: Open control menu", 64, 208, 45, Color{230, 190, 231, 255});
                DrawText("LEFT CLICK: Flip tile", 64, 256, 45, Color{230, 190, 231, 255});
                DrawText("RIGHT CLICK: Flag tile", 64, 304, 45, Color{230, 190, 231, 255});
            }
        }

        EndDrawing();
    }

    CloseWindow();
}