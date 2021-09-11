#version 330 core
in vec2 Position;
in vec3 Color;

out vec4 FragColor;

uniform float scale;
#define AREA 32


uniform float vecx[AREA];
uniform float vecy[AREA];

float rand(vec2 co){
    return fract(sin(dot(co, vec2(12.9898, 78.233))) * 43758.5453);
}

float dot(vec2 v1, vec2 v2){
    return v1.x * v2.x + v1.y * v2.y;
}

float dotGradient(float ix, float iy, float x, float y){
    float dx = x - ix;
    float dy = y - iy;
    return dot(vec2(dx,dy), vec2(vecx[int(ix)],vecy[int(iy)]));
}

float noise(float x, float y){
    float x_AREA =  x/ 1920.0 * AREA;
    float y_AREA = y / 1080.0 * AREA;

    float x0 = floor(x_AREA);
    float y0 = floor(y_AREA);
    float x1 = x0 + 1;
    float y1 = y0 + 1;

    float sx = x_AREA - float(x0);
    float sy = y_AREA - float(y0);

    float n0 = dotGradient(x0,y0, x_AREA,y_AREA);
    float n1 = dotGradient(x1,y0,x_AREA,y_AREA);
    float ix0 = mix(n0,n1,sx);
    n0 = dotGradient(x0,y1,x_AREA,y_AREA);
    n1 = dotGradient(x1,y1,x_AREA,y_AREA);
    float ix1 = mix(n0,n1,sx);

    return  mix(ix0,ix1, sy);
}

void main() {


//    float col = noise(Position.x, Position.y);

//    FragColor = vec4(col,col,col, 1.0);
    FragColor = vec4(Color,1.0);

}
