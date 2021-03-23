//
// Created by George Zorn on 3/17/21.
//

#ifndef MAZERUNNER_GUI_H
#define MAZERUNNER_GUI_H

class Application;
#include "engine/event/IEvent.h"

class Gui: public IEvent {
public:
    bool overrideControl{true};
    virtual void render(Application &app) = 0;
    std::bitset<3> processEvents(Application &app) override;
};


#endif //MAZERUNNER_GUI_H
