//
// Created by roagen on 13.09.2021.
//

#ifndef UNTITLED5_NOISE_H
#define UNTITLED5_NOISE_H
#include <glm/vec2.hpp>
#include <glm/vec3.hpp>
glm::vec3 transitionBetweenCols(glm::vec3 col1, glm::vec3 col2, float x);
float perlin(float x, float y, int AREA, unsigned SEED_A, unsigned SEED_B, unsigned SEED_C);
float perlin3D(float x,float y, float z, int AREA);

glm::vec2 randomGradient(int ix, int iy, unsigned SEED_A, unsigned SEED_B, unsigned SEED_C);
float dotGridGradient(int ix, int iy, float x, float y, unsigned SEED_A, unsigned SEED_B, unsigned SEED_C);
float interpolate(float a0, float a1, float w);


#endif //UNTITLED5_NOISE_H
