//
// Created by George Zorn on 3/20/21.
//

#ifndef MAZERUNNER_EVENT_H
#define MAZERUNNER_EVENT_H

#include <functional>
class IEvent;

template<typename ...args>
class Event{
private:
    typedef std::function<bool(IEvent &self, args...)> Function;
    Function fxn;
public:
    bool call(IEvent &self, args... ax){
        if(fxn){
            return fxn(self, ax...);
        }
        return false;
    }
    void setFunction(Function &&func){
        fxn = std::forward<Function>(func);
    }
};

#endif //MAZERUNNER_EVENT_H
