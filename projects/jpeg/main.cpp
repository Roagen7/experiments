//
// Created by roagen on 21.09.2021.
//

#include <iostream>
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include "main.h"
#include "../../abstr/glsl/Shader.h"
#include "../../abstr/databuffer/VAO.h"
#include "../../abstr/databuffer/VBO.h"
#include "../../functions/functions.h"

#include "../../include/stb/stb_image.h"

const int width = 1920;
const int height = 1080;


void openImage(const char *image, GLuint& TEX){
//    stbi_set_flip_vertically_on_load(true);
    int widthImg, heightImg, numColCh;
    unsigned char* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 0);


    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    if(numColCh == 4) glTexImage2D(GL_TEXTURE_2D, 0 ,GL_RGBA, widthImg, heightImg, 0, GL_RGBA, GL_UNSIGNED_BYTE, bytes);
    else if(numColCh == 3) glTexImage2D(GL_TEXTURE_2D, 0 ,GL_RGBA, widthImg, heightImg, 0, GL_RGB, GL_UNSIGNED_BYTE, bytes);
    else if(numColCh == 1) glTexImage2D(GL_TEXTURE_2D, 0 ,GL_RGBA, widthImg, heightImg, 0, GL_RED, GL_UNSIGNED_BYTE, bytes);
    else throw std::invalid_argument("Texture type recognition failed");



    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(bytes);
    glBindTexture(GL_TEXTURE_2D,0);

}




void jpeg::gl_main() {
    std::vector<float> points;


    for(int x = 0; x < width; x++){
        for(int y = 0; y < height; y++){
            glm::vec3 col = {1,0,0};

            points.push_back(x);
            points.push_back(y);
            points.push_back((float)x / width);
            points.push_back((float) y/ height);
            points.push_back(0.0);
        }
    }


    GLFWwindow* window;
    createWindow(window, width,height);


    GLuint TEX;
    glGenTextures(1, &TEX);
    glActiveTexture(GL_TEXTURE0);
    glBindTexture(GL_TEXTURE_2D, TEX);

    openImage("../projects/jpeg/test.jpg",TEX);




    VAO vao; VBO vbo;
    vao.Bind();
    vbo.Bind();
    vbo.Data(points);
    vao.Reserve(5 * sizeof(float));
    vao.Add<GLfloat>(2);
    vao.Add<GLfloat>(3);
    vao.Unbind();
    vbo.Unbind();

    Shader shader("../projects/jpeg/vs.glsl", "../projects/jpeg/fs.glsl");
    shader.Unif("width", (float) width);
    shader.Unif("height", (float) height);


    while(!glfwWindowShouldClose(window)){
        glfwPollEvents();




        shader.Use();
        glBindTexture(GL_TEXTURE_2D, TEX);
        glClearColor(0.0,0.0,0.0,1.0);
        glClear(GL_COLOR_BUFFER_BIT);
        vao.Bind();
        glDrawArrays(GL_POINTS, 0 , (float) points.size()/5.0);

        glfwSwapBuffers(window);
    }



}

