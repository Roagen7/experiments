#version 330 core

layout (location = 0) in vec2 pos;
layout (location = 1) in vec3 col;

out vec3 Color;
out vec2 pixPos;

uniform float width;
uniform float height;

//pos 0:1920, 0:1080

void main() {
    gl_Position = vec4(pos.x/(width/2)-1,1-pos.y/(height/2),1.0,1.0);
    Color = col;
    pixPos = pos;
}
