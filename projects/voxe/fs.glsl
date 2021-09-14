#version 330 core



in vec3 Norm;


out vec4 FragColor;

uniform vec3 color;




float dirLight(){
    //PHONG DIR LIGHT
    float ambient = 0.1;
    vec3 lightDir = normalize(vec3(1.0f,-1.0f, 0.0f));
    float diffuse = max(0.1,dot(lightDir, normalize(Norm)));

    return diffuse + ambient;
}


void main() {
    FragColor = vec4(color * dirLight(),1.0);
//    FragColor = vec4(1.0,1.0,1.0,1.0);
}
