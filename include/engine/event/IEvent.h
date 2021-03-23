//
// Created by George Zorn on 3/21/21.
//

#ifndef MAZERUNNER_IEVENT_H
#define MAZERUNNER_IEVENT_H

class Application;
#include "engine/GLImport.h"
#include "Event.h"
#include <vector>
#include <memory>
#include <bitset>

class IEvent {
public:
    static const unsigned int KEY_TEST_POS = 0;
    static const unsigned int SCROLL_TEST_POS = 1;
    static const unsigned int CURSOR_TEST_POS = 2;

    typedef std::weak_ptr<Event<Application&, GLFWwindow*, float>> Std_event;
    std::vector<Std_event> key_events;
    std::vector<Std_event> scroll_events;
    std::vector<Std_event> cursor_move_events;


    void registerKeyEvent(Std_event event);
    void registerScrollEvent(Std_event event);
    void registerMouseMoveEvent(Std_event event);

    virtual std::bitset<3> processEvents(Application &app) = 0;

    bool processKeyEvents(IEvent &self, Application &app);
    bool processScrollEvents(IEvent &self, Application &app);
    bool processMouseMoveEvents(IEvent &self, Application &app);
};


#endif //MAZERUNNER_IEVENT_H
