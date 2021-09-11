//
// Created by roagen on 11.09.2021.
//

#include <iostream>
#include <fstream>
#include "functions.h"

void createWindow(GLFWwindow* &window, int width, int height){
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);
    window = glfwCreateWindow(width,height, "Fluid", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    gladLoadGL();
    glViewport(0,0,width,height);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
}


void bindData(std::vector<GLfloat> points, GLuint &VAO){
    unsigned int VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);


    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER,points.size() * sizeof(GLfloat), points.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0,2, GL_FLOAT, GL_FALSE, 5* sizeof(GLfloat), (void*)nullptr);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE, 5 * sizeof(GLfloat), (void*)(2 * sizeof(float)));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER,0);
}


std::string get_file_contents(const char* filename) {
    std::ifstream in(filename, std::ios::binary);
    if (in)
    {
        std::string contents;
        in.seekg(0, std::ios::end);
        contents.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&contents[0], contents.size());
        in.close();
        return(contents);
    }
    throw(errno);
}
void getShaderErrors(GLuint shader, std::string type){

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

    } else if (type == "VERTEX" || type == "FRAGMENT"){
        std::cout << "SHADER_COMPILATION_ERROR::" << type << "\n" << std::endl;
    }
}



void createShader(std::string vertexFile, std::string fragmentFile, GLuint& shaderProgram){
    GLuint vertexShader, fragmentShader;
    std::string vertexSource = get_file_contents(vertexFile.c_str());
    std::string fragmentSource = get_file_contents(fragmentFile.c_str());
    const char* vs = vertexSource.c_str();
    const char* fs = fragmentSource.c_str();

    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vs, nullptr);
    glCompileShader(vertexShader);
    getShaderErrors(vertexShader, "VERTEX");

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fs, nullptr);
    glCompileShader(fragmentShader);
    getShaderErrors(fragmentShader, "FRAGMENT");
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    getShaderErrors(shaderProgram, "PROGRAM");

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);


}
