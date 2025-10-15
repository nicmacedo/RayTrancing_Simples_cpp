#include <iostream>
#include <cmath>
#include "sombreamento.h"
#include "func.h"

using namespace std;

/*
* O sombreamentos são calculados com base no modelo de iluminação de Phong,
* que considera três componentes principais: ambiente, difusa e especular.
* E será usado para calcular a cor final de um ponto na superfície de um objeto.
*/


// Normalizar os vetors da Luz (L), da Visão (V), vetor h
void calcularVetores(float pontoIntersecao[], float posLuz[], float L[], float V[], float N[], float eye[], float H[]){
    // Vetor L: da interseção até a luz
    L[0] = posLuz[0] - pontoIntersecao[0];
    L[1] = posLuz[1] - pontoIntersecao[1];
    L[2] = posLuz[2] - pontoIntersecao[2];
    normalizarVetor(L);

    // Vetor V: da interseção até o olho
    V[0] = eye[0] - pontoIntersecao[0];
    V[1] = eye[1] - pontoIntersecao[1];
    V[2] = eye[2] - pontoIntersecao[2];
    normalizarVetor(V);

    // Vetor H: média normalizada entre L e V
    // Soma direto pq já ta normalizado
    float soma[3] = {L[0] + V[0], L[1] + V[1], L[2] + V[2]};
    normalizarVetor(soma);
    H[0] = soma[0];
    H[1] = soma[1];
    H[2] = soma[2];
}

// --- Sombreamento Ambiente ---
void sombreamentoAmbiente(float ka, float I[], float corAmbiente[]){
    for (int i = 0; i < 3; i++) {
        corAmbiente[i] = ka * I[i];
    }
}


// --- Sombreamento Difuso ---
void sombreamentoDifuso(float kd, float I[], float L[], float N[], float CorDifusa[]){
    // Calcular N · L
    float LN = 0.0;
    LN = produtoEscalar(L, N);
    LN = max(LN, 0.0f);
    cout << "N·L: " << LN << endl;

    for (int i = 0; i < 3; i++) {
        CorDifusa[i] = kd * I[i] * LN;
    }
}

// --- Sombreamento Especular ---
void sombreamentoEspecular(float ks, float I[], float H[], float p, float corEspecular[], float N[]) {
    float Nh = produtoEscalar(N, H);
    Nh = max(Nh, 0.0f);
    cout << "N·H: " << Nh << endl;

    for (int i = 0; i < 3; i++) {
        corEspecular[i] = ks * I[i] * pow(Nh, p);
        corEspecular[i] = min(corEspecular[i], 255.0f);
    }
}

// --- Sombreamento Blinn-Phong ---
void sombreamentoBlinnPhong(float corAmbiente[], float corDifusa[], float corEspecular[], float corFinal[]){
    for (int i = 0; i < 3; i++) {
        corFinal[i] = corAmbiente[i] + corEspecular[i];
        corFinal[i] = min(corFinal[i], 255.0f); 
    }
}
