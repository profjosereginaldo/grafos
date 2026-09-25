#include <stdlib.h>
#include "grafo_lista.h"

GrafoLista *criar_grafo_lista(int n) {
    GrafoLista *g = malloc(sizeof(GrafoLista));
    g->n = n;
    g->adj = malloc(n * sizeof(No *));
    for (int i = 0; i < n; i++) {
        g->adj[i] = NULL;
    }
    return g;
}

static void inserir_direcionado(GrafoLista *g, int origem, int destino) {
    No *novo = malloc(sizeof(No));
    novo->destino = destino;
    novo->prox = g->adj[origem];
    g->adj[origem] = novo;
}

void inserir_aresta_lista(GrafoLista *g, int origem, int destino) {
    if (origem < 0 || origem >= g->n || destino < 0 || destino >= g->n) return;
    inserir_direcionado(g, origem, destino);
    inserir_direcionado(g, destino, origem);
}

static void remover_direcionado(GrafoLista *g, int origem, int destino) {
    No *atual = g->adj[origem];
    No *anterior = NULL;
    while (atual != NULL) {
        if (atual->destino == destino) {
            if (anterior == NULL) {
                g->adj[origem] = atual->prox;
            } else {
                anterior->prox = atual->prox;
            }
            free(atual);
            return;
        }
        anterior = atual;
        atual = atual->prox;
    }
}

void remover_aresta_lista(GrafoLista *g, int origem, int destino) {
    if (origem < 0 || origem >= g->n || destino < 0 || destino >= g->n) return;
    remover_direcionado(g, origem, destino);
    remover_direcionado(g, destino, origem);
}

int grau_lista(const GrafoLista *g, int vertice) {
    if (vertice < 0 || vertice >= g->n) return -1;
    int grau = 0;
    No *atual = g->adj[vertice];
    while (atual != NULL) {
        grau++;
        atual = atual->prox;
    }
    return grau;
}

int sao_adjacentes_lista(const GrafoLista *g, int origem, int destino) {
    if (origem < 0 || origem >= g->n || destino < 0 || destino >= g->n) return 0;
    No *atual = g->adj[origem];
    while (atual != NULL) {
        if (atual->destino == destino) return 1;
        atual = atual->prox;
    }
    return 0;
}

void liberar_grafo_lista(GrafoLista *g) {
    if (!g) return;
    for (int i = 0; i < g->n; i++) {
        No *atual = g->adj[i];
        while (atual != NULL) {
            No *tmp = atual;
            atual = atual->prox;
            free(tmp);
        }
    }
    free(g->adj);
    free(g);
}