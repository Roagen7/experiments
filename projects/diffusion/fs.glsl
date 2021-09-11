#version 330 core
in vec2 Position;
in vec3 Color;

out vec4 FragColor;





void main() {
//    vec3 cv = mandel(Complex);
    vec3 cv = vec3(0.0,0.0,0.0);



//    FragColor = (mandel(Complex),1.0);
//    FragColor = (ITERS,ITERS,ITERS,1.0);
    FragColor = vec4(cv.x, cv.y, cv.z, 1.0);
//    FragColor =

}
