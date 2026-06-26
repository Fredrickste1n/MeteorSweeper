#include <iostream>
#include <raylib.h>

#ifndef CELL_H
#define CELL_H

struct Cell {
    float x, y, width, height;
    int adjacentMeteors;
    bool isMeteor, isTurned, isFlagged;
};

#endif