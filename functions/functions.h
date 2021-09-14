//
// Created by roagen on 11.09.2021.
//

#ifndef UNTITLED5_FUNCTIONS_H
#define UNTITLED5_FUNCTIONS_H

#include <vector>
#include <glad/glad.h>
#include <string>
#include <GLFW/glfw3.h>


void createWindow(GLFWwindow* &window, int width, int height);

void getShaderErrors(GLuint shader, std::string type);


void createShader(std::string vertexFile, std::string fragmentFile, GLuint& shaderProgram, bool hasGeometryShader = false, std::string geometryFile = "");
void bindData(std::vector<GLfloat> points, GLuint& VAO);
void bindDataVec3(std::vector<GLfloat> points, GLuint& VAO, bool hasNormals = true);

std::string get_file_contents(const char* filename);

#endif //UNTITLED5_FUNCTIONS_H
