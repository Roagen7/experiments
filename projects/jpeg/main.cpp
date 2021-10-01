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

//#include "../../include/stb/stb_image.h"

#define STB_IMAGE_IMPLEMENTATION
#include <stb_image.h>

const int width = 1920;
const int height = 1080;

typedef std::vector<std::vector<glm::vec3>> arr3;


void getPixel(stbi_uc *image, size_t H, size_t y, size_t x, stbi_uc *r, stbi_uc *g, stbi_uc *b, int numColCh = 3){
    const stbi_uc *p = image + (4 * (x * H + y));
    *r = image[numColCh * (x * H + y) + 0];
    *g = image[numColCh * (x * H + y) + 1];
    *b = image[numColCh * (x * H + y) + 2];
//    *a = image[4 * (x * H + y) + 3];
}

void rgbToTex(arr3 rgb, stbi_uc*& output){

    int i = 0;
    for(int x = 0; x < width; x++){
        for(int y = 0; y < height; y++){
            output[i] = (stbi_uc) rgb[x][y].x;
            output[i + 1] = (stbi_uc) rgb[x][y].y;
            output[i + 2] = (stbi_uc) rgb[x][y].z;
            i+=3;
        }
    }
}

arr3 toGray(arr3 rgb){
    int widthImg = rgb.size();
    int heightImg = rgb[0].size();
    arr3 gray(widthImg, std::vector<glm::vec3>(heightImg,{0,0,0}));
    for(int x = 0; x < widthImg; x++){
        for(int y = 0; y < heightImg; y++){
            gray[x][y] = {rgb[x][y].x,rgb[x][y].x, rgb[x][y].x };

        }
    }
    return gray;

}

arr3 toRgb(arr3 ycc){
    int widthImg = ycc.size();
    int heightImg = ycc[0].size();
    arr3 rgb(widthImg, std::vector<glm::vec3>(heightImg,{0,0,0}));
    auto crtmat = glm::mat3();
    crtmat[0][0] = 0.299; crtmat[0][1] = 0.587; crtmat[0][2] = 0.144;
    crtmat[1][0] = -0.169; crtmat[1][1] = -0.331; crtmat[1][2] = 0.5;
    crtmat[2][0] = 0.5; crtmat[2][1] = -0.419; crtmat[2][2] = -0.081;

    crtmat = glm::inverse(crtmat);
    for(int x = 0; x < widthImg; x++){
        for(int y = 0; y < heightImg; y++){

            rgb[x][y] =  crtmat *  (ycc[x][y] - glm::vec3(0, 128, 128));

        }
    }
    return rgb;
}


arr3 toYCbCr(arr3 rgb){
    int widthImg = rgb.size();
    int heightImg = rgb[0].size();
    auto crtmat = glm::mat3();
    crtmat[0][0] = 0.299; crtmat[0][1] = 0.587; crtmat[0][2] = 0.144;
    crtmat[1][0] = -0.169; crtmat[1][1] = -0.331; crtmat[1][2] = 0.5;
    crtmat[2][0] = 0.5; crtmat[2][1] = -0.419; crtmat[2][2] = -0.081;
//
//    crtmat[0][0] = 0.299; crtmat[0][1] = -0.169; crtmat[0][2] = 0.5;
//    crtmat[1][0] = 0.587;  crtmat[1][1] = -0.331; crtmat[1][2] = -0.418531;
//    crtmat[2][0] =  0.144; crtmat[2][1] = 0.5; crtmat[2][2] = -0.081;


    arr3 ycc(widthImg, std::vector<glm::vec3>(heightImg,{0,0,0}));
    for(int x = 0; x < widthImg; x++){
        for(int y = 0; y < heightImg; y++){
//            ycc[x][y].x = 16.f + (65.481 * rgb[x][y].x + 128.53 * rgb[x][y].y + 24.966 * rgb[x][y].z); // Y
//            ycc[x][y].y = 128.f + (-37.797 * rgb[x][y].x - 74.203 * rgb[x][y].y + 112.0 * rgb[x][y].z); // Cb
//            ycc[x][y].z = 128.f + (112.0 * rgb[x][y].x - 93.786 * rgb[x][y].y - 18.214 * rgb[x][y].z); // Cr


            ycc[x][y] =glm::vec3(0,128,128) +  crtmat *   rgb[x][y];
//            ycc[x][y] =  crtmat *   rgb[x][y];


        }
    }


    return ycc;
}

arr3 extractColor(stbi_uc* input, int widthImg, int heightImg, int numColCh){
    arr3 cols(widthImg,std::vector<glm::vec3>(heightImg,{0,0,0}));

    for(int x = 0; x < widthImg; x++){
        for(int y = 0; y < heightImg; y++){
            stbi_uc r, g, b;
            getPixel(input, heightImg, y , x, &r, &g, &b);
            cols[x][y] = {(int)r, (int)g, (int)b};
        }
    }

    return cols;
}



void jpegCompress(const char *image, GLuint& TEX){
//    stbi_set_flip_vertically_on_load(true);
    int widthImg, heightImg, numColCh;
    stbi_uc* bytes = stbi_load(image, &widthImg, &heightImg, &numColCh, 3);
    stbi_uc* bits;

    bits = (stbi_uc *) malloc(3 * numColCh * widthImg * heightImg * sizeof(stbi_uc));

//
//
    auto mat = extractColor(bytes, widthImg, heightImg, numColCh);
//    mat = toGray(mat);
    mat = toYCbCr(mat);
//    mat = toRgb(mat);
//    rgbToTex(mat,bits);



    int i = 0;
    for(int x=  0; x < widthImg; x++){
        for(int y = 0; y < heightImg; y++){
            bits[i] = (stbi_uc) mat[x][y].x;
            bits[i + 1] = (stbi_uc) mat[x][y].y;
            bits[i + 2] = (stbi_uc) mat[x][y].z;
            i += 3;
        }
    }





    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MIN_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_MAG_FILTER, GL_NEAREST);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_S, GL_REPEAT);
    glTexParameteri(GL_TEXTURE_2D, GL_TEXTURE_WRAP_T, GL_REPEAT);

    if(numColCh == 4) glTexImage2D(GL_TEXTURE_2D, 0 ,GL_RGBA, widthImg, heightImg, 0, GL_RGBA, GL_UNSIGNED_BYTE, bits);
    else if(numColCh == 3) glTexImage2D(GL_TEXTURE_2D, 0 ,GL_RGBA, widthImg, heightImg, 0, GL_RGB, GL_UNSIGNED_BYTE, bits);
    else if(numColCh == 1) glTexImage2D(GL_TEXTURE_2D, 0 ,GL_RGBA, widthImg, heightImg, 0, GL_RED, GL_UNSIGNED_BYTE, bits);
    else throw std::invalid_argument("Texture type recognition failed");



    glGenerateMipmap(GL_TEXTURE_2D);

    stbi_image_free(bytes);
//    stbi_image_free(bits);
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

    jpegCompress("../projects/jpeg/test.jpg", TEX);




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

