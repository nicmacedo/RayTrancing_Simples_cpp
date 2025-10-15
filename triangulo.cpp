#include <iostream>
#include <cmath>
#include <numeric>
#include <vector>
#include "func.h"
#include "triangulo.h"
using namespace std;

void intersecaoTriangulo(float eye[], float dir[], float pontoA[], float pontoB[], float pontoC[], float &beta, float &gamma, float &t, float pontoIntersecao[]){
    float matriz[3][3] = {
        {(pontoB[0] - pontoA[0]), (pontoC[0] - pontoA[0]), (-(dir[0]))},
         {(pontoB[1] - pontoA[1]), (pontoC[1] - pontoA[1]), (-(dir[1]))},
        {(pontoB[2] - pontoA[2]), (pontoC[2] - pontoA[2]), (-(dir[2]))}
    };

    float matrizResultado[3][1] = {
        {eye[0] - pontoA[0]},
        {eye[1] - pontoA[1]},
        {eye[2] - pontoA[2]}
    };
    // Resolver o sistema linear usando eliminação de Gauss
    float solucao[3]; // beta, gamma, t
    SistemaGauss(matriz, matrizResultado, solucao);

    beta = solucao[0];
    gamma = solucao[1];
    t = solucao[2];

    //veruificar se a interseção está dentro do triângulo
    if (beta < 0 || gamma < 0 || (beta + gamma) > 1 || t < 0) {
        t = -1; // Sem interseção válida
        cout << "Sem interseção válida com o triângulo." << endl;
        return;
    }
    
    // Calcular ponto de interseção
    pontoIntersecao[0] = eye[0] + t * dir[0];
    pontoIntersecao[1] = eye[1] + t * dir[1];
    pontoIntersecao[2] = eye[2] + t * dir[2];
}

void normalPontoTriangulo(float pontoA[], float pontoB[], float pontoC[], float normal[]){
    // Calcular vetores AB e AC
    float AB[3] = {pontoB[0] - pontoA[0], pontoB[1] - pontoA[1], pontoB[2] - pontoA[2]};
    float AC[3] = {pontoC[0] - pontoA[0], pontoC[1] - pontoA[1], pontoC[2] - pontoA[2]};
    
    // Calcular o produto vetorial AB x AC
    produtoVetorial(AB, AC, normal);
    
    // Calcular o módulo do vetor normal
    normalizarVetor(normal);
}


