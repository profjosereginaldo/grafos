#include <stdlib.h>
#include "conectividade.h"

/*
 * DFS de Tarjan: calcula tempos de descoberta e low-link,
 * marcando vertices de articulacao e/ou coletando pontes.
 * eh_articulacao e pontes podem ser NULL quando o chamador
 * nao tiver interesse naquele resultado especifico.
 */
static void dfs_tarjan(
    GrafoLista *g,
    int u,
    int *visitado,
    int *descoberta,
    int *low,
    int *pai,
    int *tempo,
    int *eh_articulacao,
    Aresta *pontes,
    int *n_pontes
)
{
    int filhos = 0;
    visitado[u] = 1;
    descoberta[u] = low[u] = (*tempo)++;

    for (No *p = g->adj[u]; p != NULL; p = p->prox) {
        int v = p->destino;

        if (!visitado[v]) {
            filhos++;
            pai[v] = u;

            dfs_tarjan(
                g, v, visitado, descoberta, low, pai,
                tempo, eh_articulacao, pontes, n_pontes
            );

            if (low[v] < low[u])
                low[u] = low[v];

            if (eh_articulacao != NULL) {
                if (pai[u] == -1 && filhos > 1)
                    eh_articulacao[u] = 1;

                if (pai[u] != -1 && low[v] >= descoberta[u])
                    eh_articulacao[u] = 1;
            }

            if (pontes != NULL && low[v] > descoberta[u]) {
                pontes[*n_pontes].origem = u;
                pontes[*n_pontes].destino = v;
                (*n_pontes)++;
            }
        } else if (v != pai[u]) {
            if (descoberta[v] < low[u])
                low[u] = descoberta[v];
        }
    }
}

int *dfs_articulacoes(GrafoLista *g, int *tamanho)
{
    if (g == NULL || tamanho == NULL)
        return NULL;

    *tamanho = 0;

    if (g->n == 0)
        return NULL;

    int *visitado = calloc(g->n, sizeof(int));
    int *descoberta = malloc(g->n * sizeof(int));
    int *low = malloc(g->n * sizeof(int));
    int *pai = malloc(g->n * sizeof(int));
    int *eh_articulacao = calloc(g->n, sizeof(int));

    if (visitado == NULL || descoberta == NULL || low == NULL ||
        pai == NULL || eh_articulacao == NULL) {
        free(visitado);
        free(descoberta);
        free(low);
        free(pai);
        free(eh_articulacao);
        return NULL;
    }

    for (int i = 0; i < g->n; i++)
        pai[i] = -1;

    int tempo = 0;

    for (int i = 0; i < g->n; i++) {
        if (!visitado[i]) {
            dfs_tarjan(
                g, i, visitado, descoberta, low, pai,
                &tempo, eh_articulacao, NULL, NULL
            );
        }
    }

    int *resultado = malloc(g->n * sizeof(int));

    if (resultado == NULL) {
        free(visitado);
        free(descoberta);
        free(low);
        free(pai);
        free(eh_articulacao);
        return NULL;
    }

    for (int i = 0; i < g->n; i++) {
        if (eh_articulacao[i]) {
            resultado[*tamanho] = i;
            (*tamanho)++;
        }
    }

    free(visitado);
    free(descoberta);
    free(low);
    free(pai);
    free(eh_articulacao);

    return resultado;
}

Aresta *detectar_pontes(GrafoLista *g, int *tamanho)
{
    if (g == NULL || tamanho == NULL)
        return NULL;

    *tamanho = 0;

    if (g->n == 0)
        return NULL;

    int *visitado = calloc(g->n, sizeof(int));
    int *descoberta = malloc(g->n * sizeof(int));
    int *low = malloc(g->n * sizeof(int));
    int *pai = malloc(g->n * sizeof(int));

    /* O numero de pontes eh no maximo n - 1 (formam uma floresta) */
    Aresta *pontes = malloc(g->n * sizeof(Aresta));

    if (visitado == NULL || descoberta == NULL || low == NULL ||
        pai == NULL || pontes == NULL) {
        free(visitado);
        free(descoberta);
        free(low);
        free(pai);
        free(pontes);
        return NULL;
    }

    for (int i = 0; i < g->n; i++)
        pai[i] = -1;

    int tempo = 0;
    int n_pontes = 0;

    for (int i = 0; i < g->n; i++) {
        if (!visitado[i]) {
            dfs_tarjan(
                g, i, visitado, descoberta, low, pai,
                &tempo, NULL, pontes, &n_pontes
            );
        }
    }

    free(visitado);
    free(descoberta);
    free(low);
    free(pai);

    *tamanho = n_pontes;

    if (n_pontes == 0) {
        free(pontes);
        return NULL;
    }

    return pontes;
}