#include <stdlib.h>
#include "grafo_lista.h"
#include "ordenacao_topologica.h"

void ordenar_dfs(GrafoLista *g, int *visitado, int *ordenacao)
{
    int idx = 0;
    for (int i = 0; i < g->num_vertices; i++)
    {
        if (!visitado[i])
        {
            No *no = g->lista[i];
            int v = no->vertice;
            if (!visitado[v]) {
                buscar_dfs(g, v, visitado, &idx, ordenacao);
            }
        }
    }
}

void buscar_dfs(GrafoLista *g, int u, int *visitado, int *idx, int *ordenacao)
{
    visitado[u] = 1;
    ordenacao[*idx++] = u+1;
    No *no = g->lista[u];
    while (no != NULL)
    {
        int v = no->vertice;
        if (!visitado[v])
            buscar_dfs(g, v, visitado, idx, ordenacao);
        no = no->proximo;
    }
}