//
// Created by George Zorn on 3/16/21.
//

#ifndef MAZERUNNER_PLAYERCAMERA_H
#define MAZERUNNER_PLAYERCAMERA_H

#include "engine/scene/Camera.h"
#include "MazeGenerator.h"

class PlayerCamera: public Camera {
public:
    explicit PlayerCamera(glm::vec3 position);
    void processKeyboard(Application &app, GLFWwindow *window, float deltaTime) override;
};


#endif //MAZERUNNER_PLAYERCAMERA_H
