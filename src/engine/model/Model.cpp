//
// Created by George Zorn on 3/7/21.
//

#include "engine/model/Model.h"
#include "engine/Log.h"
#include "engine/model/Shader.h"

Model::Model(std::weak_ptr<Shader> shaderIn, int numVerticies, CallType calltype): shader(std::move(shaderIn)), numVertex(numVerticies), calltype(calltype) {
    glGenVertexArrays(1, &vao);
}

Model::~Model() {
    if(!vbos.empty()){
        glDeleteBuffers((unsigned int) vbos.size(), &vbos[0]);
    }
    glDeleteVertexArrays(1, &vao);
    Log::getCoreLogger()->info("Model Deleted");
}

void Model::render() {
    if(auto s = shader.lock()){
        s->setUniform3f("modelPosition", position);
    }
    bind();

    switch(calltype){
        case DrawArrays:
            glDrawArrays(GL_TRIANGLES, 0, numVertex);
            break;
    }
}

void Model::bindData(float data[], unsigned int dataSize, int perVertex){
    bind();
    unsigned int vbo;
    glGenBuffers(1, &vbo);

    glBindBuffer(GL_ARRAY_BUFFER, vbo);
    glBufferData(GL_ARRAY_BUFFER, dataSize, data, GL_STATIC_DRAW);
    glVertexAttribPointer(attributes, perVertex, GL_FLOAT, GL_FALSE, 0, nullptr);
    glEnableVertexAttribArray(attributes);

    ++attributes;
    vbos.push_back(vbo);
}

void Model::bind(){
    glBindVertexArray(vao);
}
