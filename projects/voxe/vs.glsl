#version 330 core

layout (location = 0) in vec3 pos;

uniform mat4 camMatrix;

void main() {
    gl_Position = camMatrix * vec4(pos,1.0);


}