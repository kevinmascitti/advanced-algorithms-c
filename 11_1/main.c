#include <stdio.h>
#include <stdlib.h>
#include "titoli.h"
#include "quotazioni.h"
#define S 2

int main()
{
    char str[21];
    Quotazione quot=QUOTInit();
    Titoli lista;
    lista=TitoliInit();
    Titolo SelTitolo=TitoloInit();
    DataOra datamin, datamax;
    int operazione=1, c;

    while(operazione!=0){
        printf("Operazioni disponibili:\n");
        printf("0. Fine programma.\n");
        printf("1. Acquisisci contenuti da file.\n");
        printf("2. Ricerca un titolo azionario.\n");
        printf("3. Ricerca quotazione per un titolo gia' selezionato.\n");
        printf("4. Ricerca quotazione massima e minima in un intervallo di date per un titolo gia' selezionato.\n");
        printf("5. Ricerca quotazione massima e minima in tutto il periodo registrato per un titolo gia' selezionato.\n");
        printf("6. Bilanciamento dell'albero delle quotazioni per un titolo gia' selezionato.\n\n");
        scanf("%d", &operazione);
        switch(operazione){
                case 0: return 0;
                case 1: LeggiFile(lista);
                        break;
                case 2: if(Titoliisnull(lista)){
                            printf("Lista vuota!\n\n");
                            break;
                        }
                        printf("Inserisci il titolo:\n");
                        scanf("%s", str);
                        SelTitolo=RicercaT(lista, str);
                        if(Titoloisnull(SelTitolo)){
                            printf("Titolo non presente nella lista.\n\n");
                            break;
                        }
                        else
                            displayTitolo(SelTitolo);
                        break;
                case 3: if(Titoliisnull(lista)){
                            printf("Lista vuota!\n\n");
                            break;
                        }
                        if(Titoloisnull(SelTitolo)){
                            printf("Nessun titolo selezionato!\nInserisci il titolo:\n");
                            scanf("%s", str);
                            SelTitolo=RicercaT(lista, str);
                            if(Titoloisnull(SelTitolo)){
                                printf("Titolo non presente nella lista.\n\n");
                                break;
                            }
                            else
                                displayTitolo(SelTitolo);
                        }
                        else
                            displayTitolo(SelTitolo);
                        quot=RicercaQuot(SelTitolo);
                        QUOTstamp(quot);
                        printf("\n");
                        break;
                case 4: if(Titoliisnull(lista)){
                            printf("Lista vuota!\n\n");
                            break;
                        }
                        if(Titoloisnull(SelTitolo)){
                            printf("Nessun titolo selezionato!\nInserisci il titolo:\n");
                            scanf("%s", str);
                            SelTitolo=RicercaT(lista, str);
                            if(Titoloisnull(SelTitolo)){
                                printf("Titolo non presente nella lista.\n\n");
                                break;
                            }
                            else
                                displayTitolo(SelTitolo);
                        }
                        else
                            displayTitolo(SelTitolo);
                        inserisciDate(&datamin, &datamax);
                        QUOTstamp(BSTminT( SelTitolo, datamin ));
                        printf("\n");
                        QUOTstamp(BSTmaxT( SelTitolo, datamax ));
                        printf("\n");
                        break;
                case 5: QUOTstamp(BSTminT( SelTitolo, DATAORAInit() ));
                        printf("\n");
                        QUOTstamp(BSTmaxT( SelTitolo, DATAORAInit() ));
                        printf("\n");
                        break;
                case 6: if(Titoliisnull(lista)){
                            printf("Lista vuota!\n\n");
                            break;
                        }
                        if(Titoloisnull(SelTitolo)){
                            printf("Nessun titolo selezionato!\nInserisci il titolo:\n");
                            scanf("%s", str);
                            SelTitolo=RicercaT(lista, str);
                            if(Titoloisnull(SelTitolo)){
                                printf("Titolo non presente nella lista.\n\n");
                                break;
                            }
                            else
                                displayTitolo(SelTitolo);
                        }
                        else
                            displayTitolo(SelTitolo);
                        c=camminoT(SelTitolo);
                        if(c > S){
                            balanceT(SelTitolo);
                            printf("Albero bilanciato con successo!\n\n");
                        }
                        else
                            printf("Albero gia' bilanciato!\n\n");
                        break;
                default:    printf("Operazione non valida.\nRiprova.\n");
                            break;
        }
    }

    free(quot);
    free(SelTitolo);
    free(lista);

    return 0;
}
