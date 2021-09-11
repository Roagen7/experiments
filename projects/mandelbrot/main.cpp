//
// Created by roagen on 11.09.2021.
//

#include "main.h"


const int width = 1920;
const int height = 1080;

const int ITERS = 100;
const int SET = 1; // 0 - mandelbrot 1 - julia

 std::complex<float>Z_0 = {-1.5,1.0};
std::complex<float> C = {-0.8f, 0.156f};
 float UNIT_RE = 2.0f;
 float UNIT_IM = 2.0f;

float SPEED = 3.0f;


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


    GLuint shaderProgram;
    createShader("../projects/mandelbrot/vs.glsl","../projects/mandelbrot/fs.glsl",shaderProgram);

    glUseProgram(shaderProgram);
    glUniform1i(glGetUniformLocation(shaderProgram,"ITERS"), ITERS);
    glUniform1i(glGetUniformLocation(shaderProgram,"HEIGHT"), height);
    glUniform1i(glGetUniformLocation(shaderProgram,"WIDTH"), width);
    glUniform1i(glGetUniformLocation(shaderProgram, "SET"), SET);


    GLuint VAO;
    bindData(points, VAO);

    float th = 0;

    while(!glfwWindowShouldClose(window)){

//        C = 0.7885f * eix(th);
//        th += 0.01;

        glfwPollEvents();
            getEvents(window);

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);
        glUseProgram(shaderProgram);

        glUniform2f(glGetUniformLocation(shaderProgram, "z0"), Z_0.real(), Z_0.imag());
        glUniform2f(glGetUniformLocation(shaderProgram, "c"), C.real(),C.imag());
        glUniform1f(glGetUniformLocation(shaderProgram,"unitRe"), UNIT_RE);
        glUniform1f(glGetUniformLocation(shaderProgram,"unitIm"), UNIT_IM);

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

std::complex<float> mandelbrot::pixToComplex(glm::vec2 pixel, std::complex<float> z0, float unitRe, float unitIm){
    return z0 + std::complex((float) pixel.x * unitRe/ width, (float) -(pixel.y * unitIm/height));
}


void mandelbrot::getEvents(GLFWwindow *window) {
    double xPos, yPos;
    glfwGetCursorPos(window, &xPos, &yPos);
    if(glfwGetMouseButton(window,GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS){
        std::cout << pixToComplex({xPos,yPos}, Z_0, UNIT_RE, UNIT_IM) << std::endl;
//        auto zi = pixToComplex({xPos,yPos}, Z_0, UNIT_RE, UNIT_IM);
//        if(zi != Z_0){
//            Z_0 = zi;
//        }
    }
    if(glfwGetKey(window, GLFW_KEY_UP) == GLFW_PRESS){
        Z_0 = Z_0 + std::complex(0.0f,(float)UNIT_IM * SPEED / height  );

    }
    if(glfwGetKey(window, GLFW_KEY_DOWN) == GLFW_PRESS){
        Z_0 = Z_0 + std::complex(0.0f,-(float)UNIT_IM * SPEED / height  );
    }
    if(glfwGetKey(window, GLFW_KEY_RIGHT) == GLFW_PRESS){
        Z_0 = Z_0 + std::complex((float)UNIT_RE * SPEED/ height ,0.0f );
    }
    if(glfwGetKey(window, GLFW_KEY_LEFT) == GLFW_PRESS){
        Z_0 = Z_0 + std::complex(-(float)UNIT_RE * SPEED/ height ,0.0f );
    }

    if(glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS){
        UNIT_RE = 0.9f * UNIT_RE;
        UNIT_IM = 0.9f * UNIT_IM;
    }

    if(glfwGetKey(window, GLFW_KEY_LEFT_CONTROL) == GLFW_PRESS){
        UNIT_RE = 1.1f * UNIT_RE;
        UNIT_IM = 1.1f * UNIT_IM;
    }

    if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS){
        SPEED = 10.0f;
    }
    if(glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_RELEASE){
        SPEED  = 3.0f;
    }

}

std::complex<float> mandelbrot::eix(float x){
    return {cosf(x), sinf(x)};
}


