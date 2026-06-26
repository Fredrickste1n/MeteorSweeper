#include <iostream>
#include <vector>
#include <raylib.h>
#include "cell.h"

#ifndef GRID_H
#define GRID_H

class Grid {
private:
    float x, y, cellDimensions;
    std::vector<std::vector<Cell>> grid;
    Texture2D cellBack, cellFront, cellMeteor, cellFlagged;
public:
    Grid(float x, float y, float cellDimensions);

    // Grid's methods
    void Draw();
    void Update();
    void FillGrid();
    void IsCellClicked();
    void CheckForMeteors();
    void CreateStartingArea();
    void FirstClick();
    void FlipAllCells();

    // Getters
    float GetX();
    float GetY();
    float GetCellDimensions();
    std::vector<std::vector<Cell>> GetGrid();

    // Setters
    void SetX(float xPos);
    void SetY(float yPos);
    void SetCellDimensions(float cellDim);
    void SetGrid(std::vector<std::vector<Cell>> grd);
};

#endif