#ifndef COLORACAO_H
#define COLORACAO_H

#include "../pratica01/grafo_lista.h"

int *coloracao_gulosa(GrafoLista *g, int *num_cores);
int *coloracao_welsh_powell(GrafoLista *g, int *num_cores);
int eh_bipartido(GrafoLista *g);

#endif