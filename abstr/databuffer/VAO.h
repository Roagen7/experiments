//
// Created by roagen on 14.09.2021.
//

#ifndef UNTITLED5_VAO_H
#define UNTITLED5_VAO_H


#include <glad/glad.h>
#include <vector>

class VAO {
private:

    int loc = 0;
    GLsizei offset = 0;
    GLsizei stride = 0;

public:
    GLuint ID;

    VAO();
    void Reserve(GLsizei s);
    void Bind();
    void Unbind();
    void Delete();

    template <typename T>
    void Add(int n);

//    template<>
//    void Add<GLfloat>(int n);

};


#endif //UNTITLED5_VAO_H
