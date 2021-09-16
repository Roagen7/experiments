//
// Created by roagen on 15.09.2021.
//

#include <cmath>
#include <glm/gtx/rotate_vector.hpp>
#include "Raycaster.h"

Raycaster::Raycaster(int width, int height, vec3 E, vec3 rot): width(width), height(height), E(E), rot(rot) {
    this->invWidth = 1.0 / float(width);
    this->invHeight = 1.0 / float(height);
    this-> fov = 30;
    this->aspectratio = float(width) / float(height);
    this-> angle = tan(M_PI * 0.5 * fov / 180.);
    this->bgColor = {0.0,0.3, 0.7};

}

void Raycaster::castRay(ray3 &r, float x, float y) {

    float xx = (2 * ((x + 0.5) * invWidth) - 1) * angle * aspectratio;
    float yy = (1 - 2 * ((y + 0.5) * invHeight)) * angle;
    r.dir = glm::normalize(vec3(xx, yy, -1));

    auto rotMat = glm::rotate(glm::mat4(1.0f), this->rot.x, vec3(1.0,0.0,0.0)) *
            glm::rotate(glm::mat4(1.0f), this->rot.y, vec3(0.0,1.0,0.0)) *
            glm::rotate(glm::mat4(1.0f), this->rot.z, vec3(0.0,0.0,1.0));


    r.dir = glm::vec3 (rotMat * glm::vec4(r.dir,1.0));
    r.origin = this->E;
}



vec3 Raycaster::trace(ray3 primRay, std::vector<sphere> objects, int depth) {

        sphere small_sphere;
        bool hit = false;
        float t_near = INFINITY;

        for(auto o : objects){
            float t0 = INFINITY;
            float t1 = INFINITY;

            if(intersect(o,primRay,t0,t1)){
                if(t0 < 0) t0 = t1;
                if(t0 < t_near){
                    t_near = t0;
                    small_sphere = o;
                    hit = true;
                }
            }

        }

        if(hit){
            ray3 shadowRay;

            vec3 pHit = primRay.origin + primRay.dir * t_near;
            vec3 nHit = pHit - small_sphere.center;

            vec3 addCol;



            if(depth != MAX_DEPTH){
                ray3 reflectRay;
                reflectRay.dir = glm::normalize(glm::reflect(primRay.dir, glm::normalize(nHit)));
                reflectRay.origin = pHit + 0.2f * glm::normalize(nHit);

                addCol = trace(reflectRay, objects, depth + 1);
            }



            shadowRay.origin = pHit + 0.2f*glm::normalize(nHit);
            shadowRay.dir = glm::normalize(L.pos - pHit);
            bool isInShadow = false;

            vec3 outCol;

            float diffuse = (glm::dot(shadowRay.dir, glm::normalize(nHit)));
            float ambient = 0.7;
            float specular = pow(std::max(glm::dot(glm::normalize(E - pHit),glm::normalize(glm::reflect(-shadowRay.dir, glm::normalize(nHit)))), 0.0f),16);


            float phong = diffuse + ambient + specular;
            if(depth != MAX_DEPTH){
                outCol = ( 2.f * small_sphere.color + addCol) / 3.0f * phong;
            } else {
                outCol = small_sphere.color * phong;
            }


            for(auto o : objects){
                float t0 = INFINITY;
                float t1 = INFINITY;
                if(intersect(o,shadowRay,t0,t1) && o.center != small_sphere.center){
                    isInShadow = true;
                }
            }
            if(isInShadow){
                return  outCol / 2.0f;
//            return {0,0,0};
            }

            return outCol;
        } else {
            return bgColor;
        }

}


bool Raycaster::intersect(sphere sph, ray3 r, float& t0, float& t1){
    vec3 l = sph.center - r.origin;
    float tca = glm::dot(l,r.dir);
    if(tca < 0) return false;
    float d2 = glm::dot(l,l) - tca * tca;
    if(d2 > sph.radiusSq) return false;
    float thc = sqrt(sph.radiusSq - d2);
    t0 = tca - thc;
    t1 = tca + thc;

    return true;
}
