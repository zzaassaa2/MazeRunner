//
// Created by George Zorn on 3/8/21.
//

#include "engine/scene/Camera.h"

Camera::Camera(glm::vec3 position)
        :position(position)
{
    updateCameraVector();
}
Camera::Camera(){
    updateCameraVector();
}

glm::mat4 Camera::getViewMatrix(){
    return glm::lookAt(position, position + front, up);
}

void Camera::processKeyboard(Application &app, GLFWwindow *window, float deltaTime) {
    float velocity = movementSpeed * deltaTime;
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
        position += glm::normalize(glm::vec3(front.x, 0, front.z)) * velocity;
    }
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
        position -= glm::normalize(glm::vec3(front.x, 0, front.z)) * velocity;
    }
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
        position -= glm::normalize(glm::cross(front, up)) * velocity;
    }
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
        position += glm::normalize(glm::cross(front, up)) * velocity;
    }
    if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS){
        position += glm::vec3(0, velocity, 0);
    }
    if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS){
        position -= glm::vec3(0, velocity, 0);
    }
}

void Camera::processMouseMovement(float xOffset, float yOffset){
    xOffset *= mouseSensitivity;
    yOffset *= mouseSensitivity;

    yaw   += xOffset;
    pitch += yOffset;

    // make sure that when pitch is out of bounds, screen doesn't get flipped
    if (pitch > 89.0f)
        pitch = 89.0f;
    if (pitch < -89.0f)
        pitch = -89.0f;

    // update Front, Right and Up Vectors using the updated Euler angles
    updateCameraVector();
}

void Camera::processMouseScroll(float yOffset){
    zoom -= (float)yOffset;
    if(zoom < 1.0f){
        zoom  = 1.0f;
    }
    if(zoom > 45.0f){
        zoom = 45.0f;
    }
}

void Camera::updateCameraVector(){
    // calculate the new Front vector
    glm::vec3 frontIn;
    frontIn.x = cos(glm::radians(yaw)) * cos(glm::radians(pitch));
    frontIn.y = sin(glm::radians(pitch));
    frontIn.z = sin(glm::radians(yaw)) * cos(glm::radians(pitch));
    front = glm::normalize(frontIn);
    // also re-calculate the Right and Up vector
    right = glm::normalize(glm::cross(front, worldUp));  // normalize the vectors, because their length gets closer to 0 the more you look up or down which results in slower movement.
    up    = glm::normalize(glm::cross(right, front));
}
