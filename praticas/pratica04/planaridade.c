#include <stddef.h>
#include "planaridade.h"

static int contar_arestas(GrafoLista *g)
{
    int soma_graus = 0;

    for (int i = 0; i < g->n; i++)
        soma_graus += grau_lista(g, i);

    return soma_graus / 2;
}

static int contar_bits(int x)
{
    int c = 0;

    while (x) {
        c += x & 1;
        x >>= 1;
    }

    return c;
}

/* Tenta dividir os 6 vertices em dois grupos de 3 formando K3,3 */
static int forma_k33(GrafoLista *g, int vertices[6])
{
    for (int mascara = 1; mascara < 63; mascara++) {
        if (contar_bits(mascara) != 3)
            continue;

        int grupoA[3], grupoB[3];
        int ia = 0, ib = 0;

        for (int i = 0; i < 6; i++) {
            if (mascara & (1 << i))
                grupoA[ia++] = vertices[i];
            else
                grupoB[ib++] = vertices[i];
        }

        /* evita processar a particao espelhada (A,B) == (B,A) */
        if (grupoA[0] > grupoB[0])
            continue;

        int completo = 1;

        for (int i = 0; i < 3 && completo; i++) {
            for (int j = 0; j < 3; j++) {
                if (!sao_adjacentes_lista(g, grupoA[i], grupoB[j])) {
                    completo = 0;
                    break;
                }
            }
        }

        if (completo)
            return 1;
    }

    return 0;
}

static int contem_k5(GrafoLista *g)
{
    if (g->n < 5)
        return 0;

    int vertices[5];

    for (int a = 0; a < g->n; a++) {
        for (int b = a + 1; b < g->n; b++) {
            for (int c = b + 1; c < g->n; c++) {
                for (int d = c + 1; d < g->n; d++) {
                    for (int e = d + 1; e < g->n; e++) {
                        vertices[0] = a;
                        vertices[1] = b;
                        vertices[2] = c;
                        vertices[3] = d;
                        vertices[4] = e;

                        int completo = 1;

                        for (int i = 0; i < 5 && completo; i++) {
                            for (int j = i + 1; j < 5; j++) {
                                if (!sao_adjacentes_lista(g, vertices[i], vertices[j])) {
                                    completo = 0;
                                    break;
                                }
                            }
                        }

                        if (completo)
                            return 1;
                    }
                }
            }
        }
    }

    return 0;
}

static int contem_k33(GrafoLista *g)
{
    if (g->n < 6)
        return 0;

    int vertices[6];

    for (int a = 0; a < g->n; a++) {
        for (int b = a + 1; b < g->n; b++) {
            for (int c = b + 1; c < g->n; c++) {
                for (int d = c + 1; d < g->n; d++) {
                    for (int e = d + 1; e < g->n; e++) {
                        for (int f = e + 1; f < g->n; f++) {
                            vertices[0] = a;
                            vertices[1] = b;
                            vertices[2] = c;
                            vertices[3] = d;
                            vertices[4] = e;
                            vertices[5] = f;

                            if (forma_k33(g, vertices))
                                return 1;
                        }
                    }
                }
            }
        }
    }

    return 0;
}

int eh_planar_euler(GrafoLista *g)
{
    if (g == NULL)
        return 0;

    if (g->n < 3)
        return 1; /* grafos com menos de 3 vertices sao sempre planares */

    int m = contar_arestas(g);

    /* Condicao necessaria (mas nao suficiente) de planaridade */
    return m <= 3 * g->n - 6;
}

int contem_k5_ou_k33(GrafoLista *g)
{
    if (g == NULL)
        return 0;

    if (g->n > 10)
        return -1; /* heuristica de forca bruta definida apenas para n <= 10 */

    return contem_k5(g) || contem_k33(g);
}

int eh_planar(GrafoLista *g)
{
    if (g == NULL)
        return 0;

    if (!eh_planar_euler(g))
        return 0;

    if (g->n <= 10 && contem_k5_ou_k33(g))
        return 0;

    return 1; /* provavelmente planar (heuristica, nao eh prova formal) */
}