//
// Created by George Zorn on 3/17/21.
//

#ifndef MAZERUNNER_MAZERUNNER_H
#define MAZERUNNER_MAZERUNNER_H

#include "engine/Application.h"
#include "MazeGenerator.h"
#include <chrono>

class MazeRunner: public Application {
public:
    static MazeGenerator *maze;
    static std::chrono::time_point<std::chrono::high_resolution_clock> start_time;
    ~MazeRunner();

    void initialization() override;
    static void generateMaze(int xy);

};


#endif //MAZERUNNER_MAZERUNNER_H
