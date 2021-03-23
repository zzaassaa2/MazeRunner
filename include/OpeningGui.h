//
// Created by George Zorn on 3/17/21.
//

#ifndef MAZERUNNER_OPENINGGUI_H
#define MAZERUNNER_OPENINGGUI_H

#include "engine/scene/Gui.h"

class OpeningGui: public Gui {
public:
    int maze_size{16};
    OpeningGui();
    ~OpeningGui();
    void render(Application &app) override;
};


#endif //MAZERUNNER_OPENINGGUI_H
