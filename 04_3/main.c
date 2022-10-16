#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>
#define MAX 30

void cercaRegexp(char *src, char *regexp);

int main()
{
    int i=0, j=0, lung=0;
    char src[MAX]="adrArdeicalBrem", regexp[MAX]="[^bcdEa].d\a[aeiou]ca.\A";
    char *occ;
    char *copia;

//creo una copia di src affinche' non venga modificata la stringa originale nella funzione
    copia = (char*) calloc ( strlen(src)+1, sizeof(char) );
    strcpy(copia, src);
    cercaRegexp(copia, regexp);


    return 0;
}

/*
la funzione cercaRegexp analizza l'espressione regolare e la confronta,
carattere per carattere, con la stringa sorgente in cui cercare.
Inizialmente viene calcolata la lunghezza dell'ipotetica parola corrispondente
all'espressione regolare, che deve essere presente nella stringa sorgente,
in quanto l'espressione regolare e' formata da gruppi di caratteri che
corrisponderebbero ad un unico carattere nella stringa sorgente
(es: parentesi quadre, apici, ...).
*/

void cercaRegexp(char *src, char *regexp){
    int i=0, j=0, k=0, flag=0, count, diff, lung=0;
    char c1, c2, a, occ[MAX];
    strcpy(occ, src);

//calcolo l'effettivo numero totale di caratteri dell'espressione regolare
    for(i=0; i<strlen(regexp); i++){
        c1=regexp[i];
        if(isalpha(regexp[i]) || regexp[i]=='.')
            lung++;
        else if(regexp[i]=='\a')
            lung++;
        else if(regexp[i]=='\A')
            lung++;
        else if(regexp[i]=='['){
            lung++;
            while(regexp[i]!=']'){
                i++;
                c1=regexp[i];
            }
        }
    }

    diff=strlen(src)-lung;

/*
analisi carattere per carattere:
scandisco la stringa sorgente fino al valore di diff (max valore
in cui si possa trovare l'espressione regolare). Utilizzo l'indice i
per memorizzare la posizone di partenza dalla quale inizio a scandire
la stringa sorgente; uso j per analizzare il carattere j-esimo dell'espressione
regolare e k per analizzare il carattere k-esimo della stringa sorgente,
a partire dalla posizione di partenza di quel determinato ciclo
(inizializzazione a k=i).
*/
    for(i=0; i<=diff; i++){
        flag=0;
        count=0;
        for(j=0, k=i; j<strlen(regexp); j++, k++){
            flag=0;
            c1=regexp[j];
            c2=src[k];
            if (isalpha(regexp[j]) && regexp[j]==src[k])
                flag=1;
            else if (regexp[j]=='.')
                flag=1;
            else if (regexp[j]=='\a'){
                if(islower(src[k])){
                    flag=1;
                }
                else
                    break;
            }
            else if (regexp[j]=='\A'){
                if(isupper(src[k])){
                    flag=1;
                }
                else
                    break;
            }

/*se trovo una parentesi quadra seguita da un carattere alfabetico, effettuo un controllo su tutti
i caratteri nelle parentesi: se almeno uno di essi e' uguale a quello corrispondente della striga sorgente, flag=1 (carattere trovato)
altrimenti rimane a 0. In modo analogo (ma con controllo contrario sul flag) effettuo il confronto, se trovo una parentesi quadra seguita da un apice ^.*/

            else if (regexp[j]=='['){
                j++;
                c1=regexp[j];
                if(isalpha(regexp[j])){
                    while(regexp[j] != ']'){
                        a=regexp[j];
                        if(src[k]==a)
                            flag=1;
                        j++;
                    }
                }
                else if(regexp[j]=='^'){
                    j++;
                    flag=1;
                    while(regexp[j] != ']'){
                        a=regexp[j];
                        if(src[k]==a)
                            flag=0;
                        j++;
                    }
                }
            }

/*se alla fine del confronto i due caratteri sono uguali (flag=1), aumento il contatore che, se uguale a lung,
indica che ho trovato l'intera espressione regolare nella stringa sorgente, percio' salvo la parola corrispondente
all'espressione regolare in un vettore di caratteri occorrenza e stampo la soluzione*/

            if(flag==1){
                count++;
                if(count==lung){
                    int pos=i;
                    for(j=0; j<lung; i++, j++)
                        src[j]=occ[i];
                    src[j]='\0';
                    printf("%s trovata in %s in posizione %d della stringa %s\n", regexp, src, pos, occ);
                    return;
                }
            }
            else
                break;
        }
    }

    printf("Nessuna corrispondenza trovata.\n");
    return;
}
