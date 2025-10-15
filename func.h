#ifndef FUNC_H
#define FUNC_H

float Bhaskara(float a, float b, float c);
void produtoVetorial(float vet1[], float vet2[], float vet3[]);
float produtoEscalar(float vet1[], float vet2[]);
void normalizarVetor(float v[]);
void SistemaGauss(float matriz[3][3], float matrizResultado[3][1], float solucao[3]);

#endif