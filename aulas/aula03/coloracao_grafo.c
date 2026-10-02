#include <stdlib.h>
#include "grafo_lista.h"
#include "coloracao_grafo.h"

void coloracao_gulosa(GrafoLista *g, int *cor, int *cor_usada)
{
    for (int i = 0; i < g->num_vertices; i++)
    {
        for (int c = 0; c < g->num_vertices; c++) {
            cor_usada[c] = 0;
        }
        
        No *no = g->lista[i];
        while (no != NULL) {
            int v = no->vertice;
            if (cor[v] != -1) cor_usada[cor[v]] = 1;
            no = no->proximo;
        }
        
        int c = 0;
        while(cor_usada[c]) c++;
        cor[i] = c;
    }
}