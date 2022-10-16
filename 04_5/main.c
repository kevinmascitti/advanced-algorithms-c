#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 1000
#define mcod 31

typedef struct Corse{
        char cod[mcod];
        char part[mcod];
        char dest[mcod];
        int giorno;
        int mese;
        int anno;
        int ora_p;
        int min_p;
        int ora_a;
        int min_a;
        int ritardo;
};

int stampa(struct Corse **c, int tot, int ord, FILE *fp);
void ordinaData(struct Corse **d, int tot);
int orario(struct Corse *temp, struct Corse *d);
void ordinaCodice(struct Corse **d, int tot);
void ordinaPartenza(struct Corse **d, int tot);
void ordinaArrivo(struct Corse **d, int tot);
int BinSearch(struct Corse **v, int l, int r, int fine, char *key, int *firstpos, int *lastpos);
int isfirst(struct Corse **v, int indice, char *key, int *firstpos);
int findlast(struct Corse **v, int indice_inizio, int r, char *key, int fine);
int ricercaLineare(struct Corse **d, int tot, char *stazione, int n, int *indici);

int main()
{
    int i=0, j, tot, stmp=0, ord=0, opzione, l, indici[MAX], corrisp=0, first=0, last=0;
    int *firstpos=&first, *lastpos=&last;
    char temp[201], staz[mcod];
    struct Corse corse[MAX], *log_disordinato[MAX], *data[MAX], *codice[MAX], *partenza[MAX], *arrivo[MAX], *ricerca[mcod];

    FILE *fp;
    FILE *fp2;

    fp=fopen("corse.txt", "r");

    if(fp == NULL){
        printf("Errore file corse.txt\n");
        return -3;
    }

    fgets(temp, "%s", fp);
    sscanf(temp, "%d", &tot);
    i=0;
    while(fgets(temp, "%s", fp) != NULL){
        sscanf(temp, "%s %s %s %d/%d/%d %d:%d %d:%d %d",
            corse[i].cod, corse[i].part, corse[i].dest, &corse[i].giorno, &corse[i].mese,
            &corse[i].anno, &corse[i].ora_p, &corse[i].min_p,
            &corse[i].ora_a, &corse[i].min_a, &corse[i].ritardo);
        i++;
    }
    fclose(fp);
    if(tot!=i){
        printf("Errore file corse.txt");
        return -1;
    }
    for(i=0; i<tot; i++){
            log_disordinato[i]=data[i]=codice[i]=partenza[i]=arrivo[i]=&corse[i];//i vettori di puntatori che conterranno le sequanze ordinate puntano inzialmente al vettore di strutture
    }
    /*uso un vettore di struct Corse per memorizzare cio' che leggo da file, poi gli elementi dei vettori di puntatori puntano agli elementi del vettore di strutture corse, all'inizio sono dunque disordinati*/

    ordinaData(data, tot); //passo il vettore di puntatori agli elementi del vettore di strutture e non il dato stesso
    ordinaCodice(codice, tot);
    ordinaPartenza(partenza, tot);
    ordinaArrivo(arrivo, tot);

    opzione=1;
    while(opzione!=0){

        printf("Scegli un'operazione:\n1   Stampa.\n");
        printf("2   Ordinamento per orario.\n3   Ordinamento per codice di tratta.\n");
        printf("4   Ordinamento per stazione di partenza.\n5   Ordinamento per stazione di arrivo.\n");
        printf("6   Ricerca parola.\n0   Interrompi il programma.\nInserisci un qualsiasi altro valore per annullare ogni ordinamento del vettore.\n\n");
        scanf("%d", &opzione);

        switch(opzione){
            case 0:
                    printf("\nTermine programma.\n");
                    return 0;

            case 1:     //stampa
                    if(ord==0){
                        stmp=stampa(log_disordinato, tot, ord, fp2);
                        if(stmp==-1)
                            return -2;
                    }
                    else if(ord==1){
                        stmp=stampa(data, tot, ord, fp2);
                        if(stmp==-1)
                            return -2;
                    }
                    else if(ord==2){
                        stmp=stampa(codice, tot, ord, fp2);
                        if(stmp==-1)
                            return -2;
                    }
                    else if(ord==3){
                        stmp=stampa(partenza, tot, ord, fp2);
                        if(stmp==-1)
                            return -2;
                    }
                    else if(ord==4){
                        stmp=stampa(arrivo, tot, ord, fp2);
                        if(stmp==-1)
                            return -2;
                    }
                    break;

            case 2:
                    ord=1;
                    break;

            case 3:
                    ord=2;
                    break;

            case 4:
                    ord=3;
                    break;

            case 5:
                    ord=4;
                    break;
            case 6:     //ricerca dicotomica nel vettore di puntatori alle strutture ordinate per stazione di partenza
                    printf("Cerca stazione di partenza:\n");
                    scanf("%s", staz);
                    strlwr(staz);
                    l=0;
                    /* corrisp=ricercaLineare(partenza, tot, staz, strlen(staz), indici);  //ricerca lineare non necessaria perche' abbiamo gia' un vettore ordinato su cui effettuare BinSearch */
                    corrisp=BinSearch(partenza, l, tot-1, tot-1, staz, firstpos, lastpos);
                    if(corrisp==1){
                        for(i=*firstpos; i<=*lastpos; i++){
                        printf("%s %s %s %02d/%02d/%02d %02d:%02d %02d:%02d %d\n",
                                partenza[i]->cod, partenza[i]->part, partenza[i]->dest, partenza[i]->giorno, partenza[i]->mese,
                                partenza[i]->anno, partenza[i]->ora_p, partenza[i]->min_p,
                                partenza[i]->ora_a, partenza[i]->min_a, partenza[i]->ritardo);
                        }
                    }
                    else if(corrisp==0){
                        printf("La ricerca non e' andata a buon fine.\nNessuna stazione di partenza corrispondente ai parametri cercati.\n");
                    }
                    break;

            default:
                    printf("Ordinamento annullato.\n");
                    ord=0;
                    break;
        }
        printf("\n");
    }
        return 0;
    }

int stampa(struct Corse **c, int tot, int ord, FILE *fp){
    int i=0, scelta_stampa=0;
    printf("\nScegli se vuoi stampare i contenuti del log a video o su file.\n");
    printf("Digita 1 per stampare a video o 2 per stampare sul file stampa.txt.\n");
    scanf("%d", &scelta_stampa);
    printf("\n");
    switch (scelta_stampa) {
            case 1: {
                        if(ord==0)
                            printf("Log disordinato:\n");
                        else if(ord==1)
                            printf("Log ordinato per data e ora:\n");
                        else if(ord==2)
                            printf("Log ordinato per codice della tratta:\n");
                        else if(ord==3)
                            printf("Log ordinato per stazione di partenza:\n");
                        else if(ord==4)
                            printf("Log ordinato per stazione di arrivo:\n");

                        for(i=0; i<tot; i++){
                            printf("%s %s %s %02d/%02d/%02d %02d:%02d %02d:%02d %d\n",
                                c[i]->cod, c[i]->part, c[i]->dest, c[i]->giorno, c[i]->mese,
                                c[i]->anno, c[i]->ora_p, c[i]->min_p,
                                c[i]->ora_a, c[i]->min_a, c[i]->ritardo);
                        }
                        return 0;
                    }

            case 2: {
                        fp=fopen("stampa.txt", "w");

                        if(ord==0)
                            fprintf(fp, "Log disordinato:\n");
                        else if(ord==1)
                            fprintf(fp, "Log ordinato per data e ora:\n");
                        else if(ord==2)
                            fprintf(fp, "Log ordinato per codice della tratta:\n");
                        else if(ord==3)
                            fprintf(fp, "Log ordinato per stazione di partenza:\n");
                        else if(ord==4)
                            fprintf(fp, "Log ordinato per stazione di arrivo:\n");

                        for(i=0; i<tot; i++){
                            fprintf(fp, "%s %s %s %02d/%02d/%02d %02d:%02d %02d:%02d %d\n",
                                c[i]->cod, c[i]->part, c[i]->dest, c[i]->giorno, c[i]->mese,
                                c[i]->anno, c[i]->ora_p, c[i]->min_p,
                                c[i]->ora_a, c[i]->min_a, c[i]->ritardo);
                        }
                        fclose(fp);
                        return 0;
                    }

            default:    printf("Errore valore inserito.\n\n");
                        return -1;
    }
}

//le funzioni di ordinamento sono state effettuate con l'algoritmo del selection sort, poiche' stabile

void ordinaData(struct Corse **d, int tot){
    int i, j, l=0, r=tot-1;
    struct Corse *temp;

    for(i = l+1; i <= r; i++){
        temp = d[i];
        j = i - 1;
        while(j >= l && orario(temp, d[j]) < 0 ){
            d[j+1] = d[j];
            j--;
        }
        d[j+1] = temp;
    }
}


int orario(struct Corse *temp, struct Corse *d){
    if(temp->anno < d->anno)
        return -1;
    else if(temp->anno==d->anno && temp->mese < d->mese)
        return -1;
    else if(temp->anno==d->anno && temp->mese==d->mese && temp->giorno < d->giorno)
        return -1;
    else if(temp->anno==d->anno && temp->mese==d->mese && temp->giorno==d->giorno && temp->ora_p < d->ora_p)
        return -1;
    else if(temp->anno==d->anno && temp->mese==d->mese && temp->giorno==d->giorno && temp->ora_p==d->ora_p && temp->min_p < d->min_p)
        return -1;
    return 1;
}


void ordinaCodice(struct Corse **d, int tot){
    int i, j, l=0, r=tot-1;
    struct Corse *temp;

    for(i = l+1; i <= r; i++){
        temp = d[i];
        j = i - 1;
        while(j >= l && strcmp(temp->cod, d[j]->cod) < 0 ){
            d[j+1] = d[j];
            j--;
        }
        d[j+1] = temp;
    }
}


void ordinaPartenza(struct Corse **d, int tot){
    int i, j, l=0, r=tot-1;
    struct Corse *temp;

    for(i = l+1; i <= r; i++){
        temp = d[i];
        j = i - 1;
        while(j >= l && strcmp(temp->part, d[j]->part) < 0 ){
            d[j+1] = d[j];
            j--;
        }
        d[j+1] = temp;
    }
}


void ordinaArrivo(struct Corse **d, int tot){
    int i, j, l=0, r=tot-1;
    struct Corse *temp;

    for(i = l+1; i <= r; i++){
        temp = d[i];
        j = i - 1;
        while(j >= l && strcmp(temp->dest, d[j]->dest) < 0 ){
            d[j+1] = d[j];
            j--;
        }
        d[j+1] = temp;
    }
}


int BinSearch(struct Corse **v, int l, int r, int fine, char *key, int *firstpos, int *lastpos){
    int m, flagfirst;
    char partenza[mcod];
    if (l > r)
        return -1;//se non trova nulla con quella ricerca

    m = (l + r) / 2;

    strcpy(partenza, v[m]->part);
    strlwr(partenza);

    flagfirst = isfirst(v, m, key, firstpos);//ritorna 1 se e' quello in m il primo e mette in *firstpos la casella del vettore che punta alla prima struct interessata

    if (flagfirst==1){
        *lastpos=findlast(v, m, fine, key, fine);//cerca la fine della ricerca
        if(*lastpos==-1){
            printf("Errore della funzone BinSearch.\n");
            return -2;
        }
        return 1;
    }

    else if(strncmp(partenza, key, strlen(key)) >= 0){
        return BinSearch(v, l, m, r, key, firstpos, lastpos);
    }
    else if(strncmp(partenza, key, strlen(key)) < 0){
        return BinSearch(v, m+1, r, r, key, firstpos, lastpos);
    }
}

//isfirst ritorna 1 se indice e' la prima posizione del vettore di puntatori che punta alla stazione chiave e mette in *firstpos la posizione di essa
// ritorna 0 se non lo e', e continua la ricerca attraverso le chiamate ricorsive della funzione, attraverso gli else if in basso.
int isfirst(struct Corse **v, int indice, char *key, int *firstpos){
    char partenza1[mcod], partenza2[mcod];
    strcpy(partenza1, v[indice]->part);
    strlwr(partenza1);  //lo faccio per poter trovare una stazione di partenza anche se la chiave di ricerca non ha maiuscole al posto giusto

    if(indice-1>=0){
        strcpy(partenza2, v[indice-1]->part);
        strlwr(partenza2);
    }

    if((strncmp(partenza1, key, strlen(key)) == 0) && (indice-1 < 0 || (indice-1 >= 0 && strncmp(partenza2, key, strlen(key)) != 0))){
        *firstpos=indice;
        return 1;
    }
    else
        return 0;
}

/*trovo l'ultima posizione della chiave all'interno del vettore di puntatori ordinato per stazione di partenza.
indice_inizio rappresenta l'indice del primo puntatore del vettore di puntatori v che contiene la chiave nel campo partenza
Attraverso una funzione ricorsiva trovo l'ultimo puntatore che lo fa e ritorno l'indice del vettore di puntatori v in cui c'e' per l'ultima volta la chiave*/
int findlast(struct Corse **v, int indice_inizio, int r, char *key, int fine){
    int i=0, m=0;
    char partenza1[mcod], partenza2[mcod];

    m = (indice_inizio + r) / 2;
    strcpy(partenza1, v[m]->part);
    strlwr(partenza1);

    if(m+1<=fine){
        strcpy(partenza2, v[m+1]->part);
        strlwr(partenza2);
    }

    if((strncmp(partenza1, key, strlen(key)) == 0) && ((m+1 > fine) || (m+1 <= fine && strncmp(partenza2, key, strlen(key)) != 0)))
        return m;
    else if(strncmp(partenza1, key, strlen(key)) > 0)
        return findlast(v, indice_inizio, m, key, fine);
    else if(strncmp(partenza1, key, strlen(key)) <= 0)
        return findlast(v, m+1, r, key, fine);
}

/*la funzione di ricerca lineare scandisce tutte le strutture i-esime puntate dal vettore v di struct e
memorizza gli indici dei puntatori alle struct in cui si trova la chiave in un altro vettore chiamato indici*/
int ricercaLineare(struct Corse **d, int tot, char *stazione, int n, int *indici){
    int i, j=0;
    char partenza[mcod];
    for(i=0; i<tot; i++){
        strcpy(partenza, d[i]->part);
        strlwr(partenza);
        if(strncmp(partenza, stazione, n) == 0){
            indici[j]=i;
            j++;
        }
    }
    return j; //j rappresenta il numero di corrispondenze trovate nel vettore di struct
}
