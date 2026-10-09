#include <stdio.h>
#include <string.h>
#include "grafo_lista_ponderado.h"
#include "menor_caminho.h"

int main()
{
    GrafoLista *grafo = criar_grafo(5);

    adicionar_aresta(grafo, 0, 1, 5);
    adicionar_aresta(grafo, 0, 2, 9);
    adicionar_aresta(grafo, 1, 3, 3);
    adicionar_aresta(grafo, 2, 3, 8);
    adicionar_aresta(grafo, 3, 4, 4);

    printf("Grafo ponderado\n");
    imprimir_grafo(grafo);

    GrafoLista *grafo_nao_ponderado = criar_grafo(6);
    adicionar_aresta(grafo_nao_ponderado, 0, 1, 1);
    adicionar_aresta(grafo_nao_ponderado, 0, 2, 1);
    adicionar_aresta(grafo_nao_ponderado, 1, 3, 1);
    adicionar_aresta(grafo_nao_ponderado, 2, 3, 1);
    adicionar_aresta(grafo_nao_ponderado, 2, 4, 1);
    adicionar_aresta(grafo_nao_ponderado, 3, 5, 1);
    adicionar_aresta(grafo_nao_ponderado, 4, 5, 1);

    printf("Grafo nao ponderado\n");
    imprimir_grafo(grafo_nao_ponderado);

    printf("Distancia de A a A: %i\n", bfs(grafo_nao_ponderado, 0, 0));
    printf("Distancia de A a B,C: %i\n", bfs(grafo_nao_ponderado, 0, 1));
    printf("Distancia de A a D,E: %i\n", bfs(grafo_nao_ponderado, 0, 3));
    printf("Distancia de A a F: %i\n", bfs(grafo_nao_ponderado, 0, 5));

    return 0;
}