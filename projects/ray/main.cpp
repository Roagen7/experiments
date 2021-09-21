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
#include "structs.h"
#include "Raycaster.h"
#include "../../functions/camera.h"
#include "Visible.h"

using glm::vec3;

const int height = 1080;
const int width = 1920;

vec3 E = {0,0,0};
vec3 dir = {0,0,-1};
auto rot = glm::mat4(1.0f);
float fov = 30.0;
bool GPU = true;

void ray::gl_main() {
    std::vector<float> points;
    std::vector<triangle> triangles;
    std::vector<sphere> objects;

    Visible vis(sphere(vec3(0.0,-1004.0,-20.0),1000, vec3((0.20,0.20,0.20))));


    objects.emplace_back(vec3(0.0,-1004.0,-20.0),1000, vec3((0.20,0.20,0.20)));
    objects.emplace_back(vec3(0.0,0.0,-40), 4.0, vec3(1.0,0.32,0.36));
    objects.emplace_back(vec3(5.0,     -2.0, -30), 2.0, vec3(0.90, 0.76, 0.46));
//    objects.emplace_back(vec3(10.5,-3.0,-20.0),1.0, vec3(0.9, 0.9, 0.9));
//    objects.emplace_back(vec3(-10.0, 0.0, -20.0), 10.0, vec3(0.0,1.0,0.0));
    objects.emplace_back(vec3( 5.0,      0, -25),     3, vec3(0.65, 0.77, 0.97), 1, 0.0);

    Raycaster rc(width, height, E, vec3(0,0.0,0));

    for(int x = 0; x < width; x++){
        for(int y = 0; y < height; y++){
            vec3 col = {0,0,0};

            if(!GPU){
                ray3 r;
                rc.castRay(r,x,y);

                col = rc.trace(r,objects);
            }



            points.push_back(x);
            points.push_back(y);
            points.push_back(col.x);
            points.push_back(col.y);
            points.push_back(col.z);

        }
    }






    GLFWwindow* window;
    createWindow(window, width,height);


    VAO vao; VBO vbo;
    vao.Bind();
    vbo.Bind();
    vbo.Data(points);
    vao.Reserve(5 * sizeof(float));
    vao.Add<GLfloat>(2);
    vao.Add<GLfloat>(3);
    vao.Unbind();
    vbo.Unbind();

    Shader shader("../projects/ray/ray_vs.glsl", "../projects/ray/ray_fs.glsl");
    Shader CPUshader("../projects/ray/vs.glsl", "../projects/ray/fs.glsl");



    if(GPU){
        std::vector<glm::vec3> sphCenter;
        std::vector<float> sphRadius;
        std::vector<glm::vec3> sphColor;
        for(auto o : objects){
            sphCenter.push_back(o.center);
            sphRadius.push_back(o.radius);
            sphColor.push_back(o.color);

        }
        shader.Unif("OBJNUM",(int) objects.size());
        shader.Unif("CURRENT_DEPTH",  3);
        shader.Unif("width",(float) width);
        shader.Unif("height",(float) height);
        shader.Unif("sphCenter",sphCenter);
        shader.Unif("sphRadius",sphRadius);
        shader.Unif("sphColor",sphColor);

    } else {
        CPUshader.Unif("width", (float) width);
        CPUshader.Unif("height", (float) height);

    }


    while(!glfwWindowShouldClose(window)){
        glfwPollEvents();

        if(GPU){
            handleEvents(window);
        }


        glClearColor(0.0,0.0,0.0,1.0);
        glClear(GL_COLOR_BUFFER_BIT);



        if(GPU){
            shader.Use();
            shader.Unif("E",E);
            shader.Unif("camRot", rot);
            shader.Unif("fov", fov);
        } else {
            CPUshader.Use();
        }

        vao.Bind();
        glDrawArrays(GL_POINTS, 0 , (float) points.size()/5.0);

        glfwSwapBuffers(window);
    }



}

void ray::handleEvents(GLFWwindow* window){
    vec3 UP = {0,1,0};
    float rotAngle = 0.01f;
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
        E += dir;
    }
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
        E -= dir;
    }
    if(glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
        E += glm::cross(dir,UP);
    }
    if(glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
        E -= glm::cross(dir,UP);
    }
    if(glfwGetKey(window,GLFW_KEY_SPACE) == GLFW_PRESS){
        E += UP;
    }
    if(glfwGetKey(window,GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS){
        E -= UP;
    }

    if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS){
        rot = glm::rotate(rot,rotAngle, UP);
        dir = glm::vec4(dir,1.0) * glm::rotate(glm::mat4(1.0f),rotAngle ,UP);
    }
    if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS){
        rot = glm::rotate(rot,-rotAngle, UP);
        dir = glm::vec4(dir,1.0) * glm::rotate(glm::mat4(1.0f),-rotAngle ,UP);
    }
    if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){
        rot = glm::rotate(rot,-rotAngle, glm::cross(dir,UP));
        dir = glm::vec4(dir,1.0) * glm::rotate(glm::mat4(1.0f),-rotAngle ,glm::cross(dir,UP));
    }
    if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS){
        rot = glm::rotate(rot,rotAngle, glm::cross(dir,UP));
        dir = glm::vec4(dir,1.0) * glm::rotate(glm::mat4(1.0f),rotAngle ,glm::cross(dir,UP));
    }
    if(glfwGetKey(window,GLFW_KEY_LEFT_ALT) == GLFW_PRESS){
        fov += 1.0f;
    }
    if(glfwGetKey(window, GLFW_KEY_RIGHT_ALT) == GLFW_PRESS){
        fov -= 1.0f;
    }



}

