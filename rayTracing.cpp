#include <iostream>
#include <cmath>
#include <numeric>
#include <vector>
#include "func.h"
#include "esfera.h"
#include "triangulo.h"
#include "sombreamento.h"
#include <windows.h>
using namespace std;
// ============== Dados globais ===================
// --- Câmera ---
float eye[3]         = {-2, 0, 0};
float centerPlano[3] = { 0, 0, 0};
float up[3]          = { 0, 1, 0};
// Vetor direção do raio
float dir[3]         = { 4, 0, 0};
// Eixos da câmera
float xEye[3];
float yEye[3];
float zEye[3];
// --- Esfera ---
float centerEsfera[3] = { 2, 0, 0};
float raio            = 1;
float tEsfera;
float pontoIntersecaoEsfera[3];
float normalEsfera[3];
// --- Triângulo ---
float pontoA[3] = {1, -1, -1};
float pontoB[3] = {1, -1,  1};
float pontoC[3] = {1,  1,  0};
float pontoIntersecaoTriangulo[3];
float betaT, gamma, tTriangulo;
float normalTriangulo[3];
// --- Sombreamento ---
float posLuz[3] = {0, 4, 0};
float corLuz[3] = {255, 255, 255};
float L[3] = {0, 0, 0}; 
float V[3] = {0, 0, 0}; 
float H[3] = {0, 0, 0};

float ka = 0.25;
float kd = 0.25;
float ks = 0.25;
float p =  1;

float corAmbiente[3];
float corDifusa[3];
float corEspecular[3];
float corFinal[3];

//Eixos da câmera
void eixos(float eye[], float center[], float up[]){
	 // --- zEye ---
    float diff[3] = {
        eye[0] - center[0],
        eye[1] - center[1],
        eye[2] - center[2]
    };
    normalizarVetor(diff);
    zEye[0] = diff[0];
    zEye[1] = diff[1];
    zEye[2] = diff[2];

    // --- xEye = ---
    float vet[3];
    produtoVetorial(up, zEye, vet);
    normalizarVetor(vet);
    xEye[0] = vet[0];
    xEye[1] = vet[1];
    xEye[2] = vet[2];

    // --- yEye ---
    produtoVetorial(zEye, xEye, yEye);
}

int main(){
    //configurar console para UTF-8 para exibir os caracteres especiais corretamente
    SetConsoleOutputCP(65001);  // UTF-8
    setlocale(LC_ALL, "Portuguese_Brazil.utf8");
    // Cálculo dos eixos da câmera
    cout << "============================================================" << endl;
    cout << "                   DADOS DA CÂMERA" << endl;
    cout << "============================================================" << endl;
    cout << "• Eye:        (" << eye[0] << ", " << eye[1] << ", " << eye[2] << ")" << endl;
    cout << "• Center:     (" << centerPlano[0] << ", " << centerPlano[1] << ", " << centerPlano[2] << ")" << endl;
    cout << "• Up:         (" << up[0] << ", " << up[1] << ", " << up[2] << ")" << endl;
    eixos(eye, centerPlano, up);
    cout << "------------------------------------------------------------" << endl;
    cout << "                 EIXOS DA CÂMERA" << endl;
    cout << "------------------------------------------------------------" << endl;
    cout << "• xEye:       (" << xEye[0] << ", " << xEye[1] << ", " << xEye[2] << ")" << endl;
    cout << "• yEye:       (" << yEye[0] << ", " << yEye[1] << ", " << yEye[2] << ")" << endl;
    cout << "• zEye:       (" << zEye[0] << ", " << zEye[1] << ", " << zEye[2] << ")" << endl;
    cout << "============================================================" << endl << endl;

    // Teste de interseção da esfera
    cout << "============================================================" << endl;
    cout << "               INTERSEÇÃO COM A ESFERA" << endl;
    cout << "============================================================" << endl;
    cout << "                   Dados da Esfera" << endl;
    cout << "------------------------------------------------------------" << endl;
    cout << "• Centro:     (" << centerEsfera[0] << ", " << centerEsfera[1] << ", " << centerEsfera[2] << ")" << endl;
    cout << "• Raio:       " << raio << endl;
    cout << "• Direção:    (" << dir[0] << ", " << dir[1] << ", " << dir[2] << ")" << endl;
    cout << "------------------------------------------------------------" << endl;
    cout << "                 Cálculos Realizados" << endl;
    cout << "------------------------------------------------------------" << endl;
    intersecaoEsfera(eye, dir, centerEsfera, raio, tEsfera, pontoIntersecaoEsfera);
    cout << "• t:          " << tEsfera << endl;
    cout << "------------------------------------------------------------" << endl;
    cout << "                    Resultados" << endl;
    cout << "------------------------------------------------------------" << endl;
    cout << "• Ponto:      (" << pontoIntersecaoEsfera[0] << ", " 
                              << pontoIntersecaoEsfera[1] << ", " 
                              << pontoIntersecaoEsfera[2] << ")" << endl;
    normalPontoEsfera(pontoIntersecaoEsfera, centerEsfera, normalEsfera);
    cout << "• Normal:     (" << normalEsfera[0] << ", " 
                              << normalEsfera[1] << ", " 
                              << normalEsfera[2] << ")" << endl;
    cout << "============================================================" << endl << endl;

    // Teste de interseção do triângulo
    cout << "============================================================" << endl;
    cout << "              INTERSEÇÃO COM O TRIÂNGULO" << endl;
    cout << "============================================================" << endl;
    cout << "                  Dados do Triângulo" << endl;
    cout << "------------------------------------------------------------" << endl;
    cout << "• Ponto A:    (" << pontoA[0] << ", " << pontoA[1] << ", " << pontoA[2] << ")" << endl;
    cout << "• Ponto B:    (" << pontoB[0] << ", " << pontoB[1] << ", " << pontoB[2] << ")" << endl;
    cout << "• Ponto C:    (" << pontoC[0] << ", " << pontoC[1] << ", " << pontoC[2] << ")" << endl;
    cout << "• Direção:    (" << dir[0] << ", " << dir[1] << ", " << dir[2] << ")" << endl;
    cout << "------------------------------------------------------------" << endl;
    cout << "                 Cálculos Realizados" << endl;
    cout << "------------------------------------------------------------" << endl;
    intersecaoTriangulo(eye, dir, pontoA, pontoB, pontoC, betaT, gamma, tTriangulo, pontoIntersecaoTriangulo);
    cout << "• beta:       " << betaT << endl;
    cout << "• gamma:      " << gamma << endl;
    cout << "• t:          " << tTriangulo << endl;
    cout << "------------------------------------------------------------" << endl;
    cout << "                    Resultados" << endl;
    cout << "------------------------------------------------------------" << endl;
    cout << "• Ponto:      (" << pontoIntersecaoTriangulo[0] << ", " 
                              << pontoIntersecaoTriangulo[1] << ", " 
                              << pontoIntersecaoTriangulo[2] << ")" << endl;
    normalPontoTriangulo(pontoA, pontoB, pontoC, normalTriangulo);
    cout << "• Normal:     (" << normalTriangulo[0] << ", " 
                              << normalTriangulo[1] << ", " 
                              << normalTriangulo[2] << ")" << endl;

    // Validação das coordenadas baricêntricas
    cout << "------------------------------------------------------------" << endl;
    cout << "           Validação Coordenadas Baricêntricas" << endl;
    cout << "------------------------------------------------------------" << endl;
    cout << "• β ≥ 0:      " << (betaT >= 0 ? "✓ SIM" : "✗ NÃO") << endl;
    cout << "• γ ≥ 0:      " << (gamma >= 0 ? "✓ SIM" : "✗ NÃO") << endl;
    cout << "• β + γ ≤ 1:  " << ((betaT + gamma) <= 1 ? "✓ SIM" : "✗ NÃO") << endl;
    cout << "• Válido:     " << (betaT >= 0 && gamma >= 0 && (betaT + gamma) <= 1 ? "✓ SIM" : "✗ NÃO") << endl;
    cout << "============================================================" << endl;

    // Cálculo do sombreamento na interseção com a esfera
    cout << "============================================================" << endl;
    cout << "          SOMBREAMENTO NA INTERSEÇÃO COM A ESFERA" << endl;
    cout << "============================================================" << endl;
    cout << "                  Dados do Sombreamento" << endl;
    cout << "------------------------------------------------------------" << endl;
    cout << "• Posição da Luz:         (" << posLuz[0] << ", " << posLuz[1] << ", " << posLuz[2] << ")" << endl;
    cout << "• Cor da Luz:             (" << corLuz[0] << ", " << corLuz[1] << ", " << corLuz[2] << ")" << endl;
    cout << "• Coef. Ambiente (ka):    " << ka << endl;
    cout << "• Coef. Difuso (kd):      " << kd << endl;
    cout << "• Coef. Especular (ks):   " << ks << endl;
    cout << "• Expoente de Brilho (p): " << p << endl;
    calcularVetores(pontoIntersecaoEsfera, posLuz, L, V, normalEsfera, eye, H);
    cout << "• L (vetor luz):          (" << L[0] << ", " << L[1] << ", " << L[2] << ")" << endl;
    cout << "• V (vetor visão):        (" << V[0] << ", " << V[1] << ", " << V[2] << ")" << endl;
    cout << "• H (vetor meio):         (" << H[0] << ", " << H[1] << ", " << H[2] << ")" << endl;
    cout << "------------------------------------------------------------" << endl;
    cout << "                 Cálculos Realizados" << endl;
    cout << "------------------------------------------------------------" << endl;

    sombreamentoAmbiente(ka, corLuz, corAmbiente);
    sombreamentoDifuso(kd, corLuz, L, normalEsfera, corDifusa);
    sombreamentoEspecular(ks, corLuz, H, p, corEspecular, normalEsfera);
    sombreamentoBlinnPhong(corAmbiente, corDifusa, corEspecular, corFinal);
    cout << "------------------------------------------------------------" << endl;
    cout << "                    Resultados" << endl;
    cout << "------------------------------------------------------------" << endl;
    cout << "• Cor Ambiente:              (" << corAmbiente[0] << ", " << corAmbiente[1] << ", " << corAmbiente[2] << ")" << endl;
    cout << "• Cor Difusa:                (" << corDifusa[0] << ", " << corDifusa[1] << ", " << corDifusa[2] << ")" << endl;
    cout << "• Cor Especular:             (" << corEspecular[0] << ", " << corEspecular[1] << ", " << corEspecular[2] << ")" << endl;
    cout << "• Cor Final(Blinn-Phong):    (" << corFinal[0] << ", " << corFinal[1] << ", " << corFinal[2] << ")" << endl;
    cout << "============================================================" << endl << endl;


    return 0;
}