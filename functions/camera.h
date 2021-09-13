//
// Created by roagen on 13.09.2021.
//

#ifndef UNTITLED5_CAMERA_H
#define UNTITLED5_CAMERA_H
#include <glm/gtc/matrix_transform.hpp>
#include <glm/gtc/type_ptr.hpp>

namespace camera {
    extern glm::vec3 pos;
    extern glm::vec3 dir;
    const glm::vec3 UP(0.0f,1.0f,0.0f);

    void init(int w, int h, glm::vec3 p, glm::vec3 d);
    glm::mat4 view();

}



#endif //UNTITLED5_CAMERA_H
