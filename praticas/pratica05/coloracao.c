#include <stdlib.h>
#include "coloracao.h"

/*
 * Colore os vertices na ordem dada em 'ordem' (array de tamanho g->n
 * com uma permutacao dos vertices 0..n-1). Retorna array de cores
 * (indexado pelo vertice original) e o numero de cores usadas em
 * *num_cores. Retorna NULL em caso de falha de alocacao.
 */
static int *colorir_na_ordem(GrafoLista *g, const int *ordem, int *num_cores)
{
    int *cor = malloc(g->n * sizeof(int));
    int *cor_usada = malloc(g->n * sizeof(int));

    if (cor == NULL || cor_usada == NULL) {
        free(cor);
        free(cor_usada);
        return NULL;
    }

    for (int i = 0; i < g->n; i++)
        cor[i] = -1;

    int maior_cor = -1;

    for (int i = 0; i < g->n; i++) {
        int u = ordem[i];

        for (int j = 0; j <= maior_cor; j++)
            cor_usada[j] = 0;

        for (No *p = g->adj[u]; p != NULL; p = p->prox) {
            int v = p->destino;

            if (cor[v] != -1 && cor[v] <= maior_cor)
                cor_usada[cor[v]] = 1;
        }

        int c = 0;

        while (c <= maior_cor && cor_usada[c])
            c++;

        cor[u] = c;

        if (c > maior_cor)
            maior_cor = c;
    }

    free(cor_usada);

    *num_cores = maior_cor + 1;
    return cor;
}

int *coloracao_gulosa(GrafoLista *g, int *num_cores)
{
    if (g == NULL || num_cores == NULL)
        return NULL;

    *num_cores = 0;

    if (g->n == 0)
        return NULL;

    int *ordem = malloc(g->n * sizeof(int));

    if (ordem == NULL)
        return NULL;

    /* Ordem arbitraria: a propria ordem natural dos vertices */
    for (int i = 0; i < g->n; i++)
        ordem[i] = i;

    int *cor = colorir_na_ordem(g, ordem, num_cores);

    free(ordem);
    return cor;
}

int *coloracao_welsh_powell(GrafoLista *g, int *num_cores)
{
    if (g == NULL || num_cores == NULL)
        return NULL;

    *num_cores = 0;

    if (g->n == 0)
        return NULL;

    int *ordem = malloc(g->n * sizeof(int));
    int *graus = malloc(g->n * sizeof(int));

    if (ordem == NULL || graus == NULL) {
        free(ordem);
        free(graus);
        return NULL;
    }

    for (int i = 0; i < g->n; i++) {
        ordem[i] = i;
        graus[i] = grau_lista(g, i);
    }

    /* Ordenacao por selecao, decrescente pelo grau (n de pratica costuma ser pequeno) */
    for (int i = 0; i < g->n - 1; i++) {
        int maior = i;

        for (int j = i + 1; j < g->n; j++) {
            if (graus[ordem[j]] > graus[ordem[maior]])
                maior = j;
        }

        if (maior != i) {
            int tmp = ordem[i];
            ordem[i] = ordem[maior];
            ordem[maior] = tmp;
        }
    }

    free(graus);

    int *cor = colorir_na_ordem(g, ordem, num_cores);

    free(ordem);
    return cor;
}

int eh_bipartido(GrafoLista *g)
{
    if (g == NULL)
        return 0;

    if (g->n == 0)
        return 1;

    int *cor = malloc(g->n * sizeof(int));
    int *fila = malloc(g->n * sizeof(int));

    if (cor == NULL || fila == NULL) {
        free(cor);
        free(fila);
        return 0;
    }

    for (int i = 0; i < g->n; i++)
        cor[i] = -1;

    int bipartido = 1;

    for (int inicio = 0; inicio < g->n && bipartido; inicio++) {
        if (cor[inicio] != -1)
            continue;

        cor[inicio] = 0;

        int frente = 0, fundo = 0;
        fila[fundo++] = inicio;

        while (frente < fundo && bipartido) {
            int u = fila[frente++];

            for (No *p = g->adj[u]; p != NULL; p = p->prox) {
                int v = p->destino;

                if (cor[v] == -1) {
                    cor[v] = 1 - cor[u];
                    fila[fundo++] = v;
                } else if (cor[v] == cor[u]) {
                    bipartido = 0;
                    break;
                }
            }
        }
    }

    free(cor);
    free(fila);

    return bipartido;
}