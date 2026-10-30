#include <stdio.h>
#include "grafo_lista.h"
#include "grafo_bipartido.h"

int main() {
    GrafoLista *grafo = criar_grafo(6);

    // X={0,1,2} Y={3,4,5} E={{0,3},{0,4},{1,4},{1,5},{2,3},{2,5}}
    adicionar_aresta(grafo, 0,3);
    adicionar_aresta(grafo, 0,4);
    adicionar_aresta(grafo, 1,4);
    adicionar_aresta(grafo, 1,5);
    adicionar_aresta(grafo, 2,3);
    adicionar_aresta(grafo, 2,5);

    imprimir_grafo(grafo);
    printf("\nO grafo eh bipartido? %s\n", eh_bipartido(grafo) ? "sim" : "nao");

    Aresta arestas[6];
    arestas[0].u = 0; arestas[0].v = 3; 
    arestas[1].u = 0; arestas[1].v = 4; 
    arestas[2].u = 1; arestas[2].v = 4; 
    arestas[3].u = 1; arestas[3].v = 5;
    arestas[4].u = 2; arestas[4].v = 3; 
    arestas[5].u = 2; arestas[5].v = 5; 

    int emparelhamento_maximo = emparelhamento_guloso(arestas, 6, 6);
    printf("O emparelhamento maximo = %i\n", emparelhamento_maximo);

    return 0;
}