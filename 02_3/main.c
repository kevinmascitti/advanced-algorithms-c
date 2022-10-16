#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX 20

int check(char parola[], char parola2[], int totmaiusc, int oldindicemaiusc[], int newindicemaiusc[], int *oldmaiusc, int *newmaiusc);

int main(){

    int i=0, j=0, k=0, w=0, lettura=0, totseq=0, maiusc_seq=0, pos=0, indice=0, ind_maiusc[MAX], ind2_maiusc[MAX], pos_seq[MAX],
        sx_maiusc=0, dx_maiusc=0, *oldmaiusc=&sx_maiusc, *newmaiusc=&dx_maiusc;
    char seq[MAX][6], tmp[MAX], restoparola[MAX];
    FILE *fp1;
    FILE *fp2;

/*salvo le sequenze in un vettore di stringhe, ricordando che il primo valore e' il numero totale di sequenze contenute nel file*/
    fp1=fopen("sequenze.txt","r");
    while(fgets(tmp,"%s",fp1)!=NULL){
        lettura++;
        if(lettura==1){
            sscanf(tmp,"%d",&totseq);
        }
        else{
            sscanf(tmp,"%s",seq[i]);
            i++;
        }
    }
    fclose(fp1);

    fp2=fopen("testo.txt","r");
    for(i=0;i<totseq;i++){
        pos=0;
        maiusc_seq=0;                               //maiusc_seq indica il numero totale di maiuscole all'interno della sequenza analizzata

/*Converto in minuscole tutte le lettere della sequenza da ricercare nel testo,
ricordandone gli indici dove erano presenti le maiuscole. Lo faccio
per effettuare correttamente il controllo strstr e per
stampare in seguito la sequenza originaria con le maiuscole al proprio posto.*/
        for(w=0;w<strlen(seq[i]);w++){
            if(isupper(seq[i][w])){
               seq[i][w]=tolower(seq[i][w]);
               pos_seq[k]=w;
               k++;
               maiusc_seq++;
            }
        }

        while(fscanf(fp2,"%s",tmp)!=EOF){           //confronto la parola e il testo intero
            pos++;
            indice=1;
            j=0;

            while(indice!=0){   //finche' non smetto di trovare segni di punteggiatura nella parola da testo
                *newmaiusc=0;

/*trasformo le maiuscole della parola da testo in minuscole, come ho fatto per la sequenza precedentemente*/
                for(k=0; k<strlen(tmp); k++){
                    if(isupper(tmp[k])!=0){
                        tmp[k]=tolower(tmp[k]);
                        ind_maiusc[j]=k;
                        j++;
                        sx_maiusc=j;                //sx_maiusc indica il numero di maiuscole trovate in una parola da testo
                    }
                }

/*Ricerco la posizone del segno di punteggiatura all'interno della parola e divido tmp in due stringhe diverse:
una raccoglie la parola a sinistra del segno (tmp), l'altra quella a destra (restoparola).
Inoltre salvo gli indici delle maiuscole presenti nella stringa a sinistra e a destra del segno in
2 vettori diversi: ind_maiusc e ind2_maiusc, per poi stampare le parole come erano originariamente.
In oldmaiusc e newmaiusc sono utilizzati per ritornare nel main il numero ttoale di maiuscole
della stringa a sinistra e a destra del segno di punteggiatura.
Indice rappresenta la posizione del segno di punteggiatura.*/
                indice=check(tmp,restoparola,sx_maiusc,ind_maiusc,ind2_maiusc,oldmaiusc,newmaiusc);

/*se l'ultima lettera della parola e' un segno di punteggiatura seguita da uno spazio, lo elimino per non stamparlo*/
                if(ispunct(tmp[strlen(tmp)-1])!=0){
                    tmp[strlen(tmp)-1]='\0';
                }

/*se trovo la parola cercata, faccio ritornare maiuscole le lettere che originariamente erano tali,
sia delle parole del testo, sia della parola da confrontare*/
                if(strstr(tmp,seq[i])!=0){
                    for(k=0;k<sx_maiusc;k++){
                        tmp[ind_maiusc[k]]=toupper(tmp[ind_maiusc[k]]);
                    }
                    for(w=0;w<maiusc_seq;w++){
                        seq[i][pos_seq[w]]=toupper(seq[i][pos_seq[w]]);
                    }

                    printf("La sequenza %s e' contenuta in %s, parola in posizione %d.\n", seq[i], tmp, pos);

/*riconverto le lettere della sequenza in minuscolo, così al prossimo ciclo posso eventualmente
confrontarle con quelle della prossima parola tramite la funzione check*/
                    k=0;
                    maiusc_seq=0;
                    for(w=0;w<strlen(seq[i]);w++){
                        if(isupper(seq[i][w])!=0){
                           seq[i][w]=tolower(seq[i][w]);
                           pos_seq[k]=w;
                           k++;
                           maiusc_seq++;
                        }
                    }

                }

/*se ho trovato un segno di punteggiatura e ho diviso in due la parola, aumento la posizione relativa alla parola nel testo,
in quanto una parola con segno di punteggiatura all'interno, e' in realta' formata da due parole diverse*/
                if(indice!=0){
                    pos++;
                }

/*riconverto in maiuscole le lettere della parola a destra del segno di punteggiatura*/
                for(k=0;k<dx_maiusc;k++){
                    restoparola[ind2_maiusc[k]]=toupper(restoparola[ind2_maiusc[k]]);
                }

/*Copio restoparola in tmp affinche' tmp venga ricontrollato come gia' fatto, per trovare altri eventuali
segni di punteggiatura presenti in restoparola, che non e' stata analizzata. Di conseguenza il numero totale
di maiuscole in restoparola diventa il numero totale di maiuscole in tmp*/
                strcpy(tmp,restoparola);
                sx_maiusc=dx_maiusc;
            }
        }

        printf("\n");
        rewind(fp2);
    }
    fclose(fp2);

    return 0;
}



int check(char parola[], char parola2[], int totmaiusc, int oldindicemaiusc[], int newindicemaiusc[], int *oldmaiusc, int *newmaiusc){
    int i=0, j=0, k=0, w=0, flag=0, ind=0, lungtot=0;

    lungtot=strlen(parola);

    for(i=0;i<lungtot-1;i++){
        if(ispunct(parola[i])!=0){
            flag=1;
            ind=i;
            for(i=ind+1;i<lungtot;i++){
                parola2[j]=parola[i];
                j++;
            }
            parola2[j]='\0';
            parola[ind]='\0';
            break;
        }
    }

/*controllo delle maiuscole a sinistra e a destra del segno di punteggiatura*/
    if(flag==1){
        for(k=0;k<totmaiusc;k++){
            if(oldindicemaiusc[k]>ind){
                newindicemaiusc[w]=oldindicemaiusc[k]-ind-1;    //il nuovo indice deve contare da 0, la prima posizone della nuova stringa
                oldindicemaiusc[k]=0;
                w++;
                }

        }
        *oldmaiusc=totmaiusc-w;
        *newmaiusc=w;
    }

    return ind;
}
