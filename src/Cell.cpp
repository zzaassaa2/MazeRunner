//
// Created by George Zorn on 3/4/21.
//

#include "Cell.h"
#include <vector>
#include <random>
#include <cmath>

Cell::Cell(int i, int j): i(i), j(j) {}

Cell* Cell::checkNeighbors(std::vector<Cell*>& grid, int cols, int rows) const {
    std::vector<Cell*> neighbors;

    int topIndex = index(i, j -1, cols, rows);
    int rightIndex = index(i + 1, j, cols, rows);
    int bottomIndex = index(i, j + 1, cols, rows);
    int leftIndex = index(i - 1, j, cols, rows);

    if(topIndex >= 0){
        Cell *top = grid[topIndex];
        if(!top->visited){
            neighbors.push_back(top);
        }
    }
    if(rightIndex >= 0){
        Cell *right = grid[rightIndex];
        if(!right->visited){
            neighbors.push_back(right);
        }
    }
    if(bottomIndex >= 0){
        Cell *bottom = grid[bottomIndex];
        if(!bottom->visited){
            neighbors.push_back(bottom);
        }
    }
    if(leftIndex >= 0){
        Cell *left = grid[leftIndex];
        if(!left->visited){
            neighbors.push_back(left);
        }
    }

    static std::random_device rd; //obtain random number from hardware
    static std::mt19937 gen(rd()); //seed generator
    if(!neighbors.empty()){//distr(gen)
        std::uniform_int_distribution<> dist(0, neighbors.size()-1);
        int r = std::floor(dist(gen));
        return neighbors[r];
    }else{
        return nullptr;
    }
}

int Cell::index(int x, int y, int cols, int rows) {
    if(x < 0 || y < 0 || x > cols - 1 || y > rows - 1){
        return -1;
    }
    return x + y * cols;
}