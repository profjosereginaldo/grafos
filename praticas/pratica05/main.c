#include <stdio.h>
#include <stdlib.h>

#include "../pratica01/grafo_lista.h"
#include "coloracao.h"

static void imprimir_coloracao(const char *nome, int *cor, int n, int num_cores)
{
    printf("%s (usou %d cor(es)):\n", nome, num_cores);

    if (cor == NULL) {
        printf("  Nao foi possivel colorir.\n");
        return;
    }

    for (int i = 0; i < n; i++)
        printf("  vertice %d -> cor %d\n", i, cor[i]);
}

int main(void)
{
    /*
     * Grafo nao-direcionado (ciclo impar + vertice extra):
     *
     * 0 - 1
     * |   |
     * 3 - 2
     *     |
     *     4
     *
     * (0,1,2,3 formam um ciclo par -> subgrafo bipartido;
     *  vertice 4 pendurado em 2)
     */

    GrafoLista *g = criar_grafo_lista(5);

    if (g == NULL) {
        printf("Erro ao criar o grafo.\n");
        return 1;
    }

    inserir_aresta_lista(g, 0, 1);
    inserir_aresta_lista(g, 1, 2);
    inserir_aresta_lista(g, 2, 3);
    inserir_aresta_lista(g, 3, 0);
    inserir_aresta_lista(g, 2, 4);

    printf("=== COLORACAO ===\n");

    int num_cores_gulosa = 0;
    int *cor_gulosa = coloracao_gulosa(g, &num_cores_gulosa);
    imprimir_coloracao("Gulosa (ordem natural)", cor_gulosa, g->n, num_cores_gulosa);
    free(cor_gulosa);

    printf("\n");

    int num_cores_wp = 0;
    int *cor_wp = coloracao_welsh_powell(g, &num_cores_wp);
    imprimir_coloracao("Welsh-Powell", cor_wp, g->n, num_cores_wp);
    free(cor_wp);

    printf("\n=== BIPARTICAO ===\n");
    printf(
        "O grafo e bipartido: %s\n",
        eh_bipartido(g) ? "sim" : "nao"
    );

    liberar_grafo_lista(g);

    return 0;
}