//
// Created by George Zorn on 3/20/21.
//

#include "EscGui.h"
#include "imgui/imgui.h"
#include "engine/Application.h"
#include "engine/scene/Scene.h"
#include "OpeningGui.h"
#include <chrono>
#include "MazeRunner.h"

EscGui::EscGui(GuiType typeIn):type(typeIn) {
    typeElapsed = std::chrono::duration_cast<std::chrono::duration<double, std::ratio<1>>>(std::chrono::high_resolution_clock::now() - MazeRunner::start_time).count();
}

void EscGui::render(Application &app) {
    float x = 500, y = 400;
    ImGui::SetNextWindowSize({x, y});
    ImGui::SetNextWindowPos({app.getScreenWidth()/2 - x/2, app.getScreenHeight()/2 - y/2});

    switch(type){
        case Pause:
            ImGui::Begin("Paused");

            if(ImGui::Button("Close")){
                if(const auto scene = app.getScene().lock()){
                    scene->removeGui(this);
                    glfwSetInputMode(app.getWindowId(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);
                }
            }
            break;
        case Victory:
            ImGui::Begin("Victory");

            ImGui::Text("Time Elapsed is %.2f", typeElapsed);
    }

    if(ImGui::Button("Return to Main Menu")){
        auto scene = std::make_shared<Scene>(app);

        auto test_gui = std::make_shared<OpeningGui>();
        scene->registerGui(test_gui);

        app.setScene(scene);
    }
    if(ImGui::Button("Quit Application")){
        glfwSetWindowShouldClose(app.getWindowId(), true);
    }

    ImGui::End();
}