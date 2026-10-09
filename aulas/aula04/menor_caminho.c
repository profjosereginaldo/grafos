#include <stdlib.h>
#include <string.h>
#include "grafo_lista_ponderado.h"
#include "menor_caminho.h"

int bfs(GrafoLista *g, int origem, int destino) {
    if (origem == destino) {
        return 0;
    }
    
    int fila[MAX_VERTICES];
    int distancia[MAX_VERTICES];
    int inicio = 0;
    int final = 0;

    memset(distancia, -1, sizeof(distancia));

    distancia[origem] = 0;
    fila[final++] = origem;
    while (inicio < final)
    {
        int u = fila[inicio++];
        No *no = g->lista[u];
        while (no != NULL)
        {
            int v = no->vertice;
            if (distancia[v] == -1)
            {
                distancia[v] = distancia[u] + 1;
                fila[final++] = v;
            
                if (destino == v) {
                  return distancia[v];
                }
            }
            no = no->proximo;            
        }
    }

    return -1;
}