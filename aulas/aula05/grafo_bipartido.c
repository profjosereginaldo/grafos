#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "grafo_lista.h"
#include "grafo_bipartido.h"

int eh_bipartido(GrafoLista *g) {
    int cor[MAX_VERTICES];
    memset(cor, -1, sizeof(cor));

    for (int i = 0; i < g->num_vertices; i++) {
        if (cor[i] != -1) continue;
        
        // BFS
        int inicio = 0, fim = 0;
        int fila[MAX_VERTICES];
        fila[fim++] = i;
        cor[i] = 0;
        while (inicio < fim) {
            int u = fila[inicio++];
            No *no = g->lista[u];
            while (no != NULL) {
                int v = no->vertice;
                if (cor[v] == -1) {
                    cor[v] = 1 - cor[u]; // 0 OU 1
                    fila[fim++] = v;
                } else if (cor[v] == cor[u]) return 0;
                no = no->proximo;
            }
        }
    }

    return 1;
}

int emparelhamento_guloso(Aresta *a, int m, int n) {
   int count = 0;
   int usado[MAX_VERTICES]; 
   int pareado[MAX_VERTICES]; 
   memset(usado, 0, sizeof(usado));
   memset(pareado, -1, sizeof(pareado));    

   for (int i = 0; i < m; i++) {
       int u = a[i].u;
       int v = a[i].v;
       if (pareado[v] == -1 && pareado[u] == -1) {
           pareado[v] = u;
           pareado[u] = v;
           count++;
       }
   }

   printf("\n");
   for (int i=0; i<n; i++) {
     printf("{%i, %i} ", i+1, pareado[i]+1);
   }
   printf("\n");

   return count;
}
