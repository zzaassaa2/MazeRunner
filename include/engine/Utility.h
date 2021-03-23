//
// Created by George Zorn on 3/16/21.
//

#ifndef MAZERUNNER_UTILITY_H
#define MAZERUNNER_UTILITY_H

#include "glm/glm.hpp"

namespace mz{
    bool isIntersecting(glm::vec3 p1, glm::vec3 p2, glm::vec3 q1, glm::vec3 q2);
    float map(float input, float input_start, float input_end, float output_start, float output_end);
}


#endif //MAZERUNNER_UTILITY_H
