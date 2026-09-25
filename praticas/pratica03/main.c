#include <stdio.h>
#include <stdlib.h>

#include "../pratica01/grafo_lista.h"
#include "dag.h"

static void inserir_arco(GrafoLista *g, int origem, int destino)
{
    No *novo = malloc(sizeof(No));

    if (novo == NULL)
        return;

    novo->destino = destino;
    novo->prox = g->adj[origem];
    g->adj[origem] = novo;
}

static void imprimir_ordem(const char *nome, int *ordem, int tamanho)
{
    printf("%s: ", nome);

    if (ordem == NULL) {
        printf("Nao foi possivel ordenar (o grafo possui ciclo).\n");
        return;
    }

    for (int i = 0; i < tamanho; i++) {
        printf("%d", ordem[i]);

        if (i < tamanho - 1)
            printf(" -> ");
    }

    printf("\n");
}

int main(void)
{
    /*
     * Grafo direcionado aciclico:
     *
     * 0 -> 1
     * |    |
     * v    v
     * 2 -> 3 -> 4 -> 5
     */

    GrafoLista *g = criar_grafo_lista(6);

    if (g == NULL) {
        printf("Erro ao criar o grafo.\n");
        return 1;
    }

    /*
     * Insercao de arcos direcionados.
     * Diferente de inserir_aresta_lista(), que cria
     * uma aresta nos dois sentidos.
     */
    inserir_arco(g, 0, 1);
    inserir_arco(g, 0, 2);
    inserir_arco(g, 1, 3);
    inserir_arco(g, 2, 3);
    inserir_arco(g, 3, 4);
    inserir_arco(g, 4, 5);

    printf("=== ORDENACAO TOPOLOGICA ===\n");

    int tamanho_kahn = 0;
    int *ordem_kahn = ordenacao_topologica_kahn(
        g,
        &tamanho_kahn
    );

    imprimir_ordem(
        "Kahn",
        ordem_kahn,
        tamanho_kahn
    );

    int tamanho_dfs = 0;
    int *ordem_dfs = ordenacao_topologica_dfs(
        g,
        &tamanho_dfs
    );

    imprimir_ordem(
        "DFS",
        ordem_dfs,
        tamanho_dfs
    );

    printf("\n=== VERIFICACAO ===\n");

    if (eh_dag(g)) {
        printf("O grafo e um DAG.\n");
    } else {
        printf("O grafo possui ciclo.\n");
    }

    free(ordem_kahn);
    free(ordem_dfs);

    liberar_grafo_lista(g);

    return 0;
}