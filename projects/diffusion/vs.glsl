#version 330 core
//POSITION <0,HEIGHT> <0,WIDTH>


layout (location = 0) in vec2 pos;
layout (location = 1) in vec3 col;

out vec2 Position;


out vec3 Color;

uniform int WIDTH;
uniform int HEIGHT;


//uniform mat4 cMatrix;

void main() {
    Position = vec2(pos.x / (WIDTH/2) - 1, -(pos.y / (HEIGHT/2) - 1));


    Color = col;
    gl_Position = vec4(Position,0.0, 1.0);
}
