//
// Created by roagen on 24.10.2021.
//


#include "main.h"
#include "../../functions/functions.h"
#include "../../functions/camera.h"
#include "../voxe/voxel.h"
#include "../../abstr/glsl/Shader.h"
#include "mesh.h"

const int width = 1920;
const int height = 1080;



void soft::gl_main() {




    GLFWwindow* window;
    createWindow(window,width, height);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_DEPTH_CLAMP);



//    GLuint shaderProgram;

//    createShader("../projects/soft/vs.glsl","../projects/soft/fs.glsl", shaderProgram);

    Shader sh("../projects/soft/vs.glsl","../projects/soft/fs.glsl");
    sh.Unif("color",glm::vec3(1,0,0));

    camera::init(width,height,{0.0,0.0,0.0},{0.0,0.0,-1.0});


    std::vector<float> points;

    auto vao = VAO();

    mesh m(cube);

    float t = 0.0;

    while(!glfwWindowShouldClose(window)){

        glfwPollEvents();
        camera::input(window);

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);

        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
//        glUseProgram(shaderProgram);


        m.modelMatrix = glm::rotate(glm::mat4(1.0),t,{0,1,1});
        t+=0.001;
        glPointSize(10);

        m.draw(sh,camera::view());
//        glDrawArrays(GL_POINTS, 0 , (float) points.size()/3.0);


        glfwSwapBuffers(window);
    }


//    glDeleteShader(shaderProgram);
    glfwDestroyWindow(window);
    glfwTerminate();

}
