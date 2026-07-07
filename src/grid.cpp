#include <iostream>
#include <vector>
#include <raylib.h>
#include "grid.h"
#include "cell.h"

using namespace std;

Color numColor = Color{117, 84, 122, 255};

// Constructor
//---------------------------------------------------------------------------------------------------------------------------------------------------------
Grid::Grid(float xPos, float yPos, float cellDim) {
    x = xPos;
    y = yPos;
    cellDimensions = cellDim;
    cellBack = LoadTexture("textures/cellTextures/cellBack.png");
    cellFront = LoadTexture("textures/cellTextures/cellFront.png");
    cellMeteor = LoadTexture("textures/cellTextures/cellMeteor.png");
    cellFlagged = LoadTexture("textures/cellTextures/cellFlagged.png");
}

// Method Declarations
//---------------------------------------------------------------------------------------------------------------------------------------------------------
void Grid::Draw() {
    for(std::vector<Cell> col : grid) {
        for(Cell cell : col) {

            // Not turned and not flagged
            if(!cell.isTurned && !cell.isFlagged) {
                DrawTexture(cellBack, cell.x, cell.y, WHITE);
            }

            // Not turned and is flagged
            else if(!cell.isTurned && cell.isFlagged) {
                DrawTexture(cellFlagged, cell.x, cell.y, WHITE);
            }

            // Is turned and not a meteor
            else if(cell.isTurned && !cell.isMeteor) {
                DrawTexture(cellFront, cell.x, cell.y, WHITE);
            }

            // Is turned and is a meteor
            else if(cell.isTurned && cell.isMeteor) {
                DrawTexture(cellMeteor, cell.x, cell.y, WHITE);
            }

            // Drawing adjacentMeteors on cells
            if(cell.isTurned && !cell.isMeteor && cell.adjacentMeteors != 0) {
                DrawText(TextFormat("%i", cell.adjacentMeteors), cell.x + cell.width / 3, cell.y + cell.height / 3, 20, numColor);
            }
        }
    }
}

void Grid::Update(bool & isPlayerLose, bool & isPlayerWin) {
    IsCellClicked(isPlayerLose);
    //FlipAllCells(); // Game testing method not intended for finished game
    GameWin(isPlayerWin);
}

void Grid::FillGrid() {
    for(int i = 0; i < GetScreenWidth() / cellDimensions; i++) {
        std::vector<Cell> column;
        for(int j = 0; j < (GetScreenHeight() - 64) / cellDimensions; j++) {
            bool isCellMeteor = false;
            if(GetRandomValue(1, 7) == 1) { // Ratio of 1:8
                isCellMeteor = true;
            } 
            
            column.push_back(Cell{x + cellDimensions * i, y + cellDimensions * j, cellDimensions, cellDimensions, 0, isCellMeteor, false, false});
        }
        grid.push_back(column);
    }
}

void Grid::IsCellClicked(bool & playerLose) {
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT) || IsMouseButtonPressed(MOUSE_BUTTON_RIGHT)) {
        for(int i = 0; i < (int)grid.size(); i++) {
            for(int j = 0; j < (int)grid.at(0).size(); j++) {
                Rectangle cellRec = {grid.at(i).at(j).x, grid.at(i).at(j).y, grid.at(i).at(j).width, grid.at(i).at(j).height};
                if(CheckCollisionPointRec(GetMousePosition(), cellRec)) {
                    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                        grid.at(i).at(j).isTurned = true;
                        if(grid.at(i).at(j).isMeteor) {
                            playerLose = true;
                        } else {
                            TurnSurroundingCells(i, j);
                        }
                        
                    }
                    else {
                        if(grid.at(i).at(j).isFlagged) {
                            grid.at(i).at(j).isFlagged = false;
                        }
                        else {
                            grid.at(i).at(j).isFlagged = true;
                        }
                    }
                }
            }
        }
    }
}

void Grid::CheckForMeteors() {
    for(int i = 0; i < (int)grid.size(); i++) {
        for(int j = 0; j < (int)grid.at(0).size(); j++) {
            // Checks all 8 adjacent cells for being a meteor and detects border cells so no out of bounds
            if(j > 0) {
                if(i > 0) {
                    if(grid.at(i - 1).at(j - 1).isMeteor) grid.at(i).at(j).adjacentMeteors++;
                }
                if(grid.at(i).at(j - 1).isMeteor) grid.at(i).at(j).adjacentMeteors++;
                if(i < (int)grid.size() - 1) {
                    if(grid.at(i + 1).at(j - 1).isMeteor) grid.at(i).at(j).adjacentMeteors++;
                }
            }

            if(i > 0) {
                if(grid.at(i - 1).at(j).isMeteor) grid.at(i).at(j).adjacentMeteors++;
            }
            if(i < (int)grid.size() - 1) {
                if(grid.at(i + 1).at(j).isMeteor) grid.at(i).at(j).adjacentMeteors++;
            }

            if(j < (int)grid.at(0).size() - 1) {
                if(i > 0) {
                    if(grid.at(i - 1).at(j + 1).isMeteor) grid.at(i).at(j).adjacentMeteors++;
                }
                if(grid.at(i).at(j + 1).isMeteor) grid.at(i).at(j).adjacentMeteors++;
                if(i < (int)grid.size() - 1) {
                    if(grid.at(i + 1).at(j + 1).isMeteor) grid.at(i).at(j).adjacentMeteors++;
                }
            }
        }
    }
}

vector<int> Grid::GetClickedCell() {
    vector<int> cellIndex;

    // Creates the starting area around player's first click
    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
        for(int i = 0; i < (int)grid.size(); i++) {
            for(int j = 0; j < (int)grid.at(0).size(); j++) {
                Rectangle cellRec = {grid.at(i).at(j).x, grid.at(i).at(j).y, grid.at(i).at(j).width, grid.at(i).at(j).height};
                if(CheckCollisionPointRec(GetMousePosition(), cellRec)) {
                    if(IsMouseButtonPressed(MOUSE_BUTTON_LEFT)) {
                        grid.at(i).at(j).isMeteor = false;
                        grid.at(i).at(j).isTurned = true;
                        
                        cellIndex.push_back(i);
                        cellIndex.push_back(j);
                    }
                }
            }
        }
    }

    return cellIndex;
}

void Grid::TurnSurroundingCells(int xIndex, int yIndex) {
    if(grid.at(xIndex).at(yIndex).adjacentMeteors == 0) {
        if(yIndex > 0) {
            if(xIndex > 0 && !grid.at(xIndex - 1).at(yIndex - 1).isTurned) {
                grid.at(xIndex - 1).at(yIndex - 1).isTurned = true;
                TurnSurroundingCells(xIndex - 1, yIndex - 1);
            }

            if(!grid.at(xIndex).at(yIndex - 1).isTurned) {
                grid.at(xIndex).at(yIndex - 1).isTurned = true;
                TurnSurroundingCells(xIndex, yIndex - 1);
            }

            if(xIndex < (int)grid.size() - 1 && !grid.at(xIndex + 1).at(yIndex - 1).isTurned) {
                grid.at(xIndex + 1).at(yIndex - 1).isTurned = true;
                TurnSurroundingCells(xIndex + 1, yIndex - 1);
            }
        }

        if(xIndex > 0 && !grid.at(xIndex - 1).at(yIndex).isTurned) {
            grid.at(xIndex - 1).at(yIndex).isTurned = true;
            TurnSurroundingCells(xIndex - 1, yIndex);
        }
        if(xIndex < (int)grid.size() - 1 && !grid.at(xIndex + 1).at(yIndex).isTurned) {
            grid.at(xIndex + 1).at(yIndex).isTurned = true;
            TurnSurroundingCells(xIndex + 1, yIndex);
        }

        if(yIndex < (int)grid.at(0).size() - 1) {
            if(xIndex > 0 && !grid.at(xIndex - 1).at(yIndex + 1).isTurned) {
                grid.at(xIndex - 1).at(yIndex + 1).isTurned = true;
                TurnSurroundingCells(xIndex - 1, yIndex + 1);
            }

            if(!grid.at(xIndex).at(yIndex + 1).isTurned) {
                grid.at(xIndex).at(yIndex + 1).isTurned = true;
                TurnSurroundingCells(xIndex, yIndex + 1);
            }
            
            if(xIndex < (int)grid.size() - 1 && !grid.at(xIndex + 1).at(yIndex + 1).isTurned) {
                grid.at(xIndex + 1).at(yIndex + 1).isTurned = true;
                TurnSurroundingCells(xIndex + 1, yIndex + 1);
            }
        }
    }
}

void Grid::FirstClick() {
    vector<int> firstClickIndex = GetClickedCell();

    CheckForMeteors(); // Updates each cell's adjacentMeteor parameter to be accurate after all of the cells are rendered

    if(firstClickIndex.size() == 2) {
        cout << "hello first click " << firstClickIndex.at(0) << ", " << firstClickIndex.at(1) << endl;
        TurnSurroundingCells(firstClickIndex.at(0), firstClickIndex.at(1));
    }
}

void Grid::FlipAllCells() {
    if(IsKeyPressed(KEY_SPACE)) {
        for(int i = 0; i < (int)grid.size(); i++) {
            for(int j = 0; j < (int)grid.at(0).size(); j++) {
                grid.at(i).at(j).isTurned = true;
            }
        }
    }
}

void Grid::GameWin(bool & isPlayerWin) {
    int turnedCells = 0;
    int totalCells = (int)grid.size() * (int)grid.at(0).size();
    int totalMeteors = 0;

    for(int i = 0; i < (int)grid.size(); i++) {
        for(int j = 0; j < (int)grid.at(0).size(); j++) {
            if(grid.at(i).at(j).isTurned) {
                turnedCells++;
            }
            if(grid.at(i).at(j).isMeteor) {
                totalMeteors++;
            }
        }
    }

    if(turnedCells == totalCells - totalMeteors) {
        isPlayerWin = true;
        std::cout << "you win" << std::endl;
    }
}

// Getters
//---------------------------------------------------------------------------------------------------------------------------------------------------------
float Grid::GetX() {
    return x;
}
float Grid::GetY() {
    return y;
}
float Grid::GetCellDimensions() {
    return cellDimensions;
}
std::vector<std::vector<Cell>> Grid::GetGrid() {
    return grid;
}

// Setters
//---------------------------------------------------------------------------------------------------------------------------------------------------------
void Grid::SetX(float xPos) {
    x = xPos;
}
void Grid::SetY(float yPos) {
    y = yPos;
}
void Grid::SetCellDimensions(float cellDim) {
    cellDimensions = cellDim;
}
void Grid::SetGrid(std::vector<std::vector<Cell>> grd) {
    grid = grd;
}