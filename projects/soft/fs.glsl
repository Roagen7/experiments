#version 330 core
//enum LIGHT TYPE {
#define LIGHT_POINT 0
#define LIGHT_DIRECTIONAL 1
#define LIGHT_CONE 2

// }

#define K_DIFFUSE 0.3
#define K_AMBIENT 0.4
#define K_SPECULAR 0.2

out vec4 FragColor;
in vec3 Col;
in vec3 Norm;

vec3 DIR = vec3(1,0,0);

float PHONG(int LIGHT_TYPE){
    float diffuse = K_DIFFUSE * dot(Norm, DIR);
    float ambient = K_AMBIENT;

    return diffuse + ambient;


}



void main() {
    FragColor = vec4(Col * PHONG(LIGHT_DIRECTIONAL),1.0f);
}
