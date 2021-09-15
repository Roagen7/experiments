//
// Created by roagen on 15.09.2021.
//

#include <iostream>
#include <glm/vec3.hpp>
#include <glm/geometric.hpp>
#include <vector>
#include <glad/glad.h>
#include <GLFW/glfw3.h>


#include "main.h"
#include "../../functions/functions.h"
#include "../../abstr/glsl/Shader.h"

using glm::vec3;

const int height = 1080;
const int width = 1920;

float invWidth = 1 / float(width), invHeight = 1 / float(height);
float fov = 30, aspectratio = width / float(height);
float angle = tan(M_PI * 0.5 * fov / 180.);


vec3 E = {0,0,0};

struct light {
    vec3 pos;
    vec3 col;
    light(vec3 p, vec3 c): pos(p), col(c){

    };


};

light L({0.0,20.0,-30.0}, {1.0,1.0,1.0});

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



bool intersect(sphere sph, ray3 r, float& t0, float& t1){
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

void castRay(ray3& r,float x, float y){
    float xx = (2 * ((x + 0.5) * invWidth) - 1) * angle * aspectratio;
    float yy = (1 - 2 * ((y + 0.5) * invHeight)) * angle;
    r.dir = glm::normalize(vec3(xx, yy, -1));
    r.dir = glm::vec3 (glm::rotate(glm::mat4(1.0f), 0.0f, vec3(0.0,1.0,0.0)) * glm::vec4(r.dir,1.0));
    r.origin = E;
}

float distSq(vec3 p1, vec3 p2){
    return p1.x * p2.x + p1.y * p2.y + p1.z * p2.z;
}

vec3 trace(ray3 primRay, std::vector<sphere> objects, int depth = 0){
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

        shadowRay.origin = pHit + 0.2f*glm::normalize(nHit);
        shadowRay.dir = glm::normalize(L.pos - pHit);
        bool isInShadow = false;

        for(auto o : objects){
            float t0 = INFINITY;
            float t1 = INFINITY;
            if(intersect(o,shadowRay,t0,t1) && o.center != small_sphere.center){
                isInShadow = true;
            }
        }
        if(isInShadow){
            return  (small_sphere.color) / 2.0f;
        }

        return small_sphere.color;
    } else {
        return {0,0,0};
    }


}


void ray::gl_main() {
    std::vector<float> points;
    std::vector<triangle> triangles;
    std::vector<sphere> objects;
    objects.reserve(4);

    objects.emplace_back(vec3(0.0,-1004.0,-20.0),1000, vec3((0.20,0.20,0.20)));
    objects.emplace_back(vec3(0.0,0.0,-30), 4.0, vec3(1.0,0.32,0.36));
    objects.emplace_back(vec3(5.0,     -2, -33), 2.0, vec3(0.90, 0.76, 0.46));

    for(int x = 0; x < width; x++){
        for(int y = 0; y < height; y++){
            ray3 r;
            castRay(r,x,y);

            vec3 col = trace(r,objects);

            points.push_back(x);
            points.push_back(y);
            points.push_back(col.x);
            points.push_back(col.y);
            points.push_back(col.z);

        }
    }






    GLFWwindow* window;
    createWindow(window, width,height);

    Shader shader("../projects/ray/vs.glsl","../projects/ray/fs.glsl");
    VAO vao; VBO vbo;
    vao.Bind();
    vbo.Bind();
    vbo.Data(points);
    vao.Reserve(5 * sizeof(float));
    vao.Add<GLfloat>(2);
    vao.Add<GLfloat>(3);
    vao.Unbind();
    vbo.Unbind();

    shader.Unif("width",width);
    shader.Unif("height",height);


    while(!glfwWindowShouldClose(window)){
        glfwPollEvents();

            glClearColor(0.0,0.0,0.0,1.0);
            glClear(GL_COLOR_BUFFER_BIT);

            shader.Use();
            vao.Bind();
            glDrawArrays(GL_POINTS, 0 , (float) points.size()/5.0);


        glfwSwapBuffers(window);
    }



}
