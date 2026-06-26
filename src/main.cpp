#include <iostream>
#include <vector>
#include <raylib.h>
#include "cell.h"
#include "grid.h"

using namespace std;

// Screen Parameters
const int screenWidth = 800;
const int screenHeight = 672;

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
        grid.Update();


// Drawing
//------------------------------------------------------------------------------------------------------------------------------------------------------------------------------
        DrawTexture(topBanner, 0, 0, WHITE);
        grid.Draw();


        EndDrawing();
    }

    CloseWindow();
}