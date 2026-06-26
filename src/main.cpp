#include <iostream>
#include <vector>
#include <raylib.h>
#include "cell.h"
#include "grid.h"

using namespace std;

// Screen Parameters
const int screenWidth = 800;
const int screenHeight = 672;

// Game Contents
int gameTime = 0;
const Color textColor = Color{123, 31, 162, 255};
bool firstClick = true;

int main() {
    InitWindow(screenWidth, screenHeight, "MeteorSweeper");
    SetTargetFPS(60);

    // Screen Textures
    //---------------------------------------------------------------
    Texture2D topBanner = LoadTexture("textures/topBanner.png");

    // Grid Declaration and initilization
    //---------------------------------------------------------------
    Grid grid(0, 64, 32);
    grid.FillGrid();

    while (!WindowShouldClose()) {
        BeginDrawing();
        ClearBackground(BLACK);

// Updating
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        if(firstClick) {
            if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                grid.FirstClick();
                firstClick = false;
            }
        }
        else {
            gameTime++;
        }

        grid.Update();

// Drawing
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        DrawTexture(topBanner, 0, 0, WHITE);
        DrawText(TextFormat("%04i", gameTime / 60), screenWidth - 112, 16, 40, textColor);

        grid.Draw();


        EndDrawing();
    }

    CloseWindow();
}