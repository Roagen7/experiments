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
#include "Raycaster.h"

using glm::vec3;

const int height = 1080;
const int width = 1920;



void ray::gl_main() {
    std::vector<float> points;
    std::vector<triangle> triangles;
    std::vector<sphere> objects;
    objects.reserve(4);

    objects.emplace_back(vec3(0.0,-1004.0,-20.0),1000, vec3((0.20,0.20,0.20)));
    objects.emplace_back(vec3(0.0,0.0,-40), 4.0, vec3(1.0,0.32,0.36));
    objects.emplace_back(vec3(5.0,     -2.0, -30), 2.0, vec3(0.90, 0.76, 0.46));

    Raycaster rc(width, height, vec3(0,0,-10), vec3(0,-0.3,0));

    for(int x = 0; x < width; x++){
        for(int y = 0; y < height; y++){
//            ray3 r;
//            rc.castRay(r,x,y);
//
//            vec3 col = rc.trace(r,objects);
            vec3 col = {0,0,0};
            points.push_back(x);
            points.push_back(y);
            points.push_back(col.x);
            points.push_back(col.y);
            points.push_back(col.z);

        }
    }






    GLFWwindow* window;
    createWindow(window, width,height);

//    Shader shader("../projects/ray/vs.glsl","../projects/ray/fs.glsl");

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

    std::vector<glm::vec3> sphCenter;
    std::vector<float> sphRadius;
    std::vector<glm::vec3> sphColor;
    for(auto o : objects){
        sphCenter.push_back(o.center);
        sphRadius.push_back(o.radius);
        sphColor.push_back(o.color);
    }

    shader.Unif("width",width);
    shader.Unif("height",height);
    shader.Unif("sphCenter",sphCenter);
    shader.Unif("sphRadius",sphRadius);
    shader.Unif("sphColor",sphColor);

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
