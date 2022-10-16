#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "graph.h"

int main(int argc, char *argv[])
{   if(argc!=2) return -1;
    int opzione=1, generato=0, i;
    char words[3][30];
    Graph G;
    FILE *fp=fopen(argv[1], "r");
    G=GRAPHload(fp);
    GRAPHstore(G, stdout);
    printf("\n");
    fclose(fp);

    while(opzione!=0){
        printf("Scegli opzione:\n0 Interrompi il programma.\n1 Elenco in ordine alfabetico di vertici e archi.\n");
        printf("2 Verifica di adiacenza a coppie.\n3 Generatore di lista di adiacenze.\n\n");
        scanf("%d", &opzione);
        switch(opzione){
            case 0: return 0;
            case 1: GRAPHStampaOrdinato(G);
                    break;
            case 2: printf("Inserisci i 3 nodi da analizzare:\n");
                    for(i=0; i<3; i++)
                        scanf("%s", words[i]);
                    GRAPHverifyM(G, words);
                    if(generato)
                        GRAPHverifyL(G, words);
                    break;
            case 3: GRAPHgenerateLadj(G);
                    GRAPHprintLadj(G);
                    generato=1;
                    break;
            default:    printf("Opzione non valida.\nRiprova.\n");
                        break;
        }
    }
    GRAPHfree(G);
    return 0;
}
