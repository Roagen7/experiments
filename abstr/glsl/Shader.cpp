//
// Created by roagen on 14.09.2021.
//

#include <glm/gtc/type_ptr.hpp>
#include "Shader.h"
#include "../../functions/functions.h"

Shader::Shader(std::string vertexFile, std::string fragmentFile) {
    GLuint vertexShader, fragmentShader;
    std::string vertexSource = get_file_contents(vertexFile.c_str());
    std::string fragmentSource = get_file_contents(fragmentFile.c_str());
    const char* vs = vertexSource.c_str();
    const char* fs = fragmentSource.c_str();

    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vs, nullptr);
    glCompileShader(vertexShader);
    getErrors(vertexShader, "VERTEX");

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fs, nullptr);
    glCompileShader(fragmentShader);
    getErrors(fragmentShader, "FRAGMENT");
    this->ID = glCreateProgram();
    glAttachShader(this->ID, vertexShader);
    glAttachShader(this->ID, fragmentShader);
    glLinkProgram(this->ID);
    getErrors(this->ID, "PROGRAM");

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::getErrors(GLuint shader, std::string type){

    GLint hasCompiled;
    char infoLog[1024];
    glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
    glGetShaderiv(shader,GL_COMPILE_STATUS, &hasCompiled);
    std::cout << infoLog << std::endl;
    if(hasCompiled){
        return;
    }

    if(type == "PROGRAM"){
        std::cout << "SHADER_LINKING_ERROR::" << type << "\n" << std::endl;

    } else if (type == "VERTEX" || type == "FRAGMENT" || type == "GEOMETRY"){
        std::cout << "SHADER_COMPILATION_ERROR::" << type << "\n" << std::endl;
    }
}

Shader::Shader(std::string vertexFile, std::string fragmentFile, std::string geometryFile) {
    GLuint vertexShader,geometryShader, fragmentShader;
    std::string vertexSource = get_file_contents(vertexFile.c_str());
    std::string geometrySource = get_file_contents(geometryFile.c_str());
    std::string fragmentSource = get_file_contents(fragmentFile.c_str());

    const char* vs = vertexSource.c_str();
    const char* gs = geometrySource.c_str();
    const char* fs = fragmentSource.c_str();

    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vs, nullptr);
    glCompileShader(vertexShader);
    getShaderErrors(vertexShader, "VERTEX");

    geometryShader = glCreateShader(GL_GEOMETRY_SHADER);
    glShaderSource(geometryShader, 1, &gs, nullptr);
    glCompileShader(geometryShader);
    getShaderErrors(geometryShader, "GEOMETRY");

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fs, nullptr);
    glCompileShader(fragmentShader);
    getShaderErrors(fragmentShader, "FRAGMENT");


    this->ID = glCreateProgram();
    glAttachShader(this->ID, vertexShader);
    glAttachShader(this->ID, geometryShader);
    glAttachShader(this->ID, fragmentShader);




    glLinkProgram(this->ID);
    getShaderErrors(this->ID, "PROGRAM");

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
}

void Shader::Use() {
    glUseProgram(this->ID);
}

void Shader::Unif(const std::string& unifname,glm::mat4 mat) {
    this->Use();
    glUniformMatrix4fv(glGetUniformLocation(this->ID,unifname.c_str()), 1, GL_FALSE, glm::value_ptr( mat));
}

void Shader::Unif(const std::string& unifname, glm::vec3 vec) {
    this->Use();
    glUniform3f(glGetUniformLocation(this->ID,unifname.c_str()), vec.x, vec.y, vec.z);
}

void Shader::Unif(const std::string& unifname, float val) {
    this->Use();
    glUniform1f(glGetUniformLocation(this->ID,unifname.c_str()), val);
}

void Shader::Delete() {
    glDeleteProgram(this->ID);
}

void Shader::Unif(const std::string &unifname, std::vector<glm::vec3> vec3arr) {
    this->Use();
    glUniform3fv(glGetUniformLocation(this->ID,unifname.c_str()), vec3arr.size(), (const GLfloat*) vec3arr.data());
}

void Shader::Unif(const std::string &unifname, std::vector<float> floatarr) {
    this->Use();
    glUniform1fv(glGetUniformLocation(this->ID,unifname.c_str()), floatarr.size(), floatarr.data());
}



