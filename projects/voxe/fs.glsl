#version 330 core

in vec3 norm;


out vec4 FragColor;

uniform vec3 color;




float dirLight(){
    vec3 lightDir = vec3(0.0,1.0, 0.0);
    return max(0.1,dot(lightDir, normalize(norm)));
}


void main() {
    FragColor = vec4(color,1.0);
//    FragColor = vec4(1.0,1.0,1.0,1.0);
}
