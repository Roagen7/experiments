//
// Created by roagen on 13.09.2021.
//

#include "main.h"
#include "voxel.h"
#include "noise.h"

const int width = 1920;
const int height = 1080;


const int AREA = 16;
unsigned SEED_A = rand();
unsigned SEED_B = rand();
unsigned SEED_C = rand();

// x in [0,1)

void generateTerrain(std::vector<voxel>& voxels){
    const int W = 100;
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
            voxels.emplace_back(glm::vec3(x ,hei,y), colv);
        }
    }

}
void generateMengerSponge(std::vector<voxel>& voxels, glm::vec3 start0 = {0.0,0.0,0.0}, float sideLen = 9.0f,int iters = 3){
//    voxels.emplace_back(glm::vec3(0,0,0), glm::vec3(1.0,1.0,1.0), sideLen);
    // start0
    if(iters == 0){
        voxels.emplace_back(start0, glm::vec3((float) rand()/RAND_MAX,1.0,(float) rand()/RAND_MAX), sideLen);
        return;
    }

    generateMengerSponge(voxels,start0, (float) sideLen/3, iters-1);
    generateMengerSponge(voxels,start0 + glm::vec3(0.0, sideLen/3, 0.0), sideLen/3,iters - 1);
    generateMengerSponge(voxels,start0 + glm::vec3(sideLen/3, 0.0, 0.0), sideLen/3,iters - 1);
    generateMengerSponge(voxels,start0 + glm::vec3(0.0, 0.0, sideLen/3), sideLen/3,iters - 1);

    generateMengerSponge(voxels,start0 + glm::vec3(2 * sideLen/3, 0, 0), sideLen/3,iters - 1);
    generateMengerSponge(voxels,start0 + glm::vec3(0.0, 2 * sideLen/3, 0), sideLen/3,iters - 1);
    generateMengerSponge(voxels,start0 + glm::vec3(0.0,0.0 , 2 * sideLen/3), sideLen/3,iters - 1);
    generateMengerSponge(voxels,start0 + glm::vec3(0.0,2 * sideLen/3 , 2 * sideLen/3), sideLen/3,iters - 1);
    generateMengerSponge(voxels,start0 + glm::vec3(2 * sideLen/3, sideLen/3,0.0 ), sideLen/3,iters - 1);
    generateMengerSponge(voxels,start0 + glm::vec3( sideLen/3, 2 * sideLen/3,0.0 ), sideLen/3,iters - 1);
    generateMengerSponge(voxels,start0 + glm::vec3( sideLen/3, 0.0,2 * sideLen/3 ), sideLen/3,iters - 1);
    generateMengerSponge(voxels,start0 + glm::vec3( 0.0,sideLen/3,2 * sideLen/3 ), sideLen/3,iters - 1);

    generateMengerSponge(voxels,start0 + glm::vec3( 2 * sideLen/3,2 * sideLen/3,2 * sideLen/3 ), sideLen/3,iters - 1);
    generateMengerSponge(voxels,start0 + glm::vec3( 0,2 * sideLen/3,2 * sideLen/3 ), sideLen/3,iters - 1);
    generateMengerSponge(voxels,start0 + glm::vec3( 2 * sideLen/3,0,2 * sideLen/3 ), sideLen/3,iters - 1);
    generateMengerSponge(voxels,start0 + glm::vec3( 2 * sideLen/3,0,1 * sideLen/3 ), sideLen/3,iters - 1);
    generateMengerSponge(voxels,start0 + glm::vec3( 2 * sideLen/3,sideLen/3,2 * sideLen/3 ), sideLen/3,iters - 1);
    generateMengerSponge(voxels,start0 + glm::vec3( 2 * sideLen/3,2 * sideLen/3,0 ), sideLen/3,iters - 1);
    generateMengerSponge(voxels,start0 + glm::vec3( 0.0,2 * sideLen/3,sideLen/3 ), sideLen/3,iters - 1);
    generateMengerSponge(voxels,start0 + glm::vec3( sideLen/3,2 * sideLen/3,2 * sideLen/3 ), sideLen/3,iters - 1);
    generateMengerSponge(voxels,start0 + glm::vec3( 2 * sideLen/3,2 * sideLen/3,sideLen/3 ), sideLen/3,iters - 1);
}


void voxe::gl_main() {
    srand(time(nullptr));
  SEED_A = rand();
  SEED_B = rand();
    SEED_C = rand();


    GLFWwindow* window;
    createWindow(window,width, height);
    glEnable(GL_DEPTH_TEST);

    GLuint shaderProgram;
    createShader("../projects/voxe/vs.glsl","../projects/voxe/fs.glsl", shaderProgram);

    camera::init(width,height,{0.0,0.0,0.0},{0.0,0.0,-1.0});



    std::vector<voxel> voxels;
//    generateTerrain(voxels);
    generateMengerSponge(voxels);


    auto vox1 = voxel({0.0,0.0,0.0},{1.0,0.0,0.0});
//    auto vox2 = voxel(vox1.locate(SOUTH),{0.0,0.0,1.0});
//    auto vox3 = voxel(vox2.locate(UP),{0.0,1.0,0.0});

    while(!glfwWindowShouldClose(window)){

        glfwPollEvents();
        camera::input(window);

//        glClearColor(178.0f/255.0f, 1.0f, 1.0f, 1.0f);
        glClearColor(0.0,0.0,0.0,1.0);
        glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);

//        vox1.draw(shaderProgram,camera::view());
//        vox2.draw(shaderProgram,camera::view());
//        vox3.draw(shaderProgram,camera::view());
//        glPolygonMode(GL_FRONT_AND_BACK, GL_LINE);
        for(auto& vox : voxels){
            vox.draw(shaderProgram, camera::view());
        }
//        glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//        for(auto& vox : voxels){
//            vox.draw(shaderProgram, camera::view());
//        }
        glfwSwapBuffers(window);
    }


    glDeleteShader(shaderProgram);
    glfwDestroyWindow(window);
    glfwTerminate();

}

