#version 330 core

#define MAX_OBJNUM 10


#define M_PI 3.1415926538
#define FLT_MAX 3.402823466e+38
#define MAX_DEPTH 2




uniform int OBJNUM;
uniform vec3 sphCenter[MAX_OBJNUM];
uniform float sphRadius[MAX_OBJNUM];
uniform vec3 sphColor[MAX_OBJNUM];
uniform vec3 sphReflect[MAX_OBJNUM];
uniform vec3 sphTransparent[MAX_OBJNUM];

uniform float width;
uniform float height;
uniform float fov;

uniform vec3 E;

uniform mat4 camRot;


in vec2 pixPos;

out vec4 FragColor;



struct light {
    vec3 pos;
    vec3 color;
};

light lite;

struct ray {
    vec3 origin;
    vec3 dir;
};

struct sphere {
    vec3 center;
    float radius;
    vec3 color;

    float reflect;
    float transparent;
};

sphere createSphere(vec3 center, float radius, vec3 color){
    sphere sph;
    sph.center = center;
    sph.radius = radius;
    sph.color = color;
    return sph;
}

sphere objects[MAX_OBJNUM];

bool intersect(sphere sph, ray r, inout float t0, inout float t1){
    vec3 l = sph.center - r.origin;
    float tca = dot(l,r.dir);
    if(tca < 0) return false;
    float d2 = dot(l,l) - tca * tca;
    if(d2 > sph.radius * sph.radius) return false;
    float thc = sqrt(sph.radius * sph.radius - d2);
    t0 = tca - thc;
    t1 = tca + thc;

    return true;
}

bool traceToLightSource(ray shadowRay, sphere small_sphere){
    for(int i = 0; i < OBJNUM; i++){
        sphere o = objects[i];
        float t0 = FLT_MAX;
        float t1 = FLT_MAX;
        if(intersect(o,shadowRay,t0,t1) && o.center != small_sphere.center){
            return true;
        }
    }


    return false;
}

vec3 calculatePointPHONG(ray shadowRay, vec3 nHit, vec3 pHit, vec3 col){
    float diffuse = (dot(shadowRay.dir, normalize(nHit)));
    float ambient = 0.3;
    float specular = pow(max(dot(normalize(E - pHit),normalize(reflect(-shadowRay.dir, normalize(nHit)))), 0.0f),16);
    float phong = diffuse + ambient + specular;
    vec3 outCol;

    outCol = col * phong;


    return outCol;
}

bool isIntersectingSphere(ray currentRay, inout sphere small_sphere, inout float t_near){
    t_near = FLT_MAX;
    bool hit = false;
    for(int i = 0; i < OBJNUM; i++){
        sphere o = objects[i];
        float t0 = FLT_MAX;
        float t1 = FLT_MAX;

        if(intersect(o,currentRay,t0,t1)){
            if(t0 < 0) {
                t0 = t1;
            }
            if(t0 < t_near){
                t_near = t0;
                small_sphere = o;
                hit = true;
            }
        }
    }
    return hit;

}



ray castRay(float x, float y){
    ray r;
    float invWidth = 1.0 / float(width);
    float invHeight = 1.0 / float(height);
//    float fov = 30;
    float aspectratio = float(width) / float(height);
    float angle = tan(M_PI * 0.5 * fov / 180.);

    float xx = (2 * ((x + 0.5) * invWidth) - 1) * angle * aspectratio;
    float yy = (1 - 2 * ((y + 0.5) * invHeight)) * angle;
    r.dir = normalize(vec3(xx,yy,-1));
    r.dir = vec3(vec4(r.dir,1.0f) * camRot);
    r.origin = E;
    return r;
}



vec3 trace1(ray primRay, int depth) {

    sphere small_sphere;
    bool hit = false;
    float t_near = FLT_MAX;

    for(int i = 0; i < OBJNUM; i++){
        sphere o = objects[i];
        float t0 = FLT_MAX;
        float t1 = FLT_MAX;

        if(intersect(o,primRay,t0,t1)){
            if(t0 < 0) {
                t0 = t1;
            }
            if(t0 < t_near){
                t_near = t0;
                small_sphere = o;
                hit = true;
            }
        }
    }


    if(hit){
        ray shadowRay;

        vec3 pHit = primRay.origin + primRay.dir * t_near;
        vec3 nHit = pHit - small_sphere.center;

        vec3 addCol;

                if(depth != MAX_DEPTH){
                    ray nextRay;
                    nextRay.dir = normalize(reflect(primRay.dir,  normalize(nHit)));
                    nextRay.origin = pHit + 0.2f*normalize(nHit);
//                    addCol = trace1(nextRay,depth + 1);
                }

        shadowRay.origin = pHit + 0.2f*normalize(nHit);
        shadowRay.dir = normalize(lite.pos - pHit);
        bool isInShadow = false;
        //
        vec3 outCol;
        //
        float diffuse = (dot(shadowRay.dir, normalize(nHit)));
        float ambient = 0.7;
        float specular = pow(max(dot(normalize(E - pHit),normalize(reflect(-shadowRay.dir, normalize(nHit)))), 0.0f),16);
        //
        //
        float phong = diffuse + ambient + specular;
        //
        if(depth != MAX_DEPTH){
            outCol = ( 2.f * small_sphere.color + addCol) / 3.0f * phong;
        } else {
            outCol = small_sphere.color * phong;
        }
        //
        //
        for(int i = 0; i < OBJNUM; i++){
            sphere o = objects[i];
            float t0 = FLT_MAX;
            float t1 = FLT_MAX;
            if(intersect(o,shadowRay,t0,t1) && o.center != small_sphere.center){
                isInShadow = true;
            }
        }
        if(isInShadow){
            return  outCol / 2.0f;
        }
        return outCol;
    } else {
        return vec3(0, 0, 0);
    }
    //}

}

vec3 trace() {
    vec3 addCols[MAX_DEPTH + 1];
    ray primRay = castRay(pixPos.x,pixPos.y);
    ray currentRay = primRay;

    int depth = 0;

    for(depth = 0; depth <= MAX_DEPTH; depth++){
        sphere small_sphere;
        float t_near = FLT_MAX;
        bool hit = isIntersectingSphere(currentRay,small_sphere,t_near);


        if(hit){
            ray shadowRay;

            vec3 pHit = currentRay.origin + currentRay.dir * t_near;
            vec3 nHit = pHit - small_sphere.center;

            vec3 addCol;


            shadowRay.origin = pHit + 0.2f*normalize(nHit);
            shadowRay.dir = normalize(lite.pos - pHit);
            bool isInShadow = traceToLightSource(shadowRay, small_sphere);
            vec3 outCol = calculatePointPHONG(shadowRay, nHit, pHit, small_sphere.color);

            if(isInShadow){
               addCols[depth] = outCol / 2.0 ;
            } else {
                addCols[depth] =  outCol;
            }

            ray reflectRay;
            reflectRay.dir = normalize(reflect(currentRay.dir,  normalize(nHit)));
            reflectRay.origin = pHit + 0.2f*normalize(nHit);
            currentRay = reflectRay;

        } else {
            addCols[depth] =  vec3(0.0, 0, 0.0);
            break;
        }

    }

    vec3 outCol = vec3(0,0,0);
    for(int i = 0; i <= depth; i++){
        outCol = (1 - pow(0.5,i)) * outCol + addCols[i] * pow(0.5,i);
    }

    return outCol;

}


void main() {

    for(int i = 0; i < OBJNUM; i++){
        objects[i] = createSphere(sphCenter[i],sphRadius[i],sphColor[i]);
    }
    lite.pos = vec3(0,20,-30);
    lite.color = vec3(1,1,1);

    vec3 col = trace();
//    FragColor = vec4(width/1920,width/1920,width/1920,1.0);
//    FragColor = vec4(primRay.dir.x,primRay.dir.y,width/1920,1.0);
//    col = sphColor[3];
    FragColor = vec4(col.x,col.y,col.z,1.0);
}
