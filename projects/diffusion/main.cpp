//
// Created by roagen on 11.09.2021.
//

#include "main.h"
//
//


const int width = 1920;
const int height = 1080;

const int AREA = 32;
float vecx[AREA];
float vecy[AREA];

glm::vec2 randomGradient(int ix, int iy) {
    // No precomputed gradients mean this works for any number of grid coordinates
    const unsigned w = 8 * sizeof(unsigned);
    const unsigned s = w / 2; // rotation width
    unsigned a = ix, b = iy;
    a *= 3284157443; b ^= a << s | a >> w-s;
    b *= 1911520717; a ^= b << s | b >> w-s;
    a *= 2048419325;
    float random = a * (3.14159265 / ~(~0u >> 1)); // in [0, 2*Pi]
    glm::vec2 v;
    v.x = sin(random); v.y = cos(random);
    return v;
}


float interpolate(float a0, float a1, float w){
    return (a1 - a0) * ((w * (w * 6.0 - 15.0) + 10.0) * w * w * w) + a0;
}


float dot(glm::vec2 v1, glm::vec2 v2){
    return v1.x * v2.x + v1.y * v2.y;
}

float dotGradient(int ix, int iy, float x, float y){
    float dx = x - (float)ix;
    float dy = y - (float)iy;
    glm::vec2 gradient = randomGradient(ix,iy);
//    glm::vec2 gradient =  glm::vec2(vecx[int(ix)],vecy[int(iy)]);
//    return dot(glm::vec2(dx,dy), glm::vec2(vecx[int(ix)],vecy[int(iy)]));
    return (dx*gradient.x + dy*gradient.y);
}

float noise(float x, float y){
    x/=AREA;
    y/=AREA;
//    x = x * AREA / 1920;
//    y = y * AREA/ 1920;
    int x0 = (int)x;
    int x1 = x0 + 1;
    int y0 = (int)y;
    int y1 = y0 + 1;


    float sx = x - (float)x0;
    float sy = y - (float)y0;

    float n0, n1, ix0, ix1, value;

    n0 = dotGradient(x0, y0, x, y);
    n1 = dotGradient(x1, y0, x, y);
    ix0 = interpolate(n0, n1, sx);

    n0 = dotGradient(x0, y1, x, y);
    n1 = dotGradient(x1, y1, x, y);
    ix1 = interpolate(n0, n1, sx);

    value = interpolate(ix0, ix1, sy);

    value = std::max(std::min(1.0f,value),-1.0f);
    return (value + 1.0)/ 2.0;
//    return std::max(0.0f,std::min(1.0f, val));
}



void diffusion::gl_main() {

    GLFWwindow* window;
    createWindow(window,width,height);
    srand(time(NULL));

    for(int i =0; i < AREA; i++){
        vecx[i] = (float) rand()/RAND_MAX;
        vecy[i] = (float) rand()/RAND_MAX;

    }



    std::vector<GLfloat> points;

    for(int x = 0; x < width; x++){
        for(int y =  0; y < height; y++){

//            std::cout << floor(x / 1920.0 * AREA) << " " << floor(y / 1080.0 * AREA) << std::endl;
            points.push_back(x);
            points.push_back(y);

            float v = noise(x,y);

            points.push_back(v);
            points.push_back(v);
            points.push_back(v);
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
        glPointSize((float) 2.0);
        glDrawArrays(GL_POINTS, 0 , points.size());

        glfwSwapBuffers(window);

    }
    glDeleteBuffers(1,&VAO);
    glDeleteShader(shaderProgram);
    glfwDestroyWindow(window);
    glfwTerminate();
}



