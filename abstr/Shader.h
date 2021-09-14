//
// Created by roagen on 14.09.2021.
//

#ifndef UNTITLED5_SHADER_H
#define UNTITLED5_SHADER_H


#include <glad/glad.h>
#include <string>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>

class Shader {
private:
    GLuint ID;
public:
    Shader(std::string vertexFile, std::string fragmentFile);
    Shader(std::string vertexFile, std::string fragmentFile, std::string geometryFile);
    static void getErrors(GLuint shader, std::string type);

    void Use();


    void Unif(std::string unifname,glm::mat4 mat);


};


#endif //UNTITLED5_SHADER_H
