#version 330 core
//POSITION <0,HEIGHT> <0,WIDTH>


layout (location = 0) in vec2 pos;
layout (location = 1) in vec3 col;

out vec2 Position;


out vec3 Color;

uniform int WIDTH;
uniform int HEIGHT;


void main() {
    Position = pos;

    Color = col;
    vec2 posv2 = vec2(pos.x / (WIDTH/2) - 1, -(pos.y / (HEIGHT/2) - 1));

    gl_Position = vec4(posv2.x, posv2.y,0.0, 1.0);
}
