#include <iostream>
#include <vector>
#include <raylib.h>
#include "cell.h"
#include "resources.h"

#ifndef GRID_H
#define GRID_H

class Grid {
private:
    float x, y, cellDimensions;
    Texture2D cellBack, cellFront, cellMeteor, cellFlagged;
public:
    std::vector<std::vector<Cell>> grid;
    Grid(float x, float y, float cellDimensions);

    // Grid's methods
    void Draw();
    void Update(bool &, bool &);
    void FillGrid();
    void IsCellClicked(bool &);
    void CheckForMeteors();
    std::vector<int> GetClickedCell();
    void TurnSurroundingCells(int xIndex, int yIndex);
    void FirstClick();
    void FlipAllCells();
    void GameWin(bool &);

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