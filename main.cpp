
#include <glad/glad.h>
#include <GLFW/glfw3.h>
#include <iostream>
#include <valarray>
#include <glm/gtc/matrix_transform.hpp>
#include <glm/glm.hpp>
#include <glm/gtc/type_ptr.hpp>
#include <complex>
#include <fstream>


const int width = 1920;
const int height = 1080;
const int ITERS = 50;

std::complex<float> Z_0 = {-0.551042,0.616667};
float UNIT_RE = 0.25f;
float UNIT_IM = 0.25f;



GLuint VAO;


void rebindData(std::vector<GLfloat> points){
    unsigned int VBO;
    glGenVertexArrays(1, &VAO);
    glGenBuffers(1, &VBO);


    glBindVertexArray(VAO);
    glBindBuffer(GL_ARRAY_BUFFER, VBO);

    glBufferData(GL_ARRAY_BUFFER,points.size() * sizeof(GLfloat), points.data(), GL_STATIC_DRAW);

    glVertexAttribPointer(0,2, GL_FLOAT, GL_FALSE, 5* sizeof(GLfloat), (void*)nullptr);
    glVertexAttribPointer(1,3,GL_FLOAT,GL_FALSE, 5 * sizeof(GLfloat), (void*)(2 * sizeof(float)));

    glEnableVertexAttribArray(0);
    glEnableVertexAttribArray(1);
    glBindVertexArray(0);
    glBindBuffer(GL_ARRAY_BUFFER,0);
}



std::complex<float> pixIntoComplex(glm::vec2 pixel,std::complex<float> z0, float unitRe, float unitIm){
    return z0 + std::complex((float) pixel.x * unitRe/ width, (float) -(pixel.y * unitIm/height));
}



glm::vec3 mandelbrot(std::complex<float> z){
    std::complex<float> m = 0;


    int blewIters = 0;


    for(int i = 0; i < ITERS; i++){
        m = m * m + z;

        float modulusSq = m.real()* m.real() + m.imag() * m.imag();
        if(modulusSq >= 4){
            blewIters = i;
            break;
        }
    }
    float modulusSq = m.real()* m.real() + m.imag() * m.imag();

    if(modulusSq < 4)
        return {0.0,0.0,0.0};
    return {1 - (float)blewIters/ITERS,   1 - (float)blewIters/ITERS, 1 - (float)blewIters/ITERS} ;


}



std::vector<float> mapComplexPlane(std::complex<float> z0, float unitRe, float unitIm){
    std::vector<GLfloat> points;

    for(int x = 0; x <= width; x++){
        for(int y = 0; y <= height; y++){

            std::cout << "PROGRESS: "<< (float)x/width<<std::endl;

//            float r = (float )x /(width/3) - 2; //0 : width ---> -2 : 1
//            float i = (float) y /(height/2) - 1; //0 : height ---> -1 : 1


            points.push_back((float )x /(width/2) - 1); // 0: 1920 --> -1 : 1
            points.push_back(-((float )y /(height/2) - 1)); //0:1080 --> -1 : 1
//            std::complex<float> c(r,i);
            std::complex<float> c = pixIntoComplex({x,y}, z0, unitRe, unitIm);
            glm::vec3 col = mandelbrot(c);
            points.push_back(col.x);
            points.push_back(col.y);
            points.push_back(col.z);
        }
    }

    return points;
}

void getShaderErrors(GLuint shader, std::string type){

    GLint hasCompiled;
    char infoLog[1024];
    glGetShaderInfoLog(shader, 1024, nullptr, infoLog);
    glGetShaderiv(shader,GL_COMPILE_STATUS, &hasCompiled);
    std::cout << infoLog << std::endl;
    if(hasCompiled){
        return;
    }

    if(type == "PROGRAM"){
            std::cout << "SHADER_LINKING_ERROR::" << type << "\n" << std::endl;

    } else if (type == "VERTEX" || type == "FRAGMENT"){
        std::cout << "SHADER_COMPILATION_ERROR::" << type << "\n" << std::endl;
    }
}

void getEvents(GLFWwindow* window){
    double xPos, yPos;
    glfwGetCursorPos(window, &xPos, &yPos);
    if(glfwGetMouseButton(window,GLFW_MOUSE_BUTTON_LEFT) == GLFW_PRESS){
        std::cout << pixIntoComplex({xPos,yPos}, Z_0, UNIT_RE, UNIT_IM) << std::endl;
    }
}

std::string get_file_contents(const char* filename) {
    std::ifstream in(filename, std::ios::binary);
    if (in)
    {
        std::string contents;
        in.seekg(0, std::ios::end);
        contents.resize(in.tellg());
        in.seekg(0, std::ios::beg);
        in.read(&contents[0], contents.size());
        in.close();
        return(contents);
    }
    throw(errno);

}


int main() {


    std::vector<GLfloat> points;
    auto vz = pixIntoComplex({960,540},{-1.5,1},2.0f,2.0f);


    points = mapComplexPlane(Z_0,UNIT_RE,UNIT_IM);
    //INIT
    glfwInit();
    glfwWindowHint(GLFW_CONTEXT_VERSION_MAJOR, 3);
    glfwWindowHint(GLFW_CONTEXT_VERSION_MINOR,3);
    glfwWindowHint(GLFW_OPENGL_PROFILE, GLFW_OPENGL_CORE_PROFILE);

    auto window = glfwCreateWindow(width,height, "Fluid", nullptr, nullptr);
    glfwMakeContextCurrent(window);
    gladLoadGL();
    //END INIT
    //GL SETTINGS
    glViewport(0,0,width,height);
    glPolygonMode(GL_FRONT_AND_BACK, GL_FILL);
//    glEnable(GL_DEPTH_TEST);
    //END GL SETTINGS

    //SHADER
//    Shader sh("../src/shader/shaders/default/not_textured/vs.glsl", "../src/shader/shaders/default/not_textured/fs.glsl");

    GLuint vertexShader, fragmentShader, shaderProgram;
    std::string vertexSource = get_file_contents("../vs.glsl");
    std::string fragmentSource = get_file_contents("../fs.glsl");
    const char* vs = vertexSource.c_str();
    const char* fs = fragmentSource.c_str();

    vertexShader = glCreateShader(GL_VERTEX_SHADER);
    glShaderSource(vertexShader, 1, &vs, nullptr);
    glCompileShader(vertexShader);
    getShaderErrors(vertexShader, "VERTEX");

    fragmentShader = glCreateShader(GL_FRAGMENT_SHADER);
    glShaderSource(fragmentShader, 1, &fs, nullptr);
    glCompileShader(fragmentShader);
    getShaderErrors(fragmentShader, "FRAGMENT");
    shaderProgram = glCreateProgram();
    glAttachShader(shaderProgram, vertexShader);
    glAttachShader(shaderProgram, fragmentShader);
    glLinkProgram(shaderProgram);
    getShaderErrors(shaderProgram, "PROGRAM");

    glDeleteShader(vertexShader);
    glDeleteShader(fragmentShader);
    //END SHADER
    // DATA



    // END DATA
//    glUseProgram(shaderProgram);
    rebindData(points);
    while(!glfwWindowShouldClose(window)){
//        for(int i = 0; i < points.size(); i += 5){
//            points[i] += 0.005*(rand()%10 - 5) / 5;
//            points[i + 1] += 0.005 * (rand()%10 - 5) / 5;
//
//
//        }

        getEvents(window);
//        rebindData(points);
        glClearColor(1.0f, 1.0f, 1.0f, 1.0f);
        glClear(GL_COLOR_BUFFER_BIT);

//        sh.Activate();




        glUseProgram(shaderProgram);
        auto projection = glm::mat4(1.0f);
//        projection = glm::perspective(glm::radians(90.f), (float)width / height, 0.01f, 100.f);
        projection = glm::mat4(1.0f);
        glUniformMatrix4fv(glGetUniformLocation(shaderProgram, "cMatrix"),1,GL_FALSE, glm::value_ptr(projection));

        glBindVertexArray(VAO);
        glPointSize(2.0);
        glDrawArrays(GL_POINTS, 0 , points.size());
        glfwSwapBuffers(window);
        glfwPollEvents();

    }
    return 0;
}
