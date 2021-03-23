//
// Created by George Zorn on 3/18/21.
//

#include "engine/scene/Scene.h"
#include "engine/Log.h"
#include "engine/scene/Gui.h"
#include "engine/model/Shader.h"
#include "engine/Application.h"
#include "engine/model/Model.h"
#include "engine/scene/Camera.h"
#include "engine/event/ScrollEvent.h"
#include "engine/event/MouseEvent.h"

Scene::Scene(Application &parent_app):application(parent_app) {

}

void Scene::render(Application &app){
    glm::mat4 transform;

    if(camera){
        glm::mat4 projection = glm::perspective(glm::radians(camera->zoom),
                                                app.getScreenWidth()/app.getScreenHeight(),
                                                camera->nearClip, camera->farClip);
        glm::mat4 view = camera->getViewMatrix();
        glm::mat4 output = glm::translate(glm::mat4(1.0f), glm::vec3(0.0f, 0.0f, 0.0f));
        transform = projection * view * output;
    }

    for(const auto& pair : toRender){
        pair.first->bind();
        if(camera){
            pair.first->setUniformMat4fv("transform", glm::value_ptr(transform));
        }
        for(auto &model : pair.second){
            model->render();
        }
    }

    while(!guis_to_remove.empty()){
        auto itr = guis.begin();
        while(itr != guis.end()){
            if(itr->get() == guis_to_remove.front()){
                guis.erase(itr);
                break;
            }
            ++itr;
        }
        guis_to_remove.pop();
    }

    if(!guis.empty()){
        ImGui_ImplOpenGL3_NewFrame();
        ImGui_ImplGlfw_NewFrame();
        ImGui::NewFrame();
        for(auto &gui : guis){
            gui->render(app);
        }
        ImGui::Render();
        ImGui_ImplOpenGL3_RenderDrawData(ImGui::GetDrawData());
    }
}

std::bitset<3> Scene::processEvents(Application &app) {
    std::bitset<3> swi;
    for(const auto &gui : guis){
        std::bitset<3> out = gui->processEvents(app);
        swi |= out;
    }
    if(!swi.test(IEvent::KEY_TEST_POS)){
        if(processKeyEvents(*this, app)){
            swi.flip(IEvent::KEY_TEST_POS);
        }
    }
    if(!swi.test(IEvent::CURSOR_TEST_POS)){
        camera->processMouseMovement(MouseEvent::xOffset, MouseEvent::yOffset);
        if(processMouseMoveEvents(*this, app)){
            swi.flip(IEvent::CURSOR_TEST_POS);
        }
    }
    if(!swi.test(IEvent::SCROLL_TEST_POS)){
        camera->processMouseScroll((float) ScrollEvent::yOffset);
        if(processScrollEvents(*this, app)){
            swi.flip(IEvent::SCROLL_TEST_POS);
        }
    }

    return swi;
}

void Scene::registerModel(std::shared_ptr<Model> modelIn) {
    if(auto sdr = modelIn->shader.lock()){
        for(auto &pair : toRender){
            if(pair.first.get() == sdr.get()){
                pair.second.push_back(std::move(modelIn));
                return;
            }
        }
        std::vector<std::shared_ptr<Model>> n;
        n.push_back(std::move(modelIn));
        toRender.emplace_back(std::move(sdr), n);
    }else{
        Log::getCoreLogger()->error("dd");
    }
}
void Scene::registerGui(std::shared_ptr<Gui> guiIn) {
    guis.push_back(std::move(guiIn));
}
void Scene::removeGui(Gui *toRemove){
    guis_to_remove.push(toRemove);
}
void Scene::savePointer(std::shared_ptr<void> toSave){
    saved_pointers.push_back(std::move(toSave));
}
