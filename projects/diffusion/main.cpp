//
// Created by roagen on 11.09.2021.
//

#include "main.h"
//
//


const int width = 1920;
const int height = 1080;

const int AREA = 16;


void diffusion::gl_main() {

    GLFWwindow* window;
    createWindow(window,width,height);

    float vecx[AREA];
    float vecy[AREA];
    for(int i =0; i < 16; i++){
        vecx[i] = (float) rand()/RAND_MAX;
        vecy[i] = (float) rand()/RAND_MAX;
    }


    std::vector<GLfloat> points;

    for(int x = 0; x < width; x++){
        for(int y =  0; y < height; y++){
            points.push_back(x);
            points.push_back(y);
            points.push_back(1.0f);
            points.push_back(1.0f);
            points.push_back(1.0f);
        }
    }

//    cells[500][500].a = 1.0f;


    GLuint shaderProgram;
    createShader("../projects/diffusion/vs.glsl","../projects/diffusion/fs.glsl",shaderProgram);

    glUseProgram(shaderProgram);
    glUniform1i(glGetUniformLocation(shaderProgram,"WIDTH"),width);
    glUniform1i(glGetUniformLocation(shaderProgram,"HEIGHT"),height);
    glUniform1fv(glGetUniformLocation(shaderProgram, "vecx"), AREA, vecx);
    glUniform1fv(glGetUniformLocation(shaderProgram,"vecy"),AREA,vecy);

    GLuint VAO;
    bindData(points, VAO);

    float th = 0;
    while(!glfwWindowShouldClose(window)){


        th += 0.01;

        glfwPollEvents();


        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);

        glBindVertexArray(VAO);
        glPointSize((float) 1.0);
        glDrawArrays(GL_POINTS, 0 , points.size());

        glfwSwapBuffers(window);

    }
    glDeleteBuffers(1,&VAO);
    glDeleteShader(shaderProgram);
    glfwDestroyWindow(window);
    glfwTerminate();
}


