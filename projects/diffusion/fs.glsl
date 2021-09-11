#version 330 core
in vec2 Position;
in vec3 Color;

out vec4 FragColor;

uniform float scale;
#define AREA 16


// vec2 grad_i = vec2(vecx[i], vecy[i])
uniform float vecx[AREA];
uniform float vecy[AREA];

float rand(vec2 co){
    return fract(sin(dot(co, vec2(12.9898, 78.233))) * 43758.5453);
}


float noise(int x, int y){
    float x_AREA = float(x) * float(AREA)/ 1920.0;
    float y_AREA = float(y) * float(AREA)/ 1080.0;

    vec2 P = vec2(x_AREA,y_AREA);

    vec2 G_bot_left = vec2(float(vecx[int(floor(x_AREA))]),float(vecy[int(floor(y_AREA))]));
    vec2 G_bot_right = vec2(vecx[int(ceil(x_AREA))],vecy[int(floor(y_AREA))]);
    vec2 G_top_left = vec2(vecx[int(floor(x_AREA))],vecy[int(ceil(y_AREA))]);
    vec2 G_top_right = vec2(vecx[int(ceil(x_AREA))], vecy[int(ceil(y_AREA))]);




    return 1.0;
}

void main() {

//    vec3 cv = Color;

//    float colx = rand(Position);
    noise(int(Position.x),int(Position.y));
    float colx = vecx[int(mod(int(Position.x),AREA))];
    float coly = vecy[int(mod(int(Position.y),AREA))];
    FragColor = vec4(mix(colx,1.0, 0.1),coly,coly, 1.0);


}
