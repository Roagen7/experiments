//
// Created by roagen on 15.09.2021.
//

#ifndef UNTITLED5_RAYCASTER_H
#define UNTITLED5_RAYCASTER_H

#include <glm/vec3.hpp>
#include <vector>
#include "structs.h"
using glm::vec3;



class Raycaster {
private:
    const int MAX_DEPTH = 3;
    int width;
    int height;
    vec3 E;
    vec3 rot;
    vec3 bgColor;
    float aspectratio;
    float fov;
    float angle;
    float invWidth;
    float invHeight;
    light L = light(vec3(0.0,20.0,-30.0), vec3(1.0,1.0,1.0));

//    const light L({0.0,20.0,-30.0}, {1.0,1.0,1.0});
public:
    Raycaster(int width, int height, vec3 E, vec3 rot);
    void castRay(ray3& r,float x, float y);
    vec3 trace(ray3 primRay, std::vector<sphere> objects, int depth = 0);
    static bool intersect(sphere sph, ray3 r, float& t0, float& t1);

};


#endif //UNTITLED5_RAYCASTER_H
