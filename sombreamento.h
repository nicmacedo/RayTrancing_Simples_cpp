#ifndef SOMBREAMENTO_H
#define SOMBREAMENTO_H

void calcularVetores(float pontoIntersecao[], float posLuz[], float L[], float V[], float N[], float eye[], float H[]);
void sombreamentoAmbiente(float ka, float I[], float corAmbiente[]);
void sombreamentoDifuso(float kd, float I[], float L[], float N[], float CorDifusa[]);
void sombreamentoEspecular(float ks, float I[], float H[], float p, float corEspecular[], float N[]);
void sombreamentoBlinnPhong(float corAmbiente[], float corDifusa[], float corEspecular[], float corFinal[]);

#endif