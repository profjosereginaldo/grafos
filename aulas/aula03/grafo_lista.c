#include <stdio.h>
#include <stdlib.h>
#include "grafo_lista.h"

GrafoLista *criar_grafo(int n)
{
    GrafoLista *g = (GrafoLista *)malloc(sizeof(GrafoLista));
    g->num_vertices = n;
    g->lista = (No **)malloc(sizeof(No) * n);
    for (int i = 0; i < n; i++)
    {
        g->lista[i] = NULL;
    }
    return g;
}

void adicionar_aresta(GrafoLista *g, int u, int v)
{
    // u -> v
    No *proximo = g->lista[u];
    No *no = (No *)malloc(sizeof(No));
    no->vertice = v;
    no->proximo = proximo;
    g->lista[u] = no;

    // v -> u
    proximo = g->lista[v];
    no = (No *)malloc(sizeof(No));
    no->vertice = u;
    no->proximo = proximo;
    g->lista[v] = no;
}

void adicionar_arco(GrafoLista *g, int u, int v)
{
    // u -> v
    No *proximo = g->lista[u];
    No *no = (No *)malloc(sizeof(No));
    no->vertice = v;
    no->proximo = proximo;
    g->lista[u] = no;
}

void imprimir_grafo(GrafoLista *g) {
    printf("\n");
    for (int i = 0; i < g->num_vertices; i++)
    {
        printf("%i: -> ", i + 1);
        No *no = g->lista[i];
        while (no != NULL)
        {
            printf("%i -> ", no->vertice + 1);
            no = no->proximo;
        }
        printf("NULL\n");
    }
    printf("\n");
}
