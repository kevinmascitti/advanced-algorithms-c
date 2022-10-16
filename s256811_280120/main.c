/*_______MATRICOLA s256811______MASCITTI KEVIN________*/

#include <stdio.h>
#include <stdlib.h>
#include "graph.h"

int main(int argc, char *argv[])
{
    int k=-1, j=-1;
    FILE *fin;
    if(argc!=2)
        return -1;
    fin=fopen(argv[1], "r");
    if(fin==NULL)
        return -2;
    Graph G;
    G=GRAPHload(fin);
    GRAPHstore(G, stdout);

    while(k<0){
        printf("\nInserisci un numero k >= 0 per determinare se il grafo e' un k-core\ne individuare l'insieme dei vertici che fanno parte del K-core.\n");
        scanf("%d", &k);
    }
    Kcore(G, k);
    printf("\n");

    while(j<1){
        printf("Inserisci un numero j >= 1 per determinare se il grafo e' un j-edge-connected\ne individuare un insieme di archi a cardinalita' j.\n");
        scanf("%d", &j);
    }
    EDGEconnected(G, j);

    GRAPHfree(G);

    return 0;
}
