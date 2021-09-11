#version 330 core
in vec2 Position;
in vec2 Complex;
in vec3 Color;
in vec2 z0;


out vec4 FragColor;


uniform int ITERS;
uniform int SET; //0 -- mandelbrot, 1 -- julia

uniform vec2 c;

vec3 coln(int n){
    float colCoord = 1 - float(n) / float(ITERS);
    return vec3(colCoord,colCoord,1);
}


vec2 multiplyComplex(vec2 z1, vec2 z2){
  return vec2(z1.x * z2.x - z1.y * z2.y, z1.x * z2.y + z1.y * z2.x);
}

vec3 mandel(vec2 z){
    vec2 m = vec2(0,0);


    for(int i  = 0; i < ITERS; i++){
        m = multiplyComplex(m,m) + z;
        float modulusSq = m.x * m.x + m.y * m.y;
        if(modulusSq > 4){
            return coln(i);
        }
    }

    return vec3(0.0, 0.0, 0.0);

}


vec3 julia(vec2 z){
    vec2 m = z;


    for(int i  = 0; i < ITERS; i++){
        m = multiplyComplex(m,m) + c;
        float modulusSq = m.x * m.x + m.y * m.y;
        if(modulusSq >= 4){
            return coln(i);
        }
    }

    return vec3(0.0, 0.0, 0.0);

}



void main() {
//    vec3 cv = mandel(Complex);
    vec3 cv = vec3(0.0,0.0,0.0);
    if(SET == 0){
        cv = mandel(Complex);
    } else if(SET == 1){
        cv = julia(Complex);
    }


//    FragColor = (mandel(Complex),1.0);
//    FragColor = (ITERS,ITERS,ITERS,1.0);
    FragColor = vec4(cv.x, cv.y, cv.z, 1.0);
}
