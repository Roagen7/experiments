//
// Created by roagen on 14.09.2021.
//


#include "main.h"
#include "../../abstr/Shader.h"


const int width = 1920;
const int height = 1080;
const int depth = 5;
const int ITERS = 10;

// {x,y,z}^n =




glm::vec3 vecPowN(glm::vec3 v, int N){
    float x = v.x;
    float y = v.y;
    float z = v.z;
    float r = sqrt(x*x + y*y + z * z);
    float r1 = sqrt(x*x + y*y);

    float theta = acos(z/r);
    float phi = atan(y/x);

    return (float) pow(r, N) * glm::vec3(cos(N * phi), sin(N * phi) * cos(N * theta), sin(N * theta));
}
glm::vec3 mandelTriplex(glm::vec3 z ,glm::vec3 c, int N){

    for(int i = 0; i < ITERS; i++){
        z = vecPowN(z,N) + c;

        float modulusSq = z.x * z.x + z.y * z.y + z.z * z.z;
        if(modulusSq > 4){
            return {0.0,0.0,0.0};
        }
    }
    return {1.0,1.0,1.0};
}


void mandelbulb::gl_main() {
    GLFWwindow* window;
    createWindow(window,width,height);
//    glEnable(GL_DEPTH_TEST);
//    GLuint shaderProgram;
//    createShader("../projects/mandelbulb/vs.glsl","../projects/mandelbulb/fs.glsl", shaderProgram);
    Shader shader("../projects/mandelbulb/vs.glsl","../projects/mandelbulb/fs.glsl");

    camera::init(width,height,{0.0,0.0,0.0}, {0.0,0.0,-1.0});
    camera::speed /= 10.0;
//    std::vector<float> points = {0.0, 0.5, 0.0,
//                                 0.1, 0.5, 0.0,
//    };
    std::vector<float> points;
    points.reserve(300 * 300 * depth * 6);
    for(int x = 0 ;x < 300; x++){
        for(int y = 0; y < 300; y++){
            for(int z = 0; z < depth; z++){
                points.emplace_back(x * 0.5);
                points.emplace_back(y * 0.5);
                points.emplace_back(z * 0.5);

//                glm::vec3 col = mandelTriplex({0,0,0}, {x,y,0}, 2);
                glm::vec3 col = {(float) rand() / RAND_MAX, (float) rand() / RAND_MAX, (float) rand() / RAND_MAX};
                points.emplace_back((float) col.x );
                points.emplace_back((float) col.y);
                points.emplace_back((float) col.z );



            }
        }
    }

    // VBO -> binn

    GLuint VAO;



//    bindDataVec3(points, VAO);
    bindClassData(points,VAO);

    while(!glfwWindowShouldClose(window)){

        camera::input(window);

        glfwPollEvents();
        glClearColor(0.0,0.0,0.0,1.0);
        glClear(GL_COLOR_BUFFER_BIT);

        auto model = glm::mat4(1.0f);

        shader.Use();
        shader.Unif("modelMatrix", model);
        shader.Unif("camMatrix", camera::view());
//        glUseProgram(shaderProgram);
//        glUniformMatrix4fv(glGetUniformLocation(shaderProgram,"modelMatrix"), 1, GL_FALSE, glm::value_ptr( model));
//        glUniformMatrix4fv(glGetUniformLocation(shaderProgram,"camMatrix"), 1, GL_FALSE, glm::value_ptr(camera::view()));
//
        glBindVertexArray(VAO);

        glPointSize(10);
        glDrawArrays(GL_POINTS, 0 , (float) points.size()/3.0);

        glfwSwapBuffers(window);

    }


}