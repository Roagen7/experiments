//
// Created by roagen on 14.09.2021.
//

#include "VBO.h"

VBO::VBO() {
    glGenBuffers(1, &this->ID);
}

template<typename T>
void VBO::Data(std::vector<T> data, GLenum draw) {
    this->Bind();
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(T), data.data(), draw);
}

template<>
void VBO::Data<GLfloat>(std::vector<GLfloat> data, GLenum draw){
    this->Bind();
    glBufferData(GL_ARRAY_BUFFER, data.size() * sizeof(GLfloat), data.data(), draw);
}

// Bind VAO, Data VBO, ...

void VBO::Bind() {
    glBindBuffer(GL_ARRAY_BUFFER, this->ID);
}

void VBO::Unbind() {
    glBindBuffer(GL_ARRAY_BUFFER, 0);
}
