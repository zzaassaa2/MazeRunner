//
// Created by George Zorn on 3/7/21.
//

#include "engine/Application.h"
#include <algorithm>
#include "engine/scene/Scene.h"
#include "engine/Log.h"
#include "engine/event/KeyEvent.h"
#include "engine/event/ScrollEvent.h"
#include "engine/event/MouseEvent.h"

Application::Application()
:screenWidth(800), screenHeight(600), lastX((float)800/2), lastY((float)400/2){
    Log::init();
    init();
}

Application::~Application() {
    Log::getCoreLogger()->info("Application Destroyed");
}

static void glfw_error_callback(int error, const char* description){
    fprintf(stderr, "Glfw Error %d: %s\n", error, description);
}

void Application::init(){
    glfwSetErrorCallback(glfw_error_callback);
    if(!glfwInit()){
        Log::getCoreLogger()->error("Couldn't Initialize glfw");
        return;
    }
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 4);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR, 1);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    glfwWindowHint(GLFW_OPENGL_FORWARD_COMPAT, true);

    windowId = glfwCreateWindow(screenWidth, screenHeight, title.c_str(), nullptr, nullptr);
    if(!windowId){
        Log::getCoreLogger()->error("Failed to create GLFW window");
        glfwTerminate();
        return;
    }
    glfwMakeContextCurrent(windowId);

    glewExperimental = true;
    if(glewInit() != GLEW_OK){
        Log::getCoreLogger()->error("Error with loading glew");
        glfwTerminate();
        return;
    }

    glfwSetWindowUserPointer(windowId, this);
    glfwSetCursorPosCallback(windowId, cursorMoveEvent);
    glfwSetScrollCallback(windowId, scrollEvent);
    glfwSetKeyCallback(windowId, keyEvent);

    glEnable(GL_DEPTH_TEST);

    // Setup Dear ImGui context
    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO(); (void)io;

    // Setup Dear ImGui style
    ImGui::StyleColorsDark();

    // Setup Platform/Renderer backends
    ImGui_ImplGlfw_InitForOpenGL(windowId, true);
    ImGui_ImplOpenGL3_Init("#version 410 core");
}

void Application::start() {
    initialization();

    if(!queued_scene){
        current_scene = std::make_shared<Scene>(*this);
    }

    glClearColor(backgroundColor.r, backgroundColor.g, backgroundColor.b, backgroundColor.a);
    while(!glfwWindowShouldClose(windowId)){
        if(queued_scene){
            current_scene = std::move(queued_scene);
            queued_scene = nullptr;
        }

        glfwPollEvents();

        auto currentFrame = (float)glfwGetTime();
        deltaTime = currentFrame - lastFrame;
        lastFrame = currentFrame;

        processEvents(*this);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        int display_w, display_h;
        glfwGetFramebufferSize(windowId, &display_w, &display_h);
        glViewport(0, 0, display_w, display_h);


        current_scene->render(*this);


        glfwSwapBuffers(windowId);
    }
    ImGui_ImplOpenGL3_Shutdown();
    ImGui_ImplGlfw_Shutdown();
    ImGui::DestroyContext();

    glfwDestroyWindow(windowId);
    glfwTerminate();
}

std::bitset<3> Application::processEvents(Application &app){
    std::bitset<3> out = current_scene->processEvents(app);

    if(!out.test(IEvent::KEY_TEST_POS)){
        processKeyEvents(*this, app);
    }
    if(!out.test(IEvent::SCROLL_TEST_POS)){
        processScrollEvents(*this, app);
    }
    if(!out.test(IEvent::CURSOR_TEST_POS)){
        processMouseMoveEvents(*this, app);
    }
    ScrollEvent::xOffset = 0;
    ScrollEvent::yOffset = 0;
    MouseEvent::xOffset = 0;
    MouseEvent::yOffset = 0;

    return false;
}

void Application::cursorMoveEvent(GLFWwindow *window, double xPos, double yPos) {
    auto *app = static_cast<Application*>(glfwGetWindowUserPointer(window));

    if(app->firstMouse){
        app->lastX = (float) xPos;
        app->lastY = (float) yPos;
        app->firstMouse = false;
    }

    MouseEvent::xOffset = ((float) xPos) - app->lastX;
    MouseEvent::yOffset = app->lastY - ((float) yPos);
    app->lastX = (float) xPos;
    app->lastY = (float) yPos;
}

void Application::scrollEvent(GLFWwindow *window, double xOffset, double yOffset) {
//    auto *app = static_cast<Application*>(glfwGetWindowUserPointer(window));
    ScrollEvent::xOffset = xOffset;
    ScrollEvent::yOffset = yOffset;
}

void Application::keyEvent(GLFWwindow *window, int key, int scancode, int action, int mods) {
    if(action == GLFW_PRESS){
        KeyEvent::pressed[key] = true;
    }else if(action == GLFW_RELEASE){
        KeyEvent::pressed[key] = false;
    }

}

void Application::setScene(std::shared_ptr<Scene> sceneIn){
    queued_scene = std::move(sceneIn);
}
std::weak_ptr<Scene> Application::getScene(){
    return current_scene;
}

GLFWwindow* Application::getWindowId(){
    return windowId;
}
float Application::getDeltaTime() const {
    return deltaTime;
}

float Application::getScreenWidth() const {
    return static_cast<float>(screenWidth);
}
float Application::getScreenHeight() const {
    return static_cast<float>(screenHeight);
}
std::string Application::getTitle(){
    return title;
}
glm::vec4 Application::getBackgroundColor(){
    return backgroundColor;
}
