//
// Created by roagen on 14.09.2021.
//

#include <stdexcept>
#include "VAO.h"

VAO::VAO() {
    glGenVertexArrays(1, &this->ID);
}

void VAO::Reserve(GLsizei s) {
    this->stride = s;
}

template<typename T>
void VAO::Add(int n) {
    throw std::runtime_error("[VAO::Add] invalid type");
}

void VAO::Bind() {
    glBindVertexArray(ID);
}

void VAO::Unbind() {
    glBindVertexArray(0);
}

void VAO::Delete() {
    glDeleteVertexArrays(1,&this->ID);
}

template<>
void VAO::Add<GLfloat>(int n){
    glVertexAttribPointer(this->loc,n, GL_FLOAT, GL_FALSE,this->stride, (void *) this->offset);
    glEnableVertexAttribArray(this->loc);
    this->loc++;
    this->offset += n * sizeof(GLfloat);
}
