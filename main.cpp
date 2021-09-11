
#include "mandelbrot/main.h"

//
//std::complex<float> pixIntoComplex(glm::vec2 pixel,std::complex<float> z0, float unitRe, float unitIm){
//    return z0 + std::complex((float) pixel.x * unitRe/ width, (float) -(pixel.y * unitIm/height));
//}
//
//
//
//void getEvents(GLFWwindow* window){
//    double xPos, yPos;
//    glfwGetCursorPos(window, &xPos, &yPos);
//    if(glfwGetMouseButton(window,GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS){
//        std::cout << pixIntoComplex({xPos,yPos}, Z_0, UNIT_RE, UNIT_IM) << std::endl;
//    }
//}



int main() {

    mandelbrot::gl_main();

    return 0;
}
