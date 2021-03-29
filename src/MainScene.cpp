//
// Created by George Zorn on 3/21/21.
//

#include "MainScene.h"
#include "MazeRunner.h"
#include "engine/model/Model.h"
#include "engine/model/Shader.h"
#include "engine/event/Event.h"
#include "engine/event/KeyEvent.h"
#include "EscGui.h"
#include <cmath>
#include "engine/Utility.h"
#include "PlayerCamera.h"
#include "Cell.h"

/*
 * Generates sphere vertices. No index buffer used
 */
std::shared_ptr<Model> genTargetSphere(std::shared_ptr<Shader> &shaderIn, float radius, int total){
    std::vector<ImVec4> vertices;
    vertices.reserve(total * total);
    const float pi = 3.14159;
    float x, y, z, xy;

    for(int i = 0; i <= total; ++i){
        auto lon = mz::map(i, 0, total, -pi, pi);
        xy = radius * cosf(lon);
        z = radius * sinf(lon);

        for(int j = 0; j <= total; ++j){
            auto lat = mz::map(j, 0, total, -pi/2, pi/2);
            x = xy * cosf(lat);
            y = xy * sinf(lat);
            vertices.emplace_back(x, y, z, 0);
        }
    }
    vertices.shrink_to_fit();

    std::vector<float> data;
    data.reserve(vertices.size() * 3 * 3);
    for(int i = 0; i < total; ++i){
        for(int j = 0; j < total; ++j){
            int i1 = (i * total) + j;
            int i2 = (i*total) + j + 1;
            int i3 = ((i+1)*total) + j;
            int i4 = ((i+1)*total) + j + 1;
            auto &v1 = vertices[i1];
            auto &v2 = vertices[i2];
            auto &v3 = vertices[i3];
            auto &v4 = vertices[i4];
            data.push_back(v1.x);
            data.push_back(v1.y);
            data.push_back(v1.z);
            data.push_back(v2.x);
            data.push_back(v2.y);
            data.push_back(v2.z);
            data.push_back(v3.x);
            data.push_back(v3.y);
            data.push_back(v3.z);

            data.push_back(v2.x);
            data.push_back(v2.y);
            data.push_back(v2.z);
            data.push_back(v4.x);
            data.push_back(v4.y);
            data.push_back(v4.z);
            data.push_back(v3.x);
            data.push_back(v3.y);
            data.push_back(v3.z);
            /*
             * i*total+j
             * i,j   i,j+1   i+1,j
             *
             */
        }
    }
    data.shrink_to_fit();

    auto target_model = std::make_shared<Model>(shaderIn, (int)data.size()/3, DrawArrays);
    target_model->bindData(data.data(), data.size() * sizeof(float), 3);
    return target_model;
}

MainScene::MainScene(Application &parentApp): Scene(parentApp){
    // Position 0.5,0.5,0.5 is a postion within the center of a maze grid, since grid goes by increments of integers
    camera = std::make_shared<PlayerCamera>(glm::vec3(0.5f, 0.5f, 0.5f));

    // Shader used for maze shading
    auto shader_test = std::make_shared<Shader>("../resources/simple.vert", "../resources/simple.frag");
    float offset = 1;
    float height = 1;
    std::vector<float> data;
    //x + y * cols
    // Generate maze mesh
    for(int zIn = 0; zIn < MazeRunner::maze->rows; ++zIn){
        for(int xIn = 0; xIn < MazeRunner::maze->cols; ++xIn){
            auto& cell = MazeRunner::maze->grid[zIn * MazeRunner::maze->cols + xIn];
            auto x = (float) xIn;
            auto z = (float) zIn;
            if(cell->walls[0]){//top
                data.push_back(x);       data.push_back(0);     data.push_back(z);
                data.push_back(x+offset);data.push_back(0);     data.push_back(z);
                data.push_back(x+offset);data.push_back(height);data.push_back(z);

                data.push_back(x+offset);data.push_back(height);data.push_back(z);
                data.push_back(x);       data.push_back(height);data.push_back(z);
                data.push_back(x);       data.push_back(0);     data.push_back(z);
            }
            if(cell->walls[1]){//right
                data.push_back(x+offset);data.push_back(0);     data.push_back(z);
                data.push_back(x+offset);data.push_back(0);     data.push_back(z+offset);
                data.push_back(x+offset);data.push_back(height);data.push_back(z+offset);

                data.push_back(x+offset);data.push_back(height);data.push_back(z+offset);
                data.push_back(x+offset);data.push_back(height);data.push_back(z);
                data.push_back(x+offset);data.push_back(0);     data.push_back(z);
            }
            if(cell->walls[2]){//bottom
                data.push_back(x+offset);data.push_back(0);     data.push_back(z+offset);
                data.push_back(x);       data.push_back(0);     data.push_back(z+offset);
                data.push_back(x);       data.push_back(height);data.push_back(z+offset);

                data.push_back(x);       data.push_back(height);data.push_back(z+offset);
                data.push_back(x+offset);data.push_back(height);data.push_back(z+offset);
                data.push_back(x+offset);data.push_back(0);     data.push_back(z+offset);
            }
            if(cell->walls[3]){//left
                data.push_back(x);data.push_back(0);     data.push_back(z+offset);
                data.push_back(x);data.push_back(0);     data.push_back(z);
                data.push_back(x);data.push_back(height);data.push_back(z);

                data.push_back(x);data.push_back(height);data.push_back(z);
                data.push_back(x);data.push_back(height);data.push_back(z+offset);
                data.push_back(x);data.push_back(0);     data.push_back(z+offset);
            }
        }
    }

    auto maze_model = std::make_shared<Model>(shader_test, (int)data.size()/3, DrawArrays);
    maze_model->bindData(data.data(), data.size() * sizeof(float), 3);
    registerModel(maze_model);

    auto red_shader = std::make_shared<Shader>("../resources/target.vert", "../resources/target.frag");
    auto target_model = genTargetSphere(red_shader, 0.5, 30);
    target_model->position = glm::vec3((float)MazeRunner::maze->rows-0.5f, 0.5, (float)MazeRunner::maze->cols-0.5f);
    registerModel(target_model);

    glfwSetInputMode(application.getWindowId(), GLFW_CURSOR, GLFW_CURSOR_DISABLED);

    auto event = std::make_shared<Event<Application&, GLFWwindow*, float>>();
    event->setFunction([](IEvent &self, Application &app, GLFWwindow *window, float deltaTime){
        if(const auto sce = app.getScene().lock()){
            if(KeyEvent::pressed[GLFW_KEY_ESCAPE]){
                auto new_gui = std::make_shared<EscGui>(Pause);
                sce->registerGui(new_gui);
                glfwSetInputMode(app.getWindowId(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
                return true;
            }
            sce->camera->processKeyboard(app, window, deltaTime);
        }

        return false;
    });
    savePointer(event);
    registerKeyEvent(event);
}

void MainScene::victory(Application &app) {
    auto victory_gui = std::make_shared<EscGui>(Victory);
    registerGui(victory_gui);
    glfwSetInputMode(app.getWindowId(), GLFW_CURSOR, GLFW_CURSOR_NORMAL);
}