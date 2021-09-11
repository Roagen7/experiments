#version 330 core
//POSITION <0,HEIGHT> <0,WIDTH>


layout (location = 0) in vec2 pos;
layout (location = 1) in vec3 col;

out vec2 Position;
out vec2 Complex;

out vec3 Color;

uniform vec2 z0;
uniform int HEIGHT;
uniform int WIDTH;
uniform float unitRe;
uniform float unitIm;


//uniform mat4 cMatrix;

void main() {
    Position = vec2(pos.x / (WIDTH/2) - 1, -(pos.y / (HEIGHT/2) - 1));
    Complex = z0 + vec2(pos.x * float(unitRe) / float(WIDTH), -pos.y * float(unitIm) / float(HEIGHT));

    Color = col;
    gl_Position = vec4(Position,0.0, 1.0);
}
