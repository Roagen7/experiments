//
// Created by roagen on 13.09.2021.
//

#include "camera.h"

bool firstClick = true;

glm::vec3 camera::pos;
glm::vec3 camera::dir;
float camera::camH;
float camera::camW;
float camera::speed;
float camera::sens;

void camera::init(int w, int h, glm::vec3 p, glm::vec3 d) {
    camW = w;
    camH = h;

    pos = p;
    dir = d;

    speed = 0.5f;
    sens = 100.0f;

}

glm::mat4 camera::view(){
    auto vx = glm::mat4(1.0f);
    auto proj = glm::mat4(1.0f);

    vx = glm::lookAt(camera::pos, camera::pos + camera::dir, camera::UP);
    proj = glm::perspective(glm::radians(90.0f), (float) camera::camW/ camera::camH, 0.1f, 100.0f);

    return proj * vx;
}

void camera::input(GLFWwindow *window) {
    if(glfwGetKey(window, GLFW_KEY_W) == GLFW_PRESS){
        pos += dir * speed;
    }
    if(glfwGetKey(window, GLFW_KEY_S) == GLFW_PRESS){
        pos += -dir * speed;
    }
    if (glfwGetKey(window, GLFW_KEY_A) == GLFW_PRESS){
        pos += speed * -glm::normalize(glm::cross(dir, UP));
    }
    if (glfwGetKey(window, GLFW_KEY_D) == GLFW_PRESS){
        pos += speed * glm::normalize(glm::cross(dir, UP));
    }
    if (glfwGetKey(window, GLFW_KEY_SPACE) == GLFW_PRESS){
        pos += speed * UP;
    }
    if (glfwGetKey(window, GLFW_KEY_LEFT_SHIFT) == GLFW_PRESS){
        pos += speed * -UP;
    }


    if(glfwGetMouseButton(window,GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS){
        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_HIDDEN);
        if(firstClick){
            glfwSetCursorPos(window, camW/2, camH/2);
            firstClick = false;
        }
        double mouseX;
        double mouseY;
        // Fetches the coordinates of the cursor
        glfwGetCursorPos(window, &mouseX, &mouseY);

        float rotX = sens * (float)(mouseY - (camH / 2)) / camH;
        float rotY = sens * (float)(mouseX - (camW / 2)) / camW;

        glm::vec3 newOrientation = glm::rotate(dir, glm::radians(-rotX), glm::normalize(glm::cross(dir, UP)));

        if (abs(glm::angle(newOrientation, UP) - glm::radians(90.0f)) <= glm::radians(85.0f)){
            dir = newOrientation;
        }
        dir = glm::rotate(dir, glm::radians(-rotY), UP);
        glfwSetCursorPos(window,(camW/2), camH/2);

    } else if(glfwGetMouseButton(window, GLFW_MOUSE_BUTTON_LEFT) == GLFW_RELEASE){

        glfwSetInputMode(window, GLFW_CURSOR, GLFW_CURSOR_NORMAL);
        firstClick = true;
    }


}