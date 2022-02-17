#include "figura.h"
#include "glm/glm.hpp"

Figura::~Figura(){
    delete points;
}

glm::vec3 Figura::vec4_to_vec3(glm::vec4 v){
    return glm::vec3(v.x, v.y, v.z);
}

glm::vec4 Figura::vec3_to_vec4(glm::vec3 v){
    return glm::vec4(v.x, v.y, v.z, 1);
}


glm::vec3 Figura::getIndependent(glm::vec3 v){

    float* arr = new float[3];
    int idx = 0;

    for(int i = 0; idx < 3; idx++){

        if ( fabs(v[i]) > fabs(v[idx]) ){
            idx = i;
        }
    }

    arr[idx] = 1;
    glm::vec3 w(arr[0], arr[1], arr[2]);

    delete arr;
    return w;

}

glm::mat4 Figura::baseOrtonormal(glm::vec3 v1, glm::vec3 v2){

    glm::vec3 w1 = glm::normalize(v1);
    glm::vec3 w2 = glm::normalize(v2 - glm::dot(w1, v2)  * w1);
    glm::vec3 w3 = glm::cross(w1, w2);

    return glm::mat4(w1.x, w2.x, w3.x, 0,
                     w1.y, w2.y, w3.y, 0,
                     w1.z, w2.z, w3.z, 0,
                     0,    0,    0,    1);

}


glm::mat4 Figura::translacio(glm::vec3 v){
    return glm::mat4(1, 0, 0, v.x,
                     0, 1, 0, v.y,
                     0, 0, 1, v.z,
                     0, 0, 0, 1);
}

glm::mat4 Figura::homotecia(glm::vec3 v){
    return glm::mat4(v.x,0,  0,  0,
                     0,  v.y,0,  0,
                     0,  0,  v.z,0,
                     0,  0,  0,  1);
}

glm::mat4 Figura::rotacio(float radians, glm::vec3 punt_rotacio, glm::vec3 eix_rotacio){

    glm::mat4 a = baseOrtonormal(eix_rotacio, getIndependent(eix_rotacio));
    glm::mat4 d = translacio(punt_rotacio);
    glm::mat4 antid = translacio(- punt_rotacio);

    float c = glm::cos(radians);
    float s = glm::sin(radians);

    glm::mat4 rot_vect(1, 0, 0, 0,
                       0, c, s, 0,
                       0,-s, c, 0,
                       0, 0, 0, 1);

    return d * a * rot_vect * glm::inverse(a) * antid;


}


void Figura::aplica_transformacio(glm::mat4 t){

    for(int i = 0; i < n_points; i++){
        points[i] = t * points[i];

    }
}

void Figura::trasllada(glm::vec3 desplazament){

    glm::mat4 trans = translacio(desplazament);
    aplica_transformacio(trans);
}

void Figura::escala(glm::vec3 factor_escalat){

    glm::mat4 hom = homotecia(factor_escalat);
    aplica_transformacio(hom);

}

void Figura::rota(float radians, glm::vec3 punt_rotacio, glm::vec3 eix_rotacio){

    glm::mat4 rot = rotacio(radians, punt_rotacio, eix_rotacio);
    aplica_transformacio(rot);
}

static glm::mat4 rotacio(float radians, glm::vec3 punt_rotacio, glm::vec3 eix_rotacio);
