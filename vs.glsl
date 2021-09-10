#version 330 core

layout (location = 0) in vec2 pos;
layout (location = 1) in vec3 col;

out vec2 Position;
out vec3 Color;



//uniform mat4 cMatrix;

void main() {
    Position = pos;
    Color = col;
    gl_Position = vec4(pos,0.0, 1.0);
}
