//
// Created by George Zorn on 3/8/21.
//

#ifndef MAZERUNNER_SHADER_H
#define MAZERUNNER_SHADER_H

#include <vector>
#include "engine/GLImport.h"

class Shader {
private:
    unsigned int shaderId;
    std::vector<std::pair<std::string, int>> uniformLocationCache;

    int getUnifromLocation(const std::string& name);
    static unsigned int generateShader(unsigned int type, std::string& input);
    static std::string parseShader(const std::string& shaderFile);
public:
    Shader(const std::string& vertexShaderPath, const std::string& fragmentShaderPath);
    ~Shader();

    void bind() const;
    static void unBind();

    void setUniform1i(const std::string& name, int v0);
    void setUniform1f(const std::string& name, float v0);
    void setUniform3f(const std::string& name, glm::vec3& v0);
    void setUniform4f(const std::string& name, glm::vec4& v0);
    void setUniformMat4fv(const std::string& name, float* v0);
};


#endif //MAZERUNNER_SHADER_H
