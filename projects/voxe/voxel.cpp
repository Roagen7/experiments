//
// Created by roagen on 13.09.2021.
//

#include "voxel.h"
#include "../../functions/functions.h"

voxel::voxel(glm::vec3 pos, glm::vec3 color, float sideLength) {
    
    bindDataVec3(cube,VAO);
    this->pos = pos;
    this->color = color;
    this->side = sideLength;
}

void voxel::draw(glm::mat4 cameraView, bool externalShader, GLuint shaderProgram) {
    auto mx  = glm::mat4(1.0f);
    mx = glm::translate(mx, voxel::pos);
//        auto proj = glm::perspective(glm::radians(45.0f), (float)width / height, 0.1f, 100.0f);
    mx = glm::scale(mx,{side,side,side});

    if(externalShader){
        glUseProgram(shaderProgram);
    }


    glUniformMatrix4fv(glGetUniformLocation(shaderProgram,"modelMatrix"), 1, GL_FALSE, glm::value_ptr( mx));
    glUniformMatrix4fv(glGetUniformLocation(shaderProgram,"camMatrix"), 1, GL_FALSE, glm::value_ptr(cameraView));
//    glUniformMatrix3fv(glGetUniformLocation(shaderProgram,"color"),color.x, color.y, color.z);

    glUniform3f(glGetUniformLocation(shaderProgram,"color"),color.x, color.y, color.z);
    glBindVertexArray(VAO);
    glDrawArrays(GL_TRIANGLES, 0 , cube.size());


}

glm::vec3 voxel::locate(DIR offset) {
    switch(offset){
        case UP:
            return voxel::pos + glm::vec3(0.0,1.0,0.0);
        case DOWN:
            return voxel::pos + glm::vec3(0.0,-1.0,0.0);
        case SOUTH:
            return voxel::pos + glm::vec3(0.0,0.0,1.0);
        case NORTH:
            return voxel::pos + glm::vec3(0.0,0.0,-1.0);
        case EAST:
            return voxel::pos + glm::vec3(1.0,0.0,0.0);
        case WEST:
            return voxel::pos + glm::vec3(-1.0,0.0,0.0);
    }

    return {0.0,0.0,0.0};
}

voxel::~voxel() {
    glDeleteVertexArrays(1,&VAO);
}

