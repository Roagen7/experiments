#version 330 core
in vec2 Position;
in vec3 Color;

out vec4 FragColor;


vec3 mandel(){


    return vec3(0,0,0);
}



void main() {
    FragColor = vec4(Color, 1.0);
}
