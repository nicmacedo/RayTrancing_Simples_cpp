#include <iostream>
#include <cmath>
#include <numeric>
#include <vector>
#include "func.h"

using namespace std;

//fórmula de Bhaskara
float Bhaskara(float a, float b, float c){
    cout << "a: " << a << " b: " << b << " c: " << c << endl;
    float t1, t2;
    float delta = b*b - 4*a*c;
    if(delta < 0){
        t1 = -1;
        t2 = -1;
    } else {
        t1 = (-b + sqrt(delta)) / (2*a);
        t2 = (-b - sqrt(delta)) / (2*a);  
        cout << "t1: " << t1 << " t2: " << t2 << endl; 
        return min(t1, t2);
    }
}

//produto vetorial (v1 X v2)
void produtoVetorial(float vet1[], float vet2[], float vet3[]) {
    vet3[0] = vet1[1]*vet2[2] - vet1[2]*vet2[1];
    vet3[1] = vet1[2]*vet2[0] - vet1[0]*vet2[2];
    vet3[2] = vet1[0]*vet2[1] - vet1[1]*vet2[0];
}

// Normaliza um vetor (torna o módulo = 1)
void normalizarVetor(float v[]) {
    float modulo = sqrt(produtoEscalar(v, v));
    if (modulo != 0) {
        v[0] /= modulo;
        v[1] /= modulo;
        v[2] /= modulo;
    }
}

//produto escalar (v1 · v2)
float produtoEscalar(float vet1[], float vet2[]) {
    return vet1[0]*vet2[0] + vet1[1]*vet2[1] + vet1[2]*vet2[2];
}

// Resolução de sistema linear 3x3 usando eliminação de Gauss
void SistemaGauss(float matriz[3][3], float matrizResultado[3][1], float solucao[3]) {
    // Cria matriz aumentada [matriz|matrizResultado]
    float aumentada[3][4];
    
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            aumentada[i][j] = matriz[i][j];
        }
        aumentada[i][3] = matrizResultado[i][0];
    }
    
    // Eliminação de Gauss com pivotamento
    for (int i = 0; i < 3; i++) {
        // Pivotamento: encontra linha com maior valor absoluto na coluna i
        int maxLinha = i;
        for (int k = i + 1; k < 3; k++) {
            if (fabs(aumentada[k][i]) > fabs(aumentada[maxLinha][i])) {
                maxLinha = k;
            }
        }
        
        // Troca linhas se necessário
        if (maxLinha != i) {
            for (int j = 0; j < 4; j++) {
                float temp = aumentada[i][j];
                aumentada[i][j] = aumentada[maxLinha][j];
                aumentada[maxLinha][j] = temp;
            }
        }
        
        // Eliminação
        for (int k = i + 1; k < 3; k++) {
            float fator = aumentada[k][i] / aumentada[i][i];
            for (int j = i; j < 4; j++) {
                aumentada[k][j] -= fator * aumentada[i][j];
            }
        }
    }
    
    // Substituição reversa
    for (int i = 2; i >= 0; i--) {
        solucao[i] = aumentada[i][3] / aumentada[i][i];
        for (int k = i - 1; k >= 0; k--) {
            aumentada[k][3] -= aumentada[k][i] * solucao[i];
        }
    }
}