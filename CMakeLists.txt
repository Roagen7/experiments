cmake_minimum_required(VERSION 3.20)
project(untitled5)

set(CMAKE_CXX_STANDARD 20)
set(CMAKE_CXX_LINK_EXECUTABLE "${CMAKE_CXX_LINK_EXECUTABLE} -ldl")

find_package(glfw3 3.3 REQUIRED)

add_subdirectory(include/glad/)
add_subdirectory(include/glm/)
add_executable(untitled5 main.cpp functions/functions.cpp functions/functions.h projects/mandelbrot/main.cpp projects/mandelbrot/main.h projects/diffusion/main.cpp projects/diffusion/main.h projects/voxe/main.h projects/voxe/main.cpp functions/camera.h functions/camera.cpp projects/voxe/voxel.h projects/voxe/voxel.cpp projects/voxe/noise.cpp projects/voxe/noise.h projects/mandelbulb/main.h projects/mandelbulb/main.cpp abstr/databuffer/VBO.cpp abstr/databuffer/VBO.h abstr/databuffer/VAO.cpp abstr/databuffer/VAO.h abstr/glsl/Shader.cpp abstr/glsl/Shader.h abstr/databuffer/Data.cpp abstr/databuffer/Data.h projects/ray/main.h projects/ray/main.cpp)


target_link_libraries(${PROJECT_NAME} PRIVATE glfw)
target_link_libraries(${PROJECT_NAME} PRIVATE glad)
target_link_libraries(${PROJECT_NAME} PRIVATE glm)