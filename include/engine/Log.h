//
// Created by George Zorn on 3/7/21.
//

#ifndef MAZERUNNER_LOG_H
#define MAZERUNNER_LOG_H

#include <memory>
#include <spdlog/spdlog.h>

class Log {
private:
    static std::shared_ptr<spdlog::logger> coreLogger;
public:
    static void init();
    inline static std::shared_ptr<spdlog::logger>& getCoreLogger(){return coreLogger;}
};


#endif //MAZERUNNER_LOG_H
