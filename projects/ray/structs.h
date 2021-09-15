//
// Created by roagen on 15.09.2021.
//

#ifndef UNTITLED5_STRUCTS_H
#define UNTITLED5_STRUCTS_H
#include <glm/vec3.hpp>
#include <glm/geometric.hpp>

using glm::vec3;

struct light {
    vec3 pos;
    vec3 col;
    light(vec3 p, vec3 c): pos(p), col(c){

    };
};

struct triangle {
    glm::vec3 verts[3];
    glm::vec3 color;

    triangle(){
        verts[0] = {0.0,0.0,0.0};
        verts[1] = {0.0,0.0,0.0};
        verts[2] = {0.0,0.0,0.0};
    }

    triangle(vec3 p1,vec3 p2,  vec3 p3){
        verts[0] = p1;
        verts[1] = p2;
        verts[2] = p3;
    }
};




struct sphere {
    vec3 center;
    float radius, radiusSq;
    vec3 color;

    sphere(vec3 cen,float rad, vec3 col):center(cen),radius(rad),color(col){
        radiusSq = rad * rad;
    }
    sphere() = default;

};

struct ray3 {
    vec3 origin;
    vec3 dir;
};




#endif //UNTITLED5_STRUCTS_H
