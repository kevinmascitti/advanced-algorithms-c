#include "pgList.h"
#include "personaggi.h"
#include "vettInv.h"
#include <stdio.h>
#include <stdlib.h>

int main()
{
    Pg_t pers;
    pgList_t pgList=pgList_init(); //creazione e allocazione dei vari ADT di prima classe
    vettInv_t vettInv=vettInv_init();
    vettEquip_t vettEquip=vettEquip_init();

    scriviPersonaggi("pg.txt", pgList);
    scriviInventario("inventario.txt", vettInv);
    stampaTUTTO(pgList, vettInv);
    int opzione = 1;
    while(opzione!=0){
        printf("\nScegli un'opzione.\n");
        printf("1 Aggiungi un nuovo personaggio.\n");
        printf("2 Elimina un personaggio.\n");
        printf("3 Aggiungi un oggetto all'equipaggiamento di un personaggio.\n");
        printf("4 Rimuovi un oggetto dell'equipaggiamento di un personaggio.\n");
        printf("5 Calcola le statistiche attuali di un personaggio.\n");
        printf("6 Stampa la lista aggiornata dei personaggi e dell'inventario.\n"); //opzione extra
        printf("7 Stampa la testa della lista e la coda.\n");
        printf("0 Per interrompere il programma.\n");
        scanf("%d", &opzione);

        switch(opzione){
            case 0: printf("\nFine del programma.\n");
                    return 0;
            case 1: aggiungi(pgList, vettInv);
                    findtail(pgList);
                    break;
            case 2: pers=elimina(pgList);
                    if( !eqPG(pers, PGsetvoid(), vettInv) ){
                        printf("\nElemento eliminato:\n\n");
                        stampaRiga_Pg(pers, vettInv);
                        findtail(pgList);
                    }
                    else
                        printf("\nPersonaggio non trovato nella lista.\n\n");
                    break;
            case 3: agg_eq(pgList, vettInv);
                    break;
            case 4: rim_eq(pgList, vettInv);
                    break;
            case 5: stampaStats(pgList, vettInv);
                    break;
            case 6: stampaTUTTO(pgList, vettInv);
                    break;
            case 7: printf("\nTesta:\n");
                    stampaTesta_Pg(pgList, vettInv);
                    findtail(pgList);
                    printf("\nCoda:\n");
                    stampaCoda_Pg(pgList, vettInv);
                    printf("\n");
                    break;
            default:    opzione=1;
                        printf("\nComando non disponibile.\n");
                        break;
        }
    }

    //liberazione dei vettori prima inizializzati e allocati dinamicamente nelle funzioni presenti in altri .c
    liberaInv(vettInv);
    liberaList(pgList);
    liberaEquip(vettEquip);

    return 0;
}

