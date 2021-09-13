//
// Created by roagen on 13.09.2021.
//

#include "camera.h"
glm::vec3 camera::pos;
glm::vec3 camera::dir;

void camera::init(int w, int h, glm::vec3 p, glm::vec3 d) {

    pos = p;
    dir = d;

}