//
// Created by George Zorn on 3/16/21.
//

#include "engine/Utility.h"

bool mz::isIntersecting(glm::vec3 p1, glm::vec3 p2, glm::vec3 q1, glm::vec3 q2){
    return (((q1.x-p1.x)*(p2.y-p1.y) - (q1.y-p1.y)*(p2.x-p1.x))
            * ((q2.x-p1.x)*(p2.y-p1.y) - (q2.y-p1.y)*(p2.x-p1.x)) < 0)
           &&
           (((p1.x-q1.x)*(q2.y-q1.y) - (p1.y-q1.y)*(q2.x-q1.x))
            * ((p2.x-q1.x)*(q2.y-q1.y) - (p2.y-q1.y)*(q2.x-q1.x)) < 0);
}

float mz::map(float input, float input_start, float input_end, float output_start, float output_end) {
    float slope = 1.0f * (output_end - output_start) / (input_end - input_start);
    return output_start + slope * (input - input_start);
}

