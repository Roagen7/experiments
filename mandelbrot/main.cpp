//
// Created by roagen on 11.09.2021.
//

#include "main.h"

//std::complex<float> pixIntoComplex(glm::vec2 pixel,std::complex<float> z0, float unitRe, float unitIm){
//    return z0 + std::complex((float) pixel.x * unitRe/ width, (float) -(pixel.y * unitIm/height));
//}
//
//
//
//void getEvents(GLFWwindow* window){
//    double xPos, yPos;
//    glfwGetCursorPos(window, &xPos, &yPos);
//    if(glfwGetMouseButton(window,GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS){
//        std::cout << pixIntoComplex({xPos,yPos}, Z_0, UNIT_RE, UNIT_IM) << std::endl;
//    }
//}


const int width = 1920;
const int height = 1080;

const int ITERS = 100;
const std::complex<float>Z_0 = {-1.5,1.0};
const float UNIT_RE = 2.0f;
const float UNIT_IM = 2.0f;



void mandelbrot::gl_main() {

    GLFWwindow* window;
    createWindow(window,width,height);



    std::vector<GLfloat> points;

    for(int x = 0; x < width; x++){
        for(int y=  0; y < height; y++){
            points.push_back(x);
            points.push_back(y);
            points.push_back(0.5f);
            points.push_back(0.0f);
            points.push_back(0.0f);
        }
    }

    //INIT


    GLuint shaderProgram;
    createShader("../vs.glsl","../fs.glsl",shaderProgram);

    glUseProgram(shaderProgram);
    glUniform1i(glGetUniformLocation(shaderProgram,"ITERS"), ITERS);
    glUniform1i(glGetUniformLocation(shaderProgram,"HEIGHT"), height);
    glUniform1i(glGetUniformLocation(shaderProgram,"WIDTH"), width);
    glUniform1f(glGetUniformLocation(shaderProgram,"unitRe"), UNIT_RE);
    glUniform1f(glGetUniformLocation(shaderProgram,"unitIm"), UNIT_IM);
    glUniform2f(glGetUniformLocation(shaderProgram, "z0"), Z_0.real(), Z_0.imag());
    // END DATA
//    glUseProgram(shaderProgram);
    GLuint VAO;
    bindData(points, VAO);


    //DRAWING
    while(!glfwWindowShouldClose(window)){

        glfwPollEvents();
//            getEvents(window);

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);
        glBindVertexArray(VAO);
        glPointSize(2.0);
        glDrawArrays(GL_POINTS, 0 , points.size());

        glfwSwapBuffers(window);

    }

}


void mandelbrot::getEvents(GLFWwindow *window) {

}


