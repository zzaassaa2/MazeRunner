//
// Created by George Zorn on 3/7/21.
//

#ifndef MAZERUNNER_APPLICATION_H
#define MAZERUNNER_APPLICATION_H

#include "GLImport.h"
#include <string>
class Scene;
class Camera;
#include <vector>
#include "engine/event/IEvent.h"

class Application: public IEvent {
private:
    GLFWwindow* windowId{nullptr};
    int screenWidth{800}, screenHeight{600};
    float lastX, lastY;
    bool firstMouse = true;
    float deltaTime = 0.0f;
    float lastFrame = 0.0f;
    std::string title = "Application";
    glm::vec4 backgroundColor = glm::vec4(0.2f, 0.3f, 0.5f, 1.0f);

    std::shared_ptr<Scene> current_scene{nullptr};
    std::shared_ptr<Scene> queued_scene{nullptr};

    void init();
public:
    Application();
    ~Application();

    void start();
    virtual void initialization() = 0;

    std::bitset<3> processEvents(Application &app) override;

    void setScene(std::shared_ptr<Scene> sceneIn);
    std::weak_ptr<Scene> getScene();
    GLFWwindow* getWindowId();
    float getDeltaTime() const;
    float getScreenWidth() const;
    float getScreenHeight() const;
    std::string getTitle();
    glm::vec4 getBackgroundColor();

    static void cursorMoveEvent(GLFWwindow *window, double xPos, double yPos);
    static void scrollEvent(GLFWwindow* window, double xOffset, double yOffset);
    static void keyEvent(GLFWwindow* window, int key, int scancode, int action, int mods);
};


#endif //MAZERUNNER_APPLICATION_H
