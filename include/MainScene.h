//
// Created by George Zorn on 3/21/21.
//

#ifndef MAZERUNNER_MAINSCENE_H
#define MAZERUNNER_MAINSCENE_H

#include "engine/scene/Scene.h"

class MainScene: public Scene {
public:
    explicit MainScene(Application &parentApp);
    void victory(Application &app);
};


#endif //MAZERUNNER_MAINSCENE_H
