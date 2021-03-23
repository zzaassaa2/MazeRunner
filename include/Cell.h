//
// Created by George Zorn on 3/4/21.
//

#ifndef ASCIMAZERUNNER_CELL_H
#define ASCIMAZERUNNER_CELL_H

#include <vector>

class Cell {
public:
    int i = 0, j = 0;
    bool walls[4] = {true, true, true, true};
    bool visited = false;

    Cell(int i, int j);

    Cell* checkNeighbors(std::vector<Cell*>& grid, int cols, int rows) const;
    static int index(int i, int y, int cols, int rows);
};


#endif //ASCIMAZERUNNER_CELL_H
