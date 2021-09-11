#version 330 core
in vec2 Position;
in vec2 Complex;
in vec3 Color;
in vec2 z0;


out vec4 FragColor;


uniform int ITERS;


vec2 multiplyComplex(vec2 z1, vec2 z2){
  return vec2(z1.x * z2.x - z1.y * z2.y, z1.x * z2.y + z1.y * z2.x);
}

vec3 mandel(vec2 z){
    vec2 m = vec2(0,0);
    int blewIters = 0;

    for(int i  = 0; i < ITERS; i++){
        m = multiplyComplex(m,m) + z;
        float modulusSq = m.x * m.x + m.y * m.y;
        if(modulusSq >= 4){
            blewIters = i;
            break;
        }
    }
    float modulusSq = m.x * m.x + m.y * m.y;
    if(modulusSq < 4){
        return vec3(0.0, 0.0, 0.0);
    }
    float col = 1 - float(blewIters) / float(ITERS);
//    float col = 1;
    return vec3(col,col,col);
}



void main() {
    vec3 cv = mandel(Complex);
//    FragColor = (mandel(Complex),1.0);
//    FragColor = (ITERS,ITERS,ITERS,1.0);
    FragColor = vec4(cv.x, cv.y, cv.z, 1.0);
}
