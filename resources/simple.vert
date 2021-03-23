#version 410 core
layout (location = 0) in vec3 aPos;

uniform mat4 transform;
uniform vec3 modelPosition;

void main(){
    gl_Position = transform * vec4(aPos+modelPosition, 1.0);
}