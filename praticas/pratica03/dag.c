#include <stdlib.h>
#include "dag.h"

int *ordenacao_topologica_kahn(GrafoLista *g, int *tamanho)
{
    if (g == NULL || tamanho == NULL)
        return NULL;

    *tamanho = 0;

    int *grau_entrada = calloc(g->n, sizeof(int));
    int *fila = malloc(g->n * sizeof(int));
    int *ordem = malloc(g->n * sizeof(int));

    if (grau_entrada == NULL || fila == NULL || ordem == NULL) {
        free(grau_entrada);
        free(fila);
        free(ordem);
        return NULL;
    }

    /* Calcula o grau de entrada de cada vértice */
    for (int u = 0; u < g->n; u++) {
        for (No *p = g->adj[u]; p != NULL; p = p->prox) {
            grau_entrada[p->destino]++;
        }
    }

    /* Coloca na fila os vértices com grau de entrada zero */
    int inicio = 0;
    int fim = 0;

    for (int i = 0; i < g->n; i++) {
        if (grau_entrada[i] == 0) {
            fila[fim++] = i;
        }
    }

    /* Algoritmo de Kahn */
    while (inicio < fim) {
        int u = fila[inicio++];
        ordem[*tamanho] = u;
        (*tamanho)++;

        for (No *p = g->adj[u]; p != NULL; p = p->prox) {
            int v = p->destino;
            grau_entrada[v]--;

            if (grau_entrada[v] == 0) {
                fila[fim++] = v;
            }
        }
    }

    free(grau_entrada);
    free(fila);

    /* Se não visitou todos, existe ciclo */
    if (*tamanho != g->n) {
        free(ordem);
        *tamanho = 0;
        return NULL;
    }

    return ordem;
}

static void dfs_topologica(
    GrafoLista *g,
    int u,
    int *estado,
    int *ordem,
    int *posicao,
    int *ciclo
)
{
    if (*ciclo)
        return;

    estado[u] = 1;

    for (No *p = g->adj[u]; p != NULL; p = p->prox) {
        int v = p->destino;

        if (estado[v] == 0) {
            dfs_topologica(g, v, estado, ordem, posicao, ciclo);
        } else if (estado[v] == 1) {
            *ciclo = 1;
            return;
        }
    }

    estado[u] = 2;

    ordem[*posicao] = u;
    (*posicao)--;
}

int *ordenacao_topologica_dfs(GrafoLista *g, int *tamanho)
{
    if (g == NULL || tamanho == NULL)
        return NULL;

    *tamanho = 0;

    int *estado = calloc(g->n, sizeof(int));
    int *ordem = malloc(g->n * sizeof(int));

    if (estado == NULL || ordem == NULL) {
        free(estado);
        free(ordem);
        return NULL;
    }

    int posicao = g->n - 1;
    int ciclo = 0;

    for (int i = 0; i < g->n; i++) {
        if (estado[i] == 0) {
            dfs_topologica(g, i, estado, ordem, &posicao, &ciclo);

            if (ciclo)
                break;
        }
    }

    free(estado);

    if (ciclo) {
        free(ordem);
        return NULL;
    }

    *tamanho = g->n;
    return ordem;
}

int eh_dag(GrafoLista *g)
{
    if (g == NULL)
        return 0;

    int tamanho = 0;
    int *ordem = ordenacao_topologica_kahn(g, &tamanho);

    if (ordem == NULL)
        return 0;

    free(ordem);
    return 1;
}