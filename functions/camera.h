//
// Created by roagen on 13.09.2021.
//

#ifndef UNTITLED5_CAMERA_H
#define UNTITLED5_CAMERA_H
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>
#include<glm/gtx/rotate_vector.hpp>
#include<glm/gtx/vector_angle.hpp>
#include <GLFW/glfw3.h>

namespace camera {
    extern glm::vec3 pos;
    extern glm::vec3 dir;
    extern float camW;
    extern float camH;
    extern float speed;
    extern float sens;

    const glm::vec3 UP(0.0f,1.0f,0.0f);



    void init(int w, int h, glm::vec3 p, glm::vec3 d);
    void input(GLFWwindow* window);

    glm::mat4 view(float zFar = 100.0f);

}



#endif //UNTITLED5_CAMERA_H
