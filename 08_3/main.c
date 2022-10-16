#include "personaggi.h"
#include "inventario.h"

int main()
{
    Pg_t pers;
    tabPg_t structpg;
    tabPg_t *tabPg=&structpg;
    tabInv_t structinv;
    tabInv_t *tabInv=&structinv;
    tabPg->headPg=NULL;
    tabPg->tailPg=NULL;
    tabPg->nPg=0;
    tabPg=scriviPersonaggi("pg.txt", tabPg);
    tabInv=scriviInventario("inventario.txt", tabInv);
    stampaTUTTO(tabPg, tabInv);
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
            case 1: tabPg->headPg=aggiungi(tabPg->headPg);
                    tabPg->tailPg=findtail(tabPg->headPg);
                    break;
            case 2: pers=elimina(tabPg->headPg);
                    if( !eqPG(pers, PGsetvoid()) ){
                        printf("\nElemento eliminato:\n\n");
                        stampaRiga_Pg(pers);
                        tabPg->tailPg=findtail(tabPg->headPg);
                    }
                    else
                        printf("\nPersonaggio non trovato nella lista.\n\n");
                    break;
            case 3: agg_eq(tabPg->headPg, tabInv->vettInv, tabInv->nInv);
                    tabPg->tailPg=findtail(tabPg->headPg);
                    break;
            case 4: rim_eq(tabPg->headPg);
                    tabPg->tailPg=findtail(tabPg->headPg);
                    break;
            case 5: stampaStats(tabPg->headPg);
                    break;
            case 6: stampaTUTTO(tabPg, tabInv);
                    break;
            case 7: printf("\nTesta:\n");
                    stampaRiga_Pg(tabPg->headPg->val);
                    tabPg->tailPg=findtail(tabPg->headPg);
                    printf("\nCoda:\n");
                    stampaRiga_Pg(tabPg->tailPg->val);
                    break;
            default:    opzione=1;
                        printf("\nComando non disponibile.\n");
                        break;
        }
    }
    free(tabInv->vettInv);
    return 0;
}
