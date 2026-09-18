#include <stdio.h>
#include <string.h>
#include "grafo_lista.h"
#include "busca_grafo.h"

int main()
{
    GrafoLista *grafo = criar_grafo(5);

    adicionar_aresta(grafo, 0, 1);
    adicionar_aresta(grafo, 0, 2);
    adicionar_aresta(grafo, 1, 3);
    adicionar_aresta(grafo, 2, 3);
    adicionar_aresta(grafo, 3, 4);
 
    printf("Grafo nao orientado\n");
    imprimir_grafo(grafo);

    int visitado[10];
    memset(visitado, 0, sizeof(visitado));
    printf("Inicia dfs pelo vertice 1\n");
    dfs(grafo, 0, visitado);
    printf("\n");

    memset(visitado, 0, sizeof(visitado));
    printf("Inicia bfs pelo vertice 1\n");
    bfs(grafo, 0, visitado);
    printf("\n");

    GrafoLista *digrafo = criar_grafo(4);

    adicionar_arco(digrafo, 0, 1);
    adicionar_arco(digrafo, 0, 2);
    adicionar_arco(digrafo, 1, 3);
    adicionar_arco(digrafo, 2, 3);

   printf("Grafo orientado (Digrafo)\n");
   imprimir_grafo(digrafo);
 
    return 0;
}