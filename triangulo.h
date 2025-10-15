#ifndef TRIANGULO_H
#define TRIANGULO_H

void intersecaoTriangulo(float eye[], float dir[], float pontoA[], float pontoB[], float pontoC[], float &beta, float &gamma, float &t, float pontoIntersecao[]);
void normalPontoTriangulo(float pontoA[], float pontoB[], float pontoC[], float normal[]);

#endif