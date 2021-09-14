//
// Created by roagen on 13.09.2021.
//

#ifndef UNTITLED5_VOXEL_H
#define UNTITLED5_VOXEL_H

#include <glad/glad.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <vector>

const std::vector<GLfloat> cube = {
        0.0f, 0.0f, 0.0f,    0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0f, 0.0f, 0.0f,

        1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 0.0f,    1.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 0.0f, 1.0f,

        1.0f, 0.0f, 1.0f,    1.0f, 1.0f, 1.0f,    0.0f, 1.0f, 1.0f,
        1.0f, 0.0f, 1.0f,    0.0f, 1.0f, 1.0f,    0.0f, 0.0f, 1.0f,

        0.0f, 0.0f, 1.0f,    0.0f, 1.0f, 1.0f,    0.0f, 1.0f, 0.0f,
        0.0f, 0.0f, 1.0f,    0.0f, 1.0f, 0.0f,    0.0f, 0.0f, 0.0f,

        0.0f, 1.0f, 0.0f,    0.0f, 1.0f, 1.0f,    1.0f, 1.0f, 1.0f,
        0.0f, 1.0f, 0.0f,    1.0f, 1.0f, 1.0f,    1.0f, 1.0f, 0.0f,

        1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f,
        1.0f, 0.0f, 1.0f,    0.0f, 0.0f, 0.0f,    1.0f, 0.0f, 0.0f,
};

enum DIR  {
    UP,
    DOWN,
    NORTH,
    SOUTH,
    EAST,
    WEST
};

struct voxel {
    glm::vec3 pos;
    glm::vec3 color;
    glm::mat4 modelMatrix;
    float side;
    GLuint VAO;


    voxel(glm::vec3 pos, glm::vec3 color, float sideLength = 1);
    ~voxel();
    void calcModelMatrix();
    void draw(glm::mat4 cameraView, bool externalShader = false, GLuint shaderProgram = 0);

    glm::vec3 locate(DIR offset);



};



#endif //UNTITLED5_VOXEL_H
