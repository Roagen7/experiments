//
// Created by roagen on 13.09.2021.
//

#include "main.h"
#include "voxel.h"
#include "noise.h"

const int width = 1920;
const int height = 1080;


const int AREA = 20;
unsigned SEED_A = rand();
unsigned SEED_B = rand();
unsigned SEED_C = rand();

// x in [0,1)

void generateTerrain(std::vector<voxel>& voxels){
    const int W = 150;
    const int H = 100;
    voxels.reserve(W * H);

    for(int x = 0; x < W; x++){
        for(int y = 0; y < H; y++){
            float noise = perlin(x,y,AREA,SEED_A,SEED_B,SEED_C);

            glm::vec3 colv = {0.0,0.0,0.0};
            int hei = (int) (noise >= 0.3 ? noise * 10 : 3);
            if(hei == 3){
                colv = {0.0,0.0,1.0};
            }
            if(hei == 4){
                colv = {1.0,1.0,0.0};
            }
            if(hei >4 && hei <= 10){
//                colv = {0.0,1.0,0.0};
                colv = transitionBetweenCols({0.0,1.0,0.0}, {0.0, 100.0/255.0,0.0}, noise);
            }
//            if(hei >=7 && hei <= 10){
////                colv = {164.0/255.0, 189.0/255.0,186.0/255.0};
//                colv = transitionBetweenCols({0.2,0.2,0.2},{164.0/255.0, 189.0/255.0,186.0/255.0}, noise);
//            }
//            transitionBetweenCols({0.0,0.0,0.0},{164.0/255.0, 189.0/255.0,186.0/255.0}, noise)
            voxels.emplace_back(glm::vec3(x - 10 ,hei - 2,y - 10), colv);
        }
    }

}
void generateMengerSponge(std::vector<voxel> &voxels, int iters = 3, float sideLen = 9.0f,
                          glm::vec3 start0 = {0.0, 0.0, 0.0}) {
//    voxels.emplace_back(glm::vec3(0,0,0), glm::vec3(1.0,1.0,1.0), sideLen);
    // start0
    if(iters == 0){
//        glm::vec3((float) rand()/RAND_MAX,1.0,(float) rand()/RAND_MAX)
//        voxels.emplace_back(start0,start0 / 9.0f , sideLen);
        float noise = perlin3D(start0.x,start0.y,start0.z,AREA);
        voxels.emplace_back(start0,glm::vec3(noise,noise,noise)  , sideLen);
        return;
    }

    generateMengerSponge(voxels, iters - 1, (float) sideLen / 3, start0);
    generateMengerSponge(voxels, iters - 1, sideLen / 3, start0 + glm::vec3(0.0, sideLen / 3, 0.0));
    generateMengerSponge(voxels, iters - 1, sideLen / 3, start0 + glm::vec3(sideLen / 3, 0.0, 0.0));
    generateMengerSponge(voxels, iters - 1, sideLen / 3, start0 + glm::vec3(0.0, 0.0, sideLen / 3));

    generateMengerSponge(voxels, iters - 1, sideLen / 3, start0 + glm::vec3(2 * sideLen / 3, 0, 0));
    generateMengerSponge(voxels, iters - 1, sideLen / 3, start0 + glm::vec3(0.0, 2 * sideLen / 3, 0));
    generateMengerSponge(voxels, iters - 1, sideLen / 3, start0 + glm::vec3(0.0, 0.0, 2 * sideLen / 3));
    generateMengerSponge(voxels, iters - 1, sideLen / 3, start0 + glm::vec3(0.0, 2 * sideLen / 3, 2 * sideLen / 3));
    generateMengerSponge(voxels, iters - 1, sideLen / 3, start0 + glm::vec3(2 * sideLen / 3, sideLen / 3, 0.0));
    generateMengerSponge(voxels, iters - 1, sideLen / 3, start0 + glm::vec3(sideLen / 3, 2 * sideLen / 3, 0.0));
    generateMengerSponge(voxels, iters - 1, sideLen / 3, start0 + glm::vec3(sideLen / 3, 0.0, 2 * sideLen / 3));
    generateMengerSponge(voxels, iters - 1, sideLen / 3, start0 + glm::vec3(0.0, sideLen / 3, 2 * sideLen / 3));

    generateMengerSponge(voxels, iters - 1,
                         sideLen / 3, start0 + glm::vec3(2 * sideLen / 3, 2 * sideLen / 3, 2 * sideLen / 3));
    generateMengerSponge(voxels, iters - 1, sideLen / 3, start0 + glm::vec3(0, 2 * sideLen / 3, 2 * sideLen / 3));
    generateMengerSponge(voxels, iters - 1, sideLen / 3, start0 + glm::vec3(2 * sideLen / 3, 0, 2 * sideLen / 3));
    generateMengerSponge(voxels, iters - 1, sideLen / 3, start0 + glm::vec3(2 * sideLen / 3, 0, 1 * sideLen / 3));
    generateMengerSponge(voxels, iters - 1,
                         sideLen / 3, start0 + glm::vec3(2 * sideLen / 3, sideLen / 3, 2 * sideLen / 3));
    generateMengerSponge(voxels, iters - 1, sideLen / 3, start0 + glm::vec3(2 * sideLen / 3, 2 * sideLen / 3, 0));
    generateMengerSponge(voxels, iters - 1, sideLen / 3, start0 + glm::vec3(0.0, 2 * sideLen / 3, sideLen / 3));
    generateMengerSponge(voxels, iters - 1,
                         sideLen / 3, start0 + glm::vec3(sideLen / 3, 2 * sideLen / 3, 2 * sideLen / 3));
    generateMengerSponge(voxels, iters - 1,
                         sideLen / 3, start0 + glm::vec3(2 * sideLen / 3, 2 * sideLen / 3, sideLen / 3));
}
void generateCaves(std::vector<voxel>& voxels){
    for(int x = 0; x < 25; x++){
        for(int y = 0; y < 25; y++){
            for(int z = 0; z < 25; z++){
                float noise = perlin3D(x,y,z, AREA);
                if(noise > 0.6){
                    voxels.emplace_back(glm::vec3( x,- y, z), glm::vec3(noise, noise, noise));
                }
            }
        }
    }


}

void voxe::gl_main() {
    srand(time(nullptr));
  SEED_A = rand();
  SEED_B = rand();
    SEED_C = rand();


    GLFWwindow* window;
    createWindow(window,width, height);
    glEnable(GL_DEPTH_TEST);
    glEnable(GL_DEPTH_CLAMP);
//    glEnable(GL_CULL_FACE_MODE);
//    glCullFace(GL_FRONT_AND_BACK);
//    glFrontFace(GL_CW);

    for(int i = 0; i < cube.size(); i+=9){
        glm::vec3 v0(cube[i],cube[i+1],cube[i+2]);
        glm::vec3 v1(cube[i+3],cube[i+4],cube[i+5]);
        glm::vec3 v2(cube[i+6],cube[i+7],cube[i+8]);

        auto z1 = v1 - v0;
        auto z2 = v2 - v0;

        auto normal = glm::cross(z2,z1);
        std::cout << normal.x <<"," <<normal.y <<"," << normal.z <<"," <<std::endl;
        }


    GLuint shaderProgram;
//    createShader("../projects/voxe/vs.glsl","../projects/voxe/fs.glsl", shaderProgram, true, "../projects/voxe/gs.glsl");
    createShader("../projects/voxe/vs.glsl","../projects/voxe/fs.glsl", shaderProgram);
    camera::init(width,height,{0.0,0.0,0.0},{0.0,0.0,-1.0});



    std::vector<voxel> voxels;
//    generateCaves(voxels);
//    generateMengerSponge(voxels, 3, 18);
    generateTerrain(voxels);



    while(!glfwWindowShouldClose(window)){

        glfwPollEvents();
        camera::input(window);

        glClearColor(178.0f/255.0f, 1.0f, 1.0f, 1.0f);
//        glClearColor(0.0,0.0,0.0,1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
        glUseProgram(shaderProgram);

        for(auto& vox : voxels){
            vox.draw(camera::view(), true, shaderProgram);
        }

        glfwSwapBuffers(window);
    }


    glDeleteShader(shaderProgram);
    glfwDestroyWindow(window);
    glfwTerminate();

}

