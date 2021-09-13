//
// Created by roagen on 13.09.2021.
//

#include "main.h"
#include "voxel.h"

const int width = 1920;
const int height = 1080;


const int AREA = 16;
unsigned SEED_A = rand();
unsigned SEED_B = rand();
unsigned SEED_C = rand();

// x in [0,1)
glm::vec3 transitionBetweenCols(glm::vec3 col1, glm::vec3 col2,float x){
    glm::vec3 m;
    m.r = (col2.r - col1.r );
    m.g = col2.g - col1.g;
    m.b = col2.b - col1.b;

    return {
        m.r * x + col1.r,
        m.g * x + col1.g,
        m.b * x + col1.b
    };

}


float interpolate(float a0, float a1, float w){
    return (a1 - a0) * ((w * (w * 6.0 - 15.0) + 10.0) * w * w * w) + a0;
};

glm::vec2 randomGradient(int ix, int iy) {
    // No precomputed gradients mean this works for any number of grid coordinates
    const unsigned w = 8 * sizeof(unsigned);
    const unsigned s = w / 2; // rotation width
    unsigned a = ix, b = iy;
    a *= SEED_A; b ^= a << s | a >> w-s;
    b *= SEED_B; a ^= b << s | b >> w-s;
    a *= SEED_C;
    float random = a * (3.14159265 / ~(~0u >> 1)); // in [0, 2*Pi]
//    float random = rand()%1000 * 3.14159;
    glm::vec2 v;
    v.x = sin(random); v.y = cos(random);
    return v;
}

float dotGridGradient(int ix, int iy, float x, float y) {
    // Get gradient from integer coordinates
    glm::vec2 gradient = randomGradient(ix, iy);

    // Compute the distance vector
    float dx = x - (float)ix;
    float dy = y - (float)iy;

    // Compute the dot-product
    return (dx*gradient.x + dy*gradient.y);
}

float perlin(float x, float y) {
    // Determine grid cell coordinates
    x = (float) x / AREA;
    y = (float) y / AREA;

    int x0 = (int)x;
    int x1 = x0 + 1;
    int y0 = (int)y;
    int y1 = y0 + 1;

    // Determine interpolation weights
    // Could also use higher order polynomial/s-curve here
    float sx = x - (float)x0;
    float sy = y - (float)y0;

    // Interpolate between grid point gradients
    float n0, n1, ix0, ix1, value;

    n0 = dotGridGradient(x0, y0, x, y);
    n1 = dotGridGradient(x1, y0, x, y);
    ix0 = interpolate(n0, n1, sx);

    n0 = dotGridGradient(x0, y1, x, y);
    n1 = dotGridGradient(x1, y1, x, y);
    ix1 = interpolate(n0, n1, sx);

    value = interpolate(ix0, ix1, sy);
    return (value + 1.0f)/ 2.0f;
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


    for(int x = 0; x < 100; x++){
        for(int y = 0; y < 100; y++){
            float noise = perlin(x,y);

            glm::vec3 colv = {0.0,0.0,0.0};
            int hei = (int) (noise >= 0.3 ? noise * 10 : 3);
            if(hei == 3){
                colv = {0.0,0.0,1.0};
            }
            if(hei == 4){
                colv = {1.0,1.0,0.0};
            }
            if(hei >4 && hei <= 6){
//                colv = {0.0,1.0,0.0};
                colv = transitionBetweenCols({0.0,1.0,0.0}, {0.0, 100.0/255.0,0.0}, noise);
            }
            if(hei >=7 && hei <= 10){
//                colv = {164.0/255.0, 189.0/255.0,186.0/255.0};
                colv = transitionBetweenCols({0.2,0.2,0.2},{164.0/255.0, 189.0/255.0,186.0/255.0}, noise);
            }
//            transitionBetweenCols({0.0,0.0,0.0},{164.0/255.0, 189.0/255.0,186.0/255.0}, noise)
            voxels.push_back(voxel({x ,hei,y}, colv));
        }
    }


    auto vox1 = voxel({0.0,0.0,0.0},{1.0,0.0,0.0});
    auto vox2 = voxel(vox1.locate(SOUTH),{0.0,0.0,1.0});
    auto vox3 = voxel(vox2.locate(UP),{0.0,1.0,0.0});

    while(!glfwWindowShouldClose(window)){



        glfwPollEvents();
        camera::input(window);

        glClearColor(178.0f/255.0f, 1.0f, 1.0f, 1.0f);
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

