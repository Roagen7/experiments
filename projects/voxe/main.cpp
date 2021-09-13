//
// Created by roagen on 13.09.2021.
//

#include "main.h"
#include "voxel.h"

const int width = 1920;
const int height = 1080;




void voxe::gl_main() {

    GLFWwindow* window;
    createWindow(window,width, height);
    glEnable(GL_DEPTH_TEST);

    GLuint shaderProgram;
    createShader("../projects/voxe/vs.glsl","../projects/voxe/fs.glsl", shaderProgram);

    camera::init(width,height,{0.0,0.0,0.0},{0.0,0.0,-1.0});



    std::vector<voxel> voxels;


    for(int x = 0; x < 20; x++){
        for(int y = 0; y < 10; y++){
            voxels.push_back(voxel({x - 4,(float) rand()/ RAND_MAX,y+2}, {(float) rand()/RAND_MAX,(float) rand()/RAND_MAX,(float) rand()/RAND_MAX}));
        }
    }


    auto vox1 = voxel({0.0,0.0,0.0},{1.0,0.0,0.0});
    auto vox2 = voxel(vox1.locate(SOUTH),{0.0,0.0,1.0});
    auto vox3 = voxel(vox2.locate(UP),{0.0,1.0,0.0});

    while(!glfwWindowShouldClose(window)){



        glfwPollEvents();
        camera::input(window);

        glClearColor(0.0f, 0.0f, 0.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//        vox1.draw(shaderProgram,camera::view());
//        vox2.draw(shaderProgram,camera::view());
//        vox3.draw(shaderProgram,camera::view());
        for(auto& vox : voxels){
            vox.draw(shaderProgram, camera::view());
        }

        glfwSwapBuffers(window);
    }


    glDeleteShader(shaderProgram);
    glfwDestroyWindow(window);
    glfwTerminate();

}

