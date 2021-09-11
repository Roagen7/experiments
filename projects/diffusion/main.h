//
// Created by roagen on 11.09.2021.
//

#ifndef UNTITLED5_DIFFUSION
#define UNTITLED5_DIFFUSION

#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <complex>
#include <iostream>
#include <vector>
#include <glm/vec2.hpp>
#include <complex>

#include "../../functions/functions.h"

namespace diffusion {
    void gl_main();
    void getEvents(GLFWwindow* window);
    std::complex<float> eix(float x);
    std::complex<float> pixToComplex(glm::vec2 pixel,std::complex<float> z0, float unitRe, float unitIm);
};


#endif //UNTITLED5_MAIN_H
