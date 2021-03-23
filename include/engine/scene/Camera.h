//
// Created by George Zorn on 3/8/21.
//

#ifndef MAZERUNNER_CAMERA_H
#define MAZERUNNER_CAMERA_H

#include "engine/GLImport.h"
#include <vector>
class Application;

class Camera {
protected:
    void updateCameraVector();
public:
    glm::vec3 position{0.0f, 0.0f, 0.0f};

    glm::vec3 front{0.0f, -1.0f, 0.0f};
    glm::vec3 up{0.0f, 1.0f, 0.0f};
    glm::vec3 right{1.0f, 0.0f, 0.0f};
    glm::vec3 worldUp{0.0f, 1.0f, 0.0f};
    float yaw{-90.0f};
    float pitch{0.0f};
    float movementSpeed{2.5f};
    float mouseSensitivity{0.1f};
    float zoom{45.0f};
    float nearClip = 0.1f;
    float farClip = 100.0f;

    Camera();
    Camera(glm::vec3 position);

    glm::mat4 getViewMatrix();
    virtual void processKeyboard(Application &app, GLFWwindow *window, float deltaTime);
    virtual void processMouseMovement(float xOffset, float yOffset);
    virtual void processMouseScroll(float yOffset);
};


#endif //MAZERUNNER_CAMERA_H
