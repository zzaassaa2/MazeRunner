//
// Created by George Zorn on 3/17/21.
//

#include "OpeningGui.h"
#include "imgui/imgui.h"
#include <iostream>
#include "MainScene.h"
#include "engine/Application.h"
#include "MazeRunner.h"

OpeningGui::OpeningGui(){
    overrideControl = true;
}

OpeningGui::~OpeningGui() {
    std::cout << "Test Gui destroyed" << std::endl;
}

void OpeningGui::render(Application &app) {
    float x = 500, y = 400;
    ImGui::SetNextWindowSize({x, y});
    ImGui::SetNextWindowPos({app.getScreenWidth()/2 - x/2, app.getScreenHeight()/2 - y/2});

    ImGui::Begin("Welcome to Maze Runner");

    ImGui::PushItemWidth(120);
    ImGui::InputInt("Maze Size (value x value)", &maze_size, 5);

    if(ImGui::Button("Generate Maze")){
        MazeRunner::generateMaze(maze_size);
        auto scene = std::make_shared<MainScene>(app);

        app.setScene(scene);
    }
//    ImGui::Text("Application average %.3f ms/frame (%.1f FPS)", 1000.0f / ImGui::GetIO().Framerate, ImGui::GetIO().Framerate);
    ImGui::End();
}