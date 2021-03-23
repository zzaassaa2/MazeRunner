//
// Created by George Zorn on 3/18/21.
//

#ifndef MAZERUNNER_SCENE_H
#define MAZERUNNER_SCENE_H

#include <vector>
#include <queue>
class Shader;
class Model;
#include "glm/glm.hpp"
class Application;
class Gui;
#include "engine/event/IEvent.h"
class Camera;

class Scene: public IEvent {
public:
    std::vector<std::pair<  std::shared_ptr<Shader>, std::vector<std::shared_ptr<Model>>  >> toRender;
    std::vector<std::shared_ptr<Gui>> guis;
    std::vector<std::shared_ptr<void>> saved_pointers;
    std::queue<Gui*> guis_to_remove;

    Application &application;
    std::shared_ptr<Camera> camera;

    Scene(Application &parent_app);

    virtual void render(Application &app);
    void registerModel(std::shared_ptr<Model> modelIn);
    void registerGui(std::shared_ptr<Gui> guiIn);
    void removeGui(Gui *toRemove);
    void savePointer(std::shared_ptr<void> toSave);

    std::bitset<3> processEvents(Application &app) override;
};


#endif //MAZERUNNER_SCENE_H
