//
// Created by George Zorn on 3/16/21.
//

#include "PlayerCamera.h"
#include "engine/Utility.h"
#include "MazeRunner.h"
#include "MainScene.h"
#include "BuildConfig.h"
#include "Cell.h"

PlayerCamera::PlayerCamera(glm::vec3 positionIn)
: Camera(positionIn){
    nearClip = 0.0001f;
    yaw = 45.0f;
    updateCameraVector();
}

void PlayerCamera::processKeyboard(Application &app, GLFWwindow *window, float deltaTime) {
    if(!MazeRunner::maze){
        return;
    }

    float velocity = movementSpeed * deltaTime;
    auto temp_position = position;
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
        temp_position += glm::normalize(glm::vec3(front.x, 0, front.z)) * velocity;
    }
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
        temp_position -= glm::normalize(glm::vec3(front.x, 0, front.z)) * velocity;
    }
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
        temp_position -= glm::normalize(glm::cross(front, up)) * velocity;
    }
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
        temp_position += glm::normalize(glm::cross(front, up)) * velocity;
    }
#ifdef Debug
    if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS){
        temp_position += glm::vec3(0, velocity, 0);
    }
    if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS){
        temp_position -= glm::vec3(0, velocity, 0);
    }
#endif

    const float factor = 0.01f;
    if(temp_position.x <= factor) temp_position.x = factor;
    else if(temp_position.x >= (float)MazeRunner::maze->rows) temp_position.x = (float)MazeRunner::maze->rows - factor;

    if(temp_position.y < 0.5) temp_position.y = 0.5f;

    if(temp_position.z <= factor) temp_position.z = factor;
    else if(temp_position.z >= (float)MazeRunner::maze->cols) temp_position.z = (float)MazeRunner::maze->cols - factor;

    int current_x = (int)position.x, current_z = (int) position.z;
    int new_x = (int)temp_position.x, new_z = (int) temp_position.z;
    if(current_x == new_x && current_z == new_z){
        position = temp_position;
        return;
    }

    auto &currentCell = MazeRunner::maze->grid[(int)position.x + (int)position.z * MazeRunner::maze->cols];
    glm::vec3 p3(position.x, position.z, 0);
    glm::vec3 p4(temp_position.x, temp_position.z, 0);

    if(currentCell->walls[0]){
        glm::vec3 p1(currentCell->i, currentCell->j, 0);
        glm::vec3 p2(currentCell->i+1, currentCell->j, 0);

        if(mz::isIntersecting(p1, p2, p3, p4)){
            return;
        }
    }
    if(currentCell->walls[1]){
        glm::vec3 p1(currentCell->i+1, currentCell->j, 0);
        glm::vec3 p2(currentCell->i+1, currentCell->j+1, 0);

        if(mz::isIntersecting(p1, p2, p3, p4)){
            return;
        }
    }
    if(currentCell->walls[2]){
        glm::vec3 p1(currentCell->i+1, currentCell->j+1, 0);
        glm::vec3 p2(currentCell->i, currentCell->j+1, 0);

        if(mz::isIntersecting(p1, p2, p3, p4)){
            return;
        }
    }
    if(currentCell->walls[3]){
        glm::vec3 p1(currentCell->i, currentCell->j+1, 0);
        glm::vec3 p2(currentCell->i, currentCell->j, 0);

        if(mz::isIntersecting(p1, p2, p3, p4)){
            return;
        }
    }

    position = temp_position;
    float center_hit_x = (float)MazeRunner::maze->cols - 0.5f;
    float center_hit_y = 0.5f;
    float center_hit_z = (float)MazeRunner::maze->rows - 0.5f;
    glm::vec3 center_hit(center_hit_x, center_hit_y, center_hit_z);
    float d = glm::distance(position, center_hit);
    if(d <= 0.5){
        if(auto scene = app.getScene().lock()){
            if(auto *main_scene = dynamic_cast<MainScene*>(scene.get())){
                main_scene->victory(app);
            }
        }
    }
}
