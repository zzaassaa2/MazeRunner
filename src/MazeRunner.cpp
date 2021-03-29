//
// Created by George Zorn on 3/17/21.
//

#include "MazeRunner.h"
#include "engine/scene/Scene.h"
#include "PlayerCamera.h"
#include "OpeningGui.h"
#include <iostream>

int main(){
    auto *app = new MazeRunner();

    app->start();

    delete app;

    return 0;
}

MazeGenerator *MazeRunner::maze{nullptr};
/* Var used to keep track of how long it took to complete the maze, see @MazeRunner::generateMaze */
std::chrono::time_point<std::chrono::high_resolution_clock> MazeRunner::start_time;

MazeRunner::~MazeRunner() {
    delete maze;
}

void MazeRunner::initialization() {
    auto scene = std::make_shared<Scene>(*this);

    auto test_gui = std::make_shared<OpeningGui>();
    scene->registerGui(test_gui);

    setScene(scene);
}

void MazeRunner::generateMaze(int xy) {
    delete maze;
    maze = nullptr;
    maze = new MazeGenerator(xy, xy);
    start_time = std::chrono::high_resolution_clock::now();
}
