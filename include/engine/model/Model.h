//
// Created by George Zorn on 3/7/21.
//

#ifndef MAZERUNNER_MODEL_H
#define MAZERUNNER_MODEL_H

#include <vector>
#include "engine/GLImport.h"
class Shader;

enum CallType{
    DrawArrays
};

class Model {
public:
    unsigned int vao{0};
    std::weak_ptr<Shader> shader;
    int attributes{0};
    std::vector<unsigned int> vbos;
    int numVertex{0};
    glm::vec3 position{0.0f, 0.0f, 0.0f};
    CallType calltype{DrawArrays};

    Model(std::weak_ptr<Shader> shaderIn, int numVerticies, CallType calltype);
    ~Model();

    void render();
    void bindData(float data[], unsigned int dataSize, int perVertex);
    void bind();
};


#endif //MAZERUNNER_MODEL_H
