#ifndef ESFERA_H
#define ESFERA_H

void intersecaoEsfera(float eye[], float dir[], float center[], float raio, float &t, float pontoIntersecaoEsfera[]);
void normalPontoEsfera(float pontoIntersecao[], float center[], float normal[]);

#endif