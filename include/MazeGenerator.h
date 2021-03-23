//
// Created by George Zorn on 3/5/21.
//

#ifndef ASCIMAZERUNNER_MAZEGENERATOR_H
#define ASCIMAZERUNNER_MAZEGENERATOR_H

#include <vector>
class Cell;
#include <string>

class MazeGenerator {
public:
    int cols, rows;
    std::vector<Cell*> grid;
    Cell* current;
    std::vector<Cell*> stack;


    MazeGenerator(int width, int height);
    ~MazeGenerator();

    static void removeWall(Cell *a, Cell *b);
};


#endif //ASCIMAZERUNNER_MAZEGENERATOR_H
