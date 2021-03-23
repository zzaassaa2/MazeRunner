//
// Created by George Zorn on 3/17/21.
//

#include "engine/scene/Gui.h"

std::bitset<3> Gui::processEvents(Application &app) {
    std::bitset<3> swi;
    if(!swi.test(IEvent::KEY_TEST_POS)){
        if(processKeyEvents(*this, app)){
            swi.flip(IEvent::KEY_TEST_POS);
        }
    }
    if(!swi.test(IEvent::CURSOR_TEST_POS)){
        if(processMouseMoveEvents(*this, app)){
            swi.flip(IEvent::CURSOR_TEST_POS);
        }
    }
    if(!swi.test(IEvent::SCROLL_TEST_POS)){
        if(processScrollEvents(*this, app)){
            swi.flip(IEvent::SCROLL_TEST_POS);
        }
    }

    if(overrideControl){
        swi.set();
    }

    return swi;
}