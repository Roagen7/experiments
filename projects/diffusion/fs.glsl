#version 330 core
in vec2 Position;
in vec3 Color;

out vec4 FragColor;

uniform int AREA;
uniform mat4 rotationMatrix;


float interpolate(float a0, float a1, float w){
    return (a1 - a0) * ((w * (w * 6.0 - 15.0) + 10.0) * w * w * w) + a0;
}

vec2 transformVec(vec2 v, mat4 m){
    vec4 vHomographic = vec4(v,1.0,1.0) * m;

    return vec2(vHomographic.x, vHomographic.y);
}


vec2 randomGradient(int ix, int iy) {
    // No precomputed gradients mean this works for any number of grid coordinates
    int w = 8;
    int s = w / 2; // rotation width
    int a = ix, b = iy;
    a = a * 3284157443; b ^= a << s | a >> w-s;
    b *= 1911520717; a ^= b << s | b >> w-s;
    a *= 2048419325;
    float random = a * (3.14159265 / (4 >> 1)); // in [0, 2*Pi]
    vec2 v;
    v.x = sin(random); v.y = cos(random);
    return v;
}


float dot(vec2 v1, vec2 v2){
    return v1.x * v2.x + v1.y * v2.y;
}

float dotGradient(float ix, float iy, float x, float y){
    float dx = x - ix;
    float dy = y - iy;

    vec2 gradient = randomGradient(int(ix),int(iy));
    gradient = transformVec(gradient,rotationMatrix);
    return gradient.x * dx + gradient.y * dy;
//    return dot(vec2(dx,dy), vec2(vecx[int(ix)],vecy[int(iy)]));
}

float noise(float x, float y){
    x/=AREA;
    y/=AREA;

    int x0 = int(x);
    int x1 = x0 + 1;
    int y0 = int(y);
    int y1 = y0 + 1;

    float sx = x - float(x0);
    float sy = y - float(y0);

    float n0, n1, ix0, ix1, value;

    n0 = dotGradient(x0, y0, x, y);
    n1 = dotGradient(x1, y0, x, y);
    ix0 = interpolate(n0, n1, sx);

    n0 = dotGradient(x0, y1, x, y);
    n1 = dotGradient(x1, y1, x, y);
    ix1 = interpolate(n0, n1, sx);

    value = interpolate(ix0, ix1, sy);

    value = max(min(1.0f,value),-1.0f);
    return (value + 1.0)/ 2.0;
//    return std::max(0.0f,std::min(1.0f, val));
}

void main() {


    float col = noise(Position.x,Position.y);

    FragColor = vec4(col,col,col, 1.0);


}
