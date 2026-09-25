#include <stdio.h>
#include <stdlib.h>

#include "../pratica01/grafo_lista.h"
#include "conectividade.h"
#include "planaridade.h"

static void imprimir_articulacoes(int *vertices, int tamanho)
{
    printf("Vertices de articulacao: ");

    if (tamanho == 0) {
        printf("nenhum\n");
        return;
    }

    for (int i = 0; i < tamanho; i++) {
        printf("%d", vertices[i]);

        if (i < tamanho - 1)
            printf(", ");
    }

    printf("\n");
}

static void imprimir_pontes(Aresta *pontes, int tamanho)
{
    printf("Pontes: ");

    if (tamanho == 0) {
        printf("nenhuma\n");
        return;
    }

    for (int i = 0; i < tamanho; i++) {
        printf("(%d-%d)", pontes[i].origem, pontes[i].destino);

        if (i < tamanho - 1)
            printf(", ");
    }

    printf("\n");
}

int main(void)
{
    /*
     * Grafo nao-direcionado com um vertice de articulacao (1) e uma ponte (1-3):
     *
     * 0 - 1 - 2
     *     |
     *     3 - 4
     */

    GrafoLista *g = criar_grafo_lista(5);

    if (g == NULL) {
        printf("Erro ao criar o grafo.\n");
        return 1;
    }

    inserir_aresta_lista(g, 0, 1);
    inserir_aresta_lista(g, 1, 2);
    inserir_aresta_lista(g, 1, 3);
    inserir_aresta_lista(g, 3, 4);

    printf("=== CONECTIVIDADE ===\n");

    int n_articulacoes = 0;
    int *articulacoes = dfs_articulacoes(g, &n_articulacoes);
    imprimir_articulacoes(articulacoes, n_articulacoes);
    free(articulacoes);

    int n_pontes = 0;
    Aresta *pontes = detectar_pontes(g, &n_pontes);
    imprimir_pontes(pontes, n_pontes);
    free(pontes);

    printf("\n=== PLANARIDADE ===\n");

    printf(
        "Satisfaz Euler (m <= 3n-6): %s\n",
        eh_planar_euler(g) ? "sim" : "nao"
    );

    printf(
        "Contem K5 ou K3,3 (heuristica, n<=10): %s\n",
        contem_k5_ou_k33(g) ? "sim" : "nao"
    );

    printf(
        "Classificacao final: %s\n",
        eh_planar(g) ? "provavelmente planar" : "nao planar"
    );

    liberar_grafo_lista(g);

    return 0;
}