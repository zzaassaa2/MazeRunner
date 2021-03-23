//
// Created by George Zorn on 3/8/21.
//

#include "engine/model/Shader.h"
#include "engine/Log.h"
#include <algorithm>
#include <sstream>
#include <fstream>

Shader::Shader(const std::string &vertexShaderPath, const std::string &fragmentShaderPath) {
    std::string vs = parseShader(vertexShaderPath);
    std::string fs = parseShader(fragmentShaderPath);
    unsigned int vertexShader = generateShader(GL_VERTEX_SHADER, vs);
    unsigned int fragmentShader = generateShader(GL_FRAGMENT_SHADER, fs);
    int success;
    char infoLog[512];

    shaderId = glCreateProgram();
    glAttachShader(shaderId, vertexShader);
    glAttachShader(shaderId, fragmentShader);
    glLinkProgram(shaderId);
    glGetProgramiv(shaderId, GL_LINK_STATUS, &success);
    if(!success){
        glGetProgramInfoLog(shaderId, 512, nullptr, infoLog);
        Log::getCoreLogger()->error("ERROR::SHADER:PROGRAM:LINKING_FAILED\n", infoLog);
    }
    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

Shader::~Shader() {
    Log::getCoreLogger()->info("Shader deleted");
    glDeleteProgram(shaderId);
}

void Shader::bind() const {
    glUseProgram(shaderId);
}

void Shader::unBind() {
    glUseProgram(0);
}

int Shader::getUnifromLocation(const std::string &name) {
    for(const auto& pair : uniformLocationCache){
        if(pair.first == name){
            return pair.second;
        }
    }

    int location = glGetUniformLocation(shaderId, name.c_str());
    if(location == -1){
        Log::getCoreLogger()->error("Warning: uniform ", name, " doesnt' exist");
        return -1;
    }

    uniformLocationCache.emplace_back(name, location);
    return location;
}

unsigned int Shader::generateShader(unsigned int type, std::string &input){
    unsigned int shader = glCreateShader(type);
    const char* src = input.c_str();
    glShaderSource(shader, 1, &src, nullptr);
    glCompileShader(shader);
    int success;
    char infoLog[512];
    glGetShaderiv(shader, GL_COMPILE_STATUS, &success);
    if(!success){
        glGetShaderInfoLog(shader, 512, nullptr, infoLog);
        Log::getCoreLogger()->error("ERROR::SHADER::COMPILATION_FAILED", infoLog);
    }

    return shader;
}

std::string Shader::parseShader(const std::string& shaderFile) {
    std::string line;
    std::ifstream myFile(shaderFile);
    std::stringstream ss;

    if(myFile.is_open()){
        while(getline(myFile, line)){
            ss << line << '\n';
        }
        myFile.close();
    }else{
        Log::getCoreLogger()->error("Unable to open file: " + shaderFile);
    }

    return ss.str();
}

void Shader::setUniform1i(const std::string &name, int v0){
    glUniform1i(getUnifromLocation(name), v0);
}

void Shader::setUniform1f(const std::string &name, float v0){
    glUniform1f(getUnifromLocation(name), v0);
}

void Shader::setUniform3f(const std::string &name, glm::vec3& v0){
    glUniform3f(getUnifromLocation(name), v0.x, v0.y, v0.z);
}

void Shader::setUniform4f(const std::string &name, glm::vec4 &v0){
    glUniform4f(getUnifromLocation(name), v0.x, v0.y, v0.z, v0.w);
}

void Shader::setUniformMat4fv(const std::string &name, float* v0){
    glUniformMatrix4fv(getUnifromLocation(name), 1, GL_FALSE, v0);
}
