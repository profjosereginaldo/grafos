#ifndef GRAFO_LISTA_PONDERADO_H
#define GRAFO_LISTA_PONDERADO_H

#define MAX_VERTICES 100

typedef struct No
{
    int vertice;
    int peso;
    struct No *proximo;
} No;

typedef struct
{
    No **lista;
    int num_vertices;
} GrafoLista;

GrafoLista *criar_grafo(int n);
void adicionar_aresta(GrafoLista *g, int u, int v, int p);
void adicionar_arco(GrafoLista *g, int u, int v, int p);
void imprimir_grafo(GrafoLista *g);

#endif