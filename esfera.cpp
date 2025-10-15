#include <iostream>
#include <cmath>
#include <numeric>
#include <vector>
#include "func.h"
#include "esfera.h"
using namespace std;

void  intersecaoEsfera(float eye[], float dir[], float center[], float raio, float &t, float pontoIntersecao[]){
    // Calcular vetor (eye - center)
    float diff[3];
    diff[0] = eye[0] - center[0];
    diff[1] = eye[1] - center[1];
    diff[2] = eye[2] - center[2];

    // Calcular coeficientes a, b e c
    float a = produtoEscalar(dir, dir);
    float b = 2 * (produtoEscalar(dir, diff));
    float c = (produtoEscalar(diff, diff)) - raio*raio;

    // Calcular t1 e t2 usando a fórmula de Bhaskara
    t = Bhaskara(a, b, c);

    pontoIntersecao[0] = eye[0] + t*dir[0];
    pontoIntersecao[1] = eye[1] + t*dir[1];
    pontoIntersecao[2] = eye[2] + t*dir[2];
}

void normalPontoEsfera(float pontoIntersecao[], float center[], float normal[]){
    // Calcular vetor (pontoIntersecao - center)
    float diff[3];
    diff[0] = pontoIntersecao[0] - center[0];
    diff[1] = pontoIntersecao[1] - center[1];
    diff[2] = pontoIntersecao[2] - center[2];

    // Calcular a normal
    normalizarVetor(diff);
    normal[0] = diff[0];
    normal[1] = diff[1];
    normal[2] = diff[2];
}
