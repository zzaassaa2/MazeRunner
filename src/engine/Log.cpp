//
// Created by George Zorn on 3/7/21.
//

#include "engine/Log.h"
#include "spdlog/sinks/stdout_color_sinks.h"

std::shared_ptr<spdlog::logger> Log::coreLogger;
bool firstCall = true;

void Log::init() {
    if(firstCall){
        spdlog::set_pattern("%^[%T] %n: %v%$");
        coreLogger = spdlog::stdout_color_mt("GLEngine");
        coreLogger->set_level(spdlog::level::trace);
        firstCall = false;
    }
}
