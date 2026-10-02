#include <stdio.h>
#include <string.h>
#include "grafo_lista_ponderado.h"

int main()
{
    GrafoLista *grafo = criar_grafo(5);

    adicionar_aresta(grafo, 0, 1, 5);
    adicionar_aresta(grafo, 0, 2, 9);
    adicionar_aresta(grafo, 1, 3, 3);
    adicionar_aresta(grafo, 2, 3, 8);
    adicionar_aresta(grafo, 3, 4, 4);

    printf("Grafo nao orientado\n");
    imprimir_grafo(grafo);

   return 0;
}