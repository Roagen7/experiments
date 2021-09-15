//
// Created by roagen on 14.09.2021.
//

#ifndef UNTITLED5_VBO_H
#define UNTITLED5_VBO_H

#include <glad/glad.h>
#include <vector>

class VBO {
private:
    GLuint ID;
public:
    VBO();

    void Bind();
    void Unbind();
    template <typename T>
    void Data(std::vector<T> data,  GLenum draw = GL_STATIC_DRAW);

};


#endif //UNTITLED5_VBO_H
