//
// Created by George Zorn on 3/5/21.
//

#include "MazeGenerator.h"
#include "Cell.h"

MazeGenerator::~MazeGenerator() {
    for(auto* cell : grid){
        delete cell;
    }
}

MazeGenerator::MazeGenerator(int width, int height): cols(width), rows(height) {
    grid.reserve(cols * rows);
    for(int j = 0; j < rows; ++j){
        for(int i = 0; i < cols; ++i){
            Cell *cell = new Cell(i, j);
            grid.push_back(cell);
        }
    }
    grid.shrink_to_fit();
    current = grid[0];

    while(true){
        current->visited = true;
        //STEP 1
        Cell *next = current->checkNeighbors(grid, cols, rows);
        if(next != nullptr){
            next->visited = true;

            //STEP 2
            stack.push_back(current);

            //STEP 3
            removeWall(current, next);

            //STEP 4
            current = next;
        }else if(!stack.empty()){
            current = stack.back();
            stack.pop_back();
        }else{
            break;
        }
    }
}

void MazeGenerator::removeWall(Cell *a, Cell *b) {
    int x = a->i - b->i;
    if(x == 1){
        a->walls[3] = false;
        b->walls[1] = false;
    }else if(x == -1){
        a->walls[1] = false;
        b->walls[3] = false;
    }
    int y = a->j - b->j;
    if(y == 1){
        a->walls[0] = false;
        b->walls[2] = false;
    }else if(y == -1){
        a->walls[2] = false;
        b->walls[0] = false;
    }
}
