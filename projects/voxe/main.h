//
// Created by roagen on 13.09.2021.
//

#ifndef UNTITLED5_VOXE
#define UNTITLED5_VOXE

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

#include <vector>
#include <iostream>

#include "../../functions/functions.h"
#include "../../functions/camera.h"

namespace voxe {
    void gl_main();

    void bindDataVec3(std::vector<GLfloat> points, GLuint& VAO);

}



#endif //UNTITLED5_VOXE
