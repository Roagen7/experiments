//
// Created by roagen on 23.09.2021.
//

#include "main.h"
#include "../voxe/voxel.h"


const int width = 1920;
const int height = 1080;


glm::vec3 cubeCol[6][3][3];

void initCube(){
    glm::vec3 colors[] = {{1,0,0}, {0,1,0}, {0,0,1}, {1,1,0}, {1,1,1}, {1,0,1}};

    for(int face = 0; face < 6; face++){
        for(int x = 0; x < 3; x++){
            for(int y = 0; y < 3; y++){
                cubeCol[face][x][y] = colors[face];
            }
        }
    }

}




void createCube(std::vector<voxel>& voxels, float cubeSide){
    voxels.clear();
    float space = cubeSide / 90.0;
    float smallSideLength = cubeSide/3.0 - 2 * space;
    float indent = 0.05;

    voxels.emplace_back(glm::vec3({0,0,0}),glm::vec3({0,0,0}), cubeSide);

    //RED

    voxels.emplace_back(glm::vec3(-indent,space,space), cubeCol[0][0][0],smallSideLength);
    voxels.emplace_back(glm::vec3(-indent,cubeSide/3.0 +space ,space), cubeCol[0][0][1],smallSideLength);
    voxels.emplace_back(glm::vec3(-indent,2* cubeSide/3.0 + space,space), cubeCol[0][0][2],smallSideLength);

    voxels.emplace_back(glm::vec3(-indent,space, cubeSide/3.0 + space), cubeCol[0][1][0],smallSideLength);
    voxels.emplace_back(glm::vec3(-indent, cubeSide/3.0 + space,cubeSide/3.0 + space), cubeCol[0][1][1],smallSideLength);
    voxels.emplace_back(glm::vec3(-indent,2* cubeSide/3.0 + space,cubeSide/3.0 + space), cubeCol[0][1][2],smallSideLength);

    voxels.emplace_back(glm::vec3(-indent,space, 2 * cubeSide/3.0 + space), cubeCol[0][2][0],smallSideLength);
    voxels.emplace_back(glm::vec3(-indent, cubeSide/3.0 + space,2 * cubeSide/3.0 + space),cubeCol[0][2][1],smallSideLength);
    voxels.emplace_back(glm::vec3(-indent,2* cubeSide/3.0 + space,2 * cubeSide/3.0 + space), cubeCol[0][2][2],smallSideLength);

    //BLUE

    voxels.emplace_back(glm::vec3(indent + 2 * space+ 2 * cubeSide / 3.0,space,space), cubeCol[2][0][0],smallSideLength);
    voxels.emplace_back(glm::vec3( indent + 2 * space + 2 * cubeSide / 3.0,cubeSide/3.0 +space ,space), cubeCol[2][0][1],smallSideLength);
    voxels.emplace_back(glm::vec3( indent + 2 * space+ 2 * cubeSide / 3.0,2* cubeSide/3.0 + space,space), cubeCol[2][0][2],smallSideLength);

    voxels.emplace_back(glm::vec3( indent +2 * space+ 2 * cubeSide / 3.0,space, cubeSide/3.0 + space), cubeCol[2][1][0],smallSideLength);
    voxels.emplace_back(glm::vec3( indent + 2 * space+2 * cubeSide / 3.0, cubeSide/3.0 + space,cubeSide/3.0 + space), cubeCol[2][1][1],smallSideLength);
    voxels.emplace_back(glm::vec3(indent + 2 * space+2 * cubeSide / 3.0,2* cubeSide/3.0 + space,cubeSide/3.0 + space), cubeCol[2][1][2],smallSideLength);

    voxels.emplace_back(glm::vec3( indent +2 * space+ 2 * cubeSide / 3.0,space, 2 * cubeSide/3.0 + space), cubeCol[2][2][0],smallSideLength);
    voxels.emplace_back(glm::vec3( indent + 2 * space+2 * cubeSide / 3.0, cubeSide/3.0 + space,2 * cubeSide/3.0 + space),cubeCol[2][2][1],smallSideLength);
    voxels.emplace_back(glm::vec3( indent +2 * space+ 2 * cubeSide / 3.0,2* cubeSide/3.0 + space,2 * cubeSide/3.0 + space), cubeCol[2][2][2],smallSideLength);

    //YELLOW

//    voxels.emplace_back(glm::vec3(space,space,-0.5), cubeCol[3][2][2],smallSideLength);
    voxels.emplace_back(glm::vec3(space,space,-indent), cubeCol[3][0][0],smallSideLength);
    voxels.emplace_back(glm::vec3(space,cubeSide/3.0 +space ,-indent), cubeCol[3][0][1],smallSideLength);
    voxels.emplace_back(glm::vec3(space,2* cubeSide/3.0 + space,-indent), cubeCol[3][0][2],smallSideLength);
//
    voxels.emplace_back(glm::vec3(cubeSide/3.0 + space,space, -indent ), cubeCol[3][1][0],smallSideLength);
    voxels.emplace_back(glm::vec3(cubeSide/3.0 + space, cubeSide/3.0 + space,-indent), cubeCol[3][1][1],smallSideLength);
    voxels.emplace_back(glm::vec3(cubeSide / 3.0 + space,2* cubeSide/3.0 + space,-indent), cubeCol[3][1][2],smallSideLength);

    voxels.emplace_back(glm::vec3(2 * cubeSide / 3.0 + space,space, -indent), cubeCol[2][2][0],smallSideLength);
    voxels.emplace_back(glm::vec3( 2 * cubeSide / 3.0 + space, cubeSide/3.0 + space,-indent),cubeCol[2][2][1],smallSideLength);
    voxels.emplace_back(glm::vec3( 2 * cubeSide / 3.0 + space,2* cubeSide/3.0 + space,-indent), cubeCol[2][2][2],smallSideLength);



}

void rubiks::gl_main() {




    GLFWwindow* window;
    createWindow(window,width, height);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_DEPTH_CLAMP);
//    glEnable(GL_CULL_FACE_MODE);
//    glCullFace(GL_FRONT_AND_BACK);
//    glFrontFace(GL_CW);



    GLuint shaderProgram;
//    createShader("../projects/voxe/vs.glsl","../projects/voxe/fs.glsl", shaderProgram, true, "../projects/voxe/gs.glsl");
    createShader("../projects/voxe/vs.glsl","../projects/voxe/fs.glsl", shaderProgram);
    camera::init(width,height,{0.0,0.0,0.0},{0.0,0.0,-1.0});
    voxel vox({0,0,0},{0,0,0},0.0);


    std::vector<voxel> voxels;
    //glm::vec3 pos, glm::vec3 color, float sideLength = 1)
    initCube();
    createCube(voxels,9.0f);





    while(!glfwWindowShouldClose(window)){

        glfwPollEvents();
        camera::input(window);

        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
//        glClearColor(0.0,0.0,0.0,1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(shaderProgram);
        vox.draw(camera::view(), true, shaderProgram);

        createCube(voxels, 9.0f);

        for(auto& vox : voxels){
            vox.draw(camera::view(), true, shaderProgram);
        }

        glfwSwapBuffers(window);
    }


    glDeleteShader(shaderProgram);
    glfwDestroyWindow(window);
    glfwTerminate();

}