//
// Created by George Zorn on 3/21/21.
//

#include "engine/event/IEvent.h"
#include "engine/Application.h"

void IEvent::registerKeyEvent(std::weak_ptr<Event<Application&, GLFWwindow*, float>> event){
    key_events.push_back(std::move(event));
}
void IEvent::registerScrollEvent(Std_event event){
    scroll_events.push_back(std::move(event));
}
void IEvent::registerMouseMoveEvent(Std_event event){
    cursor_move_events.push_back(std::move(event));
}


bool IEvent::processKeyEvents(IEvent &self, Application &app) {
    auto itr = key_events.begin();
    while(itr != key_events.end()){
        if(auto ptr = itr->lock()){
            if(ptr->call(self, app, app.getWindowId(), app.getDeltaTime())){
                return true;
            }
            ++itr;
        }else{
            key_events.erase(itr);
        }
    }
    return false;
}
bool IEvent::processScrollEvents(IEvent &self, Application &app){
    auto itr = scroll_events.begin();
    while(itr != scroll_events.end()){
        if(auto ptr = itr->lock()){
            if(ptr->call(self, app, app.getWindowId(), app.getDeltaTime())){
                return true;
            }
            ++itr;
        }else{
            scroll_events.erase(itr);
        }
    }
    return false;
}
bool IEvent::processMouseMoveEvents(IEvent &self, Application &app){
    auto itr = cursor_move_events.begin();
    while(itr != cursor_move_events.end()){
        if(auto ptr = itr->lock()){
            if(ptr->call(self, app, app.getWindowId(), app.getDeltaTime())){
                return true;
            }
            ++itr;
        }else{
            cursor_move_events.erase(itr);
        }
    }
    return false;
}