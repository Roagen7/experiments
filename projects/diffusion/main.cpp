//
// Created by roagen on 11.09.2021.
//

#include "main.h"


const int width = 1920;
const int height = 1080;

const int ITERS = 256;
const int SET = 0; // 0 - mandelbrot 1 - julia

 std::complex<float>Z_0F = {-1.5,1.0};
std::complex<float> CF = {-0.8f, 0.156f};
 float UNIT_REF = 2.0f;
 float UNIT_IMF = 2.0f;

float SPEEDF = 3.0f;


void diffusion::gl_main() {

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


    GLuint shaderProgram;
    createShader("../projects/diffusion/vs.glsl","../projects/diffusion/fs.glsl",shaderProgram);

    glUseProgram(shaderProgram);
    glUniform1i(glGetUniformLocation(shaderProgram,"WIDTH"),width);
    glUniform1i(glGetUniformLocation(shaderProgram,"HEIGHT"),height);
    GLuint VAO;
    bindData(points, VAO);

    float th = 0;

    while(!glfwWindowShouldClose(window)){

//        C = 0.7885f * eix(th);
        th += 0.01;

        glfwPollEvents();
            getEvents(window);

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);

        glBindVertexArray(VAO);
        glPointSize(1.0);
        glDrawArrays(GL_POINTS, 0 , points.size());

        glfwSwapBuffers(window);

    }
    glDeleteBuffers(1,&VAO);
    glDeleteShader(shaderProgram);
    glfwDestroyWindow(window);
    glfwTerminate();
}

std::complex<float> diffusion::pixToComplex(glm::vec2 pixel, std::complex<float> z0, float unitRe, float unitIm){
    return z0 + std::complex((float) pixel.x * unitRe/ width, (float) -(pixel.y * unitIm/height));
}


void diffusion::getEvents(GLFWwindow *window) {
    double xPos, yPos;
    glfwGetCursorPos(window, &xPos, &yPos);
    if(glfwGetMouseButton(window,GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS){
        std::cout << pixToComplex({xPos,yPos}, Z_0F, UNIT_REF, UNIT_IMF) << std::endl;
//        auto zi = pixToComplex({xPos,yPos}, Z_0, UNIT_RE, UNIT_IM);
//        if(zi != Z_0){
//            Z_0 = zi;
//        }
    }
    if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){
        Z_0F = Z_0F + std::complex(0.0f,(float)UNIT_IMF * SPEEDF / height  );

    }
    if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS){
        Z_0F = Z_0F + std::complex(0.0f,-(float)UNIT_IMF * SPEEDF / height  );
    }
    if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS){
        Z_0F = Z_0F + std::complex((float)UNIT_REF * SPEEDF/ height ,0.0f );
    }
    if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS){
        Z_0F = Z_0F + std::complex(-(float)UNIT_REF * SPEEDF/ height ,0.0f );
    }

    if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS){
        UNIT_REF = 0.9f * UNIT_REF;
        UNIT_IMF = 0.9f * UNIT_IMF;
    }

    if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS){
        UNIT_REF = 1.1f * UNIT_REF;
        UNIT_IMF = 1.1f * UNIT_IMF;
    }

    if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS){
        SPEEDF = 10.0f;
    }
    if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE){
        SPEEDF  = 3.0f;
    }

}

std::complex<float> diffusion::eix(float x){
    return {cosf(x), sinf(x)};
}


