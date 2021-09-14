#version 330 core

layout (location = 0) in vec3 pos;
layout (location = 1) in vec3 col;

out vec3 Col;

uniform mat4 camMatrix;
uniform mat4 modelMatrix;

void main() {

//    gl_Position = camMatrix * modelMatrix * vec4(pos,1.0);
    gl_Position = camMatrix * modelMatrix*vec4(pos,1.0f);
    Col = col;
}
