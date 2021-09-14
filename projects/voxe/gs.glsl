#version 330 core
layout (triangles) in;


in mat4 cMat[];
//in vec3 vx;
out vec3 norm;

layout(triangle_strip, max_vertices = 3) out;

uniform mat4 camMatrix;

bool in_frustum(mat4 M, vec3 p) {
    vec4 Pclip = M * vec4(p, 1.0);

//    return Pclip.w >= 0;
    return true;
//    return
//    abs(p.x) <= Pclip.w ;
//    abs(p.y) <= Pclip.w &&
//    p.z >= 0 &&
//    p.z <= Pclip.w;
//    abs(p.z) <= Pclip.w;

}


vec3 calculateNormal(){
    vec3 x0 = vec3(gl_in[0].gl_Position.x,gl_in[0].gl_Position.y, gl_in[0].gl_Position.z) / gl_in[0].gl_Position.w;
    vec3 x1 = vec3(gl_in[1].gl_Position.x,gl_in[1].gl_Position.y, gl_in[1].gl_Position.z)/ gl_in[1].gl_Position.w;
    vec3 x2 = vec3(gl_in[2].gl_Position.x,gl_in[2].gl_Position.y, gl_in[2].gl_Position.z)/ gl_in[2].gl_Position.w;

    return cross(x1 - x0, x2 - x0);
}



void main() {
    vec3 x0 = vec3(gl_in[0].gl_Position);
    vec3 x1 = vec3(gl_in[1].gl_Position);
    vec3 x2 = vec3(gl_in[2].gl_Position);

    if(in_frustum(cMat[0],x0) && in_frustum(cMat[1],x1) && in_frustum(cMat[2],x2)){
        gl_Position = gl_in[0].gl_Position;
        EmitVertex();
        gl_Position = gl_in[1].gl_Position;
        EmitVertex();
        gl_Position = gl_in[2].gl_Position;
        EmitVertex();
        EndPrimitive();

    }
//    gl_in[0].cMat;

    norm = calculateNormal();
}
