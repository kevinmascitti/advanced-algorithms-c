#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#include <string.h>

int main()
{
    int recodemax=0, ciclo=0, i=0, indice=0, j=0, k=0, trovato=0;
    char originale[201], codifica[101], car, restoparola[201], sequenza[51];
    char *posizione;
    FILE *fp1;
    FILE *fp2;
    FILE *fp3;
    typedef struct Diz{
        char cod[30][50+1];
        char seq[30][50+1];
    };
    struct Diz sdiz;

    fp2=fopen("dizionario.txt","r");
    while((fgets(codifica,"%s",fp2))!=NULL){
        if(ciclo==0){
            sscanf(codifica, "%d", &recodemax);
        }
        else{
            sscanf(codifica, "%s %s", sdiz.cod[ciclo-1], sdiz.seq[ciclo-1]);
        }
        ciclo++;
    }
    fclose(fp2);
    fp1=fopen("sorgente.txt","r");
    fp3=fopen("ricodificato.txt","w");

    while(fscanf(fp1, "%s%c", originale, &car)!=EOF){   /*prendo una parola dal file sorgente per analizzarla*/
        for(j=0;j<recodemax;j++){                       /*confronto la parola appena presa rispettivamente con ogni parola presente nel dizionario*/
            trovato=1;
            strcpy(sequenza,sdiz.seq[j]);

/*finche' trovato==1, continua a cercare la parola j del dizionario all'interno della parola da sorgente,
perche' essa puo' ripetersi piu' volte al suo interno*/

            while(trovato==1){
                 if(strstr(originale, sequenza)!=0){
                    posizione = strstr(originale, sequenza);
                    indice=posizione-originale;
                    trovato=1;
                    k=0;
                    for(i=indice+strlen(sequenza); i<strlen(originale); i++){
                        restoparola[k]=originale[i];
                        k++;
                    }
                    originale[indice]='\0';
                    restoparola[k]='\0';
                    strcat(originale, sdiz.cod[j]);
                    strcat(originale, restoparola);
                }
                else{
                    trovato=0;
                }
            }

        }

        /*printf("%s", originale);
        printf("%c", car);*/

        fprintf(fp3, "%s", originale);
        fprintf(fp3, "%c", car);
    }

    fclose(fp1);
    fclose(fp3);

    return 0;
}
