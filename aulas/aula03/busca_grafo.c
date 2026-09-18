#include <stdio.h>
#include <stdlib.h>
#include "grafo_lista.h"

void dfs(GrafoLista *g, int u, int *visitado) {
    visitado[u] = 1;    
    printf("Empilha %i, Visita %i\n", u+1, u+1);
    No *no = g->lista[u];
    while (no != NULL) {
        int v = no->vertice;
        if (!visitado[v]) dfs(g, v, visitado); // pilha de recursividade
        no = no->proximo;
    }
    printf("Desempilha %i\n", u+1);
}

void bfs(GrafoLista *g, int u, int *visitado) {
   int fila[10];
   int inicio = 0;
   int final = 0;

   visitado[u] = 1;
   fila[final++] = u;
   printf("Visita %i, Enfilera %i\n", u+1, u+1);
   
   while(inicio < final) {
      int i = fila[inicio++];
      printf("Desinfilera %i\n", i+1);
      No *no = g->lista[i];
      while(no != NULL) {
        int v = no->vertice;
        if (!visitado[v]) {
            visitado[v] = 1;
            fila[final++] = v;
            printf("Visita %i, Enfilera %i\n", v+1, v+1);
        }
        no = no->proximo;
      }
   }



}
