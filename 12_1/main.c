#include <stdio.h>
#include <stdlib.h>
#include "Graph.h"

int main()
{
    Graph G;
    int k, massimo=0;
    Edge *a, *sol, *sol_max;
    FILE *fin=fopen("grafo2.txt", "r");

    G=GRAPHload(fin);
    fclose(fin);
    GRAPHstore(G, stdout);
    a=malloc(edges(G)*sizeof(Edge));
    GRAPHedges(G, a);
    sol=malloc(edges(G)*sizeof(Edge));
    sol_max=malloc(edges(G)*sizeof(Edge));

    if(GRAPHciclico(G)){
//finche' il massimo e' pari a 0, ovvero finche' non trovo un insieme, che sara' di conseguenza quello a cardinalita' minima
        for(k=1; k<edges(G) && massimo==0; k++)
            comb_sempl(0, a, sol, k, 0, G, &massimo, sol_max);
        fprintf(stdout, "\nL'insieme di archi a cardinalita' %d e di peso massimo da rimuovere dal grafo per ottenere un DAG sono:\n\n", k-1);
        EDGESstore(sol_max, k-1, G, stdout);
        rimuoviArchi(G, k-1, sol_max);
        fprintf(stdout, "Il DAG aggiornato e':\n");
        GRAPHstore(G, stdout);
        GRAPHedges(G, a);
    }
    else{
        fprintf(stdout, "Il grafo e' gia' un DAG.\n");
    }

    for(int j = 0; j < vertex(G); j++){
        DAGmaxPath(G, j);
    }


    free(a);
    free(sol);
    free(sol_max);
    GRAPHfree(G);

    return 0;
}
