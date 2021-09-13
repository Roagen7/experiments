//
// Created by roagen on 13.09.2021.
//

#include "main.h"

const int width = 1920;
const int height = 1080;




void voxe::gl_main() {
    GLFWwindow* window;
    createWindow(window,width, height);

    GLuint shaderProgram;
    createShader("../projects/voxe/vs.glsl","../projects/voxe/fs.glsl", shaderProgram);


    float th = 0.0;

    camera::init(width,height,{0.0,0.0,0.0},{0.0,0.0,-1.0});


//    glUseProgram(shaderProgram);


    std::vector<GLfloat> points = {
            0.0f, 0.0f, 0.0f,    0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0f, 0.0f, 0.0f,

            1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0f, 1.0f, 1.0f,
            1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 0.0f, 1.0f,

            1.0f, 0.0f, 1.0f,    1.0f, 1.0f, 1.0f,    0.0f, 1.0f, 1.0f,
            1.0f, 0.0f, 1.0f,    0.0f, 1.0f, 1.0f,    0.0f, 0.0f, 1.0f,

            0.0f, 0.0f, 1.0f,    0.0f, 1.0f, 1.0f,    0.0f, 1.0f, 0.0f,
            0.0f, 0.0f, 1.0f,    0.0f, 1.0f, 0.0f,    0.0f, 0.0f, 0.0f,

            0.0f, 1.0f, 0.0f,    0.0f, 1.0f, 1.0f,    1.0f, 1.0f, 1.0f,
            0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 1.0f, 0.0f,

            1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f,
            1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f,    1.0f, 0.0f, 0.0f,
    };
    GLuint VAO;
    bindDataVec3(points, VAO);

    while(!glfwWindowShouldClose(window)){
        th+= 0.01;


        glfwPollEvents();
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

        auto mx  = glm::mat4(1.0f);
        mx = glm::translate(mx, {0.0f, -0.5f, -10.0f}) * glm::rotate(mx, th, {0.0,1.0,1.0});
        auto proj = glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 100.0f);


        glUseProgram(shaderProgram);
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram,"camMatrix"), 1, GL_FALSE, glm::value_ptr(proj * mx));


        glBindVertexArray(VAO);
        glDrawArrays(GL_TRIANGLES, 0 , points.size());
        glfwSwapBuffers(window);
    }


    glDeleteBuffers(1,&VAO);
    glDeleteShader(shaderProgram);
    glfwDestroyWindow(window);
    glfwTerminate();

}


void voxe::bindDataVec3(std::vector<GLfloat> points, GLuint &VAO) {
    unsigned int VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);


    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER,points.size() * sizeof(GLfloat), points.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0,3, GL_FLOAT, GL_FALSE, 3* sizeof(GLfloat), (void*)nullptr);

    glEnableVertexAttribArray(0);

    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER,0);

    glDeleteBuffers(1,&VBO);

}