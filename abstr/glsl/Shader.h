//
// Created by roagen on 14.09.2021.
//

#ifndef UNTITLED5_SHADER_H
#define UNTITLED5_SHADER_H


#include <glad/glad.h>
#include <string>
#include <glm/gtc/matrix_transform.hpp>

#include <iostream>
#include <vector>

class Shader {
private:
    GLuint ID;
public:
    Shader(std::string vertexFile, std::string fragmentFile);
    Shader(std::string vertexFile, std::string fragmentFile, std::string geometryFile);
    static void getErrors(GLuint shader, std::string type);

    void Use();
    void Unif(const std::string& unifname,glm::mat4 mat);
    void Unif(const std::string& unifname, glm::vec3 vec);
    void Unif(const std::string& unifname, float val);
    void Unif(const std::string& unifname, int val);
    void Unif(const std::string& unifname, std::vector<glm::vec3> vec3arr);
    void Unif(const std::string& unifname, std::vector<float> floatarr);
    void Delete();
};


#endif //UNTITLED5_SHADER_H
