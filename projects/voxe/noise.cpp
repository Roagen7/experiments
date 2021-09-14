//
// Created by roagen on 13.09.2021.
//

#include <valarray>
#include "noise.h"


glm::vec3 transitionBetweenCols(glm::vec3 col1, glm::vec3 col2, float x){
    glm::vec3 m;
    m.r = (col2.r - col1.r );
    m.g = col2.g - col1.g;
    m.b = col2.b - col1.b;

    return {
            m.r * x + col1.r,
            m.g * x + col1.g,
            m.b * x + col1.b
    };

}


float interpolate(float a0, float a1, float w){
    return (a1 - a0) * ((w * (w * 6.0 - 15.0) + 10.0) * w * w * w) + a0;
};

glm::vec2 randomGradient(int ix, int iy, unsigned SEED_A, unsigned SEED_B, unsigned SEED_C) {
    // No precomputed gradients mean this works for any number of grid coordinates
    const unsigned w = 8 * sizeof(unsigned);
    const unsigned s = w / 2; // rotation width
    unsigned a = ix, b = iy;
    a *= SEED_A; b ^= a << s | a >> w-s;
    b *= SEED_B; a ^= b << s | b >> w-s;
    a *= SEED_C;
    float random = a * (3.14159265 / ~(~0u >> 1)); // in [0, 2*Pi]
//    float random = rand()%1000 * 3.14159;
    glm::vec2 v;
    v.x = sin(random); v.y = cos(random);
    return v;
}

float dotGridGradient(int ix, int iy, float x, float y, unsigned SEED_A, unsigned SEED_B, unsigned SEED_C) {
    // Get gradient from integer coordinates
    glm::vec2 gradient = randomGradient(ix, iy, SEED_A, SEED_B, SEED_C);

    // Compute the distance vector
    float dx = x - (float)ix;
    float dy = y - (float)iy;

    // Compute the dot-product
    return (dx*gradient.x + dy*gradient.y);
}

float perlin(float x, float y, int AREA, unsigned SEED_A, unsigned SEED_B, unsigned SEED_C) {
    // Determine grid cell coordinates



    x = (float) x / AREA;
    y = (float) y / AREA;

    int x0 = (int)x;
    int x1 = x0 + 1;
    int y0 = (int)y;
    int y1 = y0 + 1;

    // Determine interpolation weights
    // Could also use higher order polynomial/s-curve here
    float sx = x - (float)x0;
    float sy = y - (float)y0;

    // Interpolate between grid point gradients
    float n0, n1, ix0, ix1, value;

    n0 = dotGridGradient(x0, y0, x, y, SEED_A, SEED_B, SEED_C);
    n1 = dotGridGradient(x1, y0, x, y, SEED_A, SEED_B, SEED_C);
    ix0 = interpolate(n0, n1, sx);

    n0 = dotGridGradient(x0, y1, x, y, SEED_A, SEED_B, SEED_C);
    n1 = dotGridGradient(x1, y1, x, y, SEED_A, SEED_B, SEED_C);
    ix1 = interpolate(n0, n1, sx);

    value = interpolate(ix0, ix1, sy);
    return (value + 1.0f)/ 2.0f;
}

glm::vec3 randomGradient3D(int ix, int iy,int iz) {
    float PHI = 2.2323;
    float COSTHETA = -0.54;

    float theta = acos(COSTHETA);

    return {
        sin(theta) * cos(PHI),
        sin(theta) * sin(PHI),
        cos(theta) * cos(PHI)
    };

}


float dotGridGradient3D(int ix, int iy, int iz,float x, float y, float z){
    glm::vec3 gradient = randomGradient3D(ix, iy,iz);

    // Compute the distance vector
    float dx = x - (float)ix;
    float dy = y - (float)iy;
    float dz = y - (float)iz;
    // Compute the dot-product
    return (dx*gradient.x + dy*gradient.y + dz * gradient.z);
}



float perlin3D(float x,float y, float z, int AREA){

    // 0 - AREA

    x = (float) x / AREA;
    y = (float) y / AREA;
    z = (float) z / AREA;

    int x0 = (int)x;
    int x1 = x0 + 1;
    int y0 = (int)y;
    int y1 = y0 + 1;
    int z0 = (int)z;
    int z1 = z0 + 1;

    float sx = x - (float)x0;
    float sy = y - (float)y0;
    float sz = z - (float)z0;

    float n0, n1,ix0, ix1,ix2,ix3, iy0, iy1,value;

    n0 = dotGridGradient3D(x0,y0,z0, x, y, z);
    n1 = dotGridGradient3D(x1,y0,z0,x,y,z);
    ix0 = interpolate(n0,n1,sx);
    n0 = dotGridGradient3D(x0,y1,z0,x,y,z);
    n1 = dotGridGradient3D(x1,y1,z0,x,y,z);
    ix1 = interpolate(n0,n1,sx);

    n0 = dotGridGradient3D(x0,y0,z1,x,y,z);
    n1 = dotGridGradient3D(x1,y0,z1,x,y,z);
    ix2 = interpolate(n0,n1,sx);
    n0 = dotGridGradient3D(x1,y0,z1,x,y,z);
    n1 = dotGridGradient3D(x1,y1,z1,x,y,z);
    ix3 = interpolate(n0,n1,sx);

    iy0 = interpolate(ix0,ix1,sy);
    iy1 = interpolate(ix2,ix3,sy);

    value = interpolate(iy0,iy1,sz);

    return  (value + 1.0f)/ 2.0f;


}
