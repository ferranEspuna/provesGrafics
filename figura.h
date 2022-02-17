#ifndef FIGURA_H
#define FIGURA_H
#include "glm/glm.hpp"

#endif // FIGURA_H

class Figura{

public:

    virtual ~Figura() = 0;
    virtual float calculaArea() = 0;
    virtual glm::vec3 obteNormal() = 0;

    void trasllada(glm::vec3 desplazament);
    void escala(glm::vec3 factor_escalat);
    void rota(float radians, glm::vec3 punt_rotacio, glm::vec3 eix_rotacio);




private:

    int n_points;
    glm::vec4 points[];

    static glm::vec3 vec4_to_vec3(glm::vec4 v);
    static glm::vec4 vec3_to_vec4(glm::vec3 v);

    static glm::mat4 baseOrtonormal(glm::vec3 v1, glm::vec3 v2);
    static glm::vec3 getIndependent(glm::vec3 v);

    static glm::mat4 translacio(glm::vec3 v);
    static glm::mat4 homotecia(glm::vec3 factor_escalat);
    static glm::mat4 rotacio(float radians, glm::vec3 punt_rotacio, glm::vec3 eix_rotacio);

    void aplica_transformacio(glm::mat4 t);


};

