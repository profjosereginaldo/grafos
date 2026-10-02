#include <stdio.h>
#include <string.h>
#include "grafo_lista.h"
#include "busca_grafo.h"
#include "ordenacao_topologica.h"
#include "coloracao_grafo.h"

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

    int visitado[MAX_VERTICES];
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
    
    int ordem[MAX_VERTICES];
    memset(visitado, 0, sizeof(visitado));
    memset(ordem, 0, sizeof(ordem));

    printf("Ordena com dfs\n");
    ordenar_dfs(digrafo, visitado, ordem);

    printf("Ordem topologica do digrafo\n"); // apliacao do dfs
    for (int i = 0; i < digrafo->num_vertices; i++) {
        printf("%i ", ordem[i]);
    }
    printf("\n");

    printf("Componentes conexos do digrafo\n"); // aplicacao do dfs
    memset(visitado, 0, sizeof(visitado));
    int num_componentes = 0;
    for (int i = 0; i < digrafo->num_vertices; i++) {
       if (!visitado[i]) {
           num_componentes++;
           dfs(digrafo, i, visitado);
       }
   }

   printf("Total de componentes conexos = %i\n", num_componentes);

   printf("Coloracao de grafos\n");
   int cor[MAX_VERTICES];
   memset(cor, -1, sizeof(cor));
   int cor_usada[MAX_VERTICES];

   coloracao_gulosa(grafo, cor, cor_usada);
   printf("Cores\n");
   for (int i = 0; i < grafo->num_vertices; i++) {
      printf("%i ", cor[i]);
   }
   printf("\n");

   return 0;
}