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
struct Corse *leggiFile(FILE *fp, char *file, int *tot);

int main()
{
    int i=0, tot, stmp=0, ord=0, opzione=7, l, corrisp=0, first=0, last=0, N=0;
    int *firstpos=&first, *lastpos=&last;
    struct Corse *cors;
    char sta[mcod], file[mcod]="corse.txt";
    struct Corse **log_disordinat, **dat, **codic, **partenz, **arriv;

    FILE *fp;
    FILE *fp2;

    while(opzione == 7){

        cors = leggiFile(fp, file, &tot);

        log_disordinat = (struct Corse**) malloc (tot * sizeof(struct Corse));
        dat = (struct Corse**) malloc (tot * sizeof(struct Corse));
        codic = (struct Corse**) malloc (tot * sizeof(struct Corse));
        partenz = (struct Corse**) malloc (tot * sizeof(struct Corse));
        arriv = (struct Corse**) malloc (tot * sizeof(struct Corse));

        for(i=0; i<tot; i++){
            log_disordinat[i]=dat[i]=codic[i]=partenz[i]=arriv[i]=&cors[i];
        }
/*uso un vettore di struct Corse per memorizzare cio' che leggo da file, poi gli elementi dei vettori di puntatori puntano agli elementi del vettore di strutture corse, all'inizio sono dunque disordinati*/
        if(tot==-1){
            printf("ERRORE FILE.");
            return -1;
        }

        //ordinamenti
        ordinaData(dat, tot); //passo il vettore di puntatori agli elementi del vettore di strutture e non il dato stesso
        ordinaCodice(codic, tot);
        ordinaPartenza(partenz, tot);
        ordinaArrivo(arriv, tot);

        opzione=1;
        while(opzione != 7){

            printf("Scegli un'operazione:\n1   Stampa.\n");
            printf("2   Ordinamento per orario.\n3   Ordinamento per codice di tratta.\n");
            printf("4   Ordinamento per stazione di partenza.\n5   Ordinamento per stazione di arrivo.\n");
            printf("6   Ricerca parola.\n7   Leggi nuovo file.\n0   Interrompi il programma.\n");
            printf("Inserisci un qualsiasi altro valore per annullare ogni ordinamento del vettore.\n");
            scanf("%d", &opzione);
            printf("\n");

            switch(opzione){
                case 0:     //interrompi
                        printf("\nTermine programma.\n");
                        return 0;

                case 1:     //stampa
                        if(ord==0){
                            stmp=stampa(log_disordinat, tot, ord, fp2);
                            if(stmp==-1)
                                return -2;
                        }
                        else if(ord==1){
                            stmp=stampa(dat, tot, ord, fp2);
                            if(stmp==-1)
                                return -2;
                        }
                        else if(ord==2){
                            stmp=stampa(codic, tot, ord, fp2);
                            if(stmp==-1)
                                return -2;
                        }
                        else if(ord==3){
                            stmp=stampa(partenz, tot, ord, fp2);
                            if(stmp==-1)
                                return -2;
                        }
                        else if(ord==4){
                            stmp=stampa(arriv, tot, ord, fp2);
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
                        N=1;
                        i=0;
                        l=0;
                        scanf("%s", sta);
                        /*corrisp=ricercaLineare(partenz, tot, staz, strlen(staz), indic);  //ricerca lineare inutile perche' ho gia' un vettore di puntatori ordinato per stazione di partenza*/
                        corrisp=BinSearch(partenz, l, tot-1, tot-1, sta, firstpos, lastpos);
                        if(corrisp==1){
                            for(i = *firstpos; i <= *lastpos; i++){
                            printf("%s %s %s %02d/%02d/%02d %02d:%02d %02d:%02d %d\n",
                                    partenz[i]->cod, partenz[i]->part, partenz[i]->dest, partenz[i]->giorno, partenz[i]->mese,
                                    partenz[i]->anno, partenz[i]->ora_p, partenz[i]->min_p,
                                    partenz[i]->ora_a, partenz[i]->min_a, partenz[i]->ritardo);
                            }
                        }
                        else if(corrisp==0){
                            printf("La ricerca non e' andata a buon fine.\nNessuna stazione di partenza corrispondente ai parametri cercati.\n");
                        }

                        break;

                case 7:
                        printf("Inserisci il nome di un nuovo file:\n");
                        scanf("%s", file);
                        break;

                case 8: printf("\nFine del prgramma.\n");
                        return 0;
                default:
                        printf("Ordinamento annullato.\n");
                        ord=0;
                        break;
            }
            printf("\n");
        }
        //libero lo spazio in memoria occupato dai vettori di puntatori alla fine di ogni ciclo while
        free(log_disordinat);
        free(dat);
        free(codic);
        free(partenz);
        free(arriv);
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
    char *p;
    strlwr(key);
    if (l > r)
        return 0;//se non trova nulla con quella ricerca

    m = (l + r) / 2;

    flagfirst = isfirst(v, m, key, firstpos);//ritorna 1 se e' quello in m il primo e mette in *firstpos la casella del vettore che punta alla prima struct interessata
    p = (char*) malloc ( sizeof(v[m]->part) + 1 );
    strcpy(p, v[m]->part);

    if (flagfirst==1){
        *lastpos=findlast(v, m, fine, key, fine);//cerca la fine della ricerca
        if(*lastpos==-1){
            printf("Errore della funzone BinSearch.\n");
            return -2;
        }
        return 1;
    }

    else if(strncmp(strlwr(p), key, strlen(key)) >= 0)
        return BinSearch(v, l, m, r, key, firstpos, lastpos);

    else if(strncmp(strlwr(p), key, strlen(key)) < 0)
        return BinSearch(v, m+1, r, r, key, firstpos, lastpos);

    printf("Errore della funzone BinSearch.\n");
    return -2;
}

//isfirst ritorna 1 se indice e' la prima posizione del vettore di puntatori che punta alla stazione chiave e mette in *firstpos la posizione di essa
// ritorna 0 se non lo e', e continua la ricerca attraverso le chiamate ricorsive della funzione, attraverso gli else if in basso.
int isfirst(struct Corse **v, int indice, char *key, int *firstpos){
    char *s, *z;
    s = (char*) malloc( sizeof(v[indice]->part) + 1);
    strcpy(s, v[indice]->part);

    if(indice>=1){
        z = (char*) malloc( sizeof(v[indice-1]->part) + 1);
        strcpy(z, v[indice-1]->part);
    }

    if((strncmp(strlwr(s), key, strlen(key)) == 0) && (indice-1 < 0 || (indice-1 >= 0 && strncmp(strlwr(z), key, strlen(key)) != 0))){
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
    int m=0;
    m = (indice_inizio + r) / 2;
    char *e, *f;
    e = (char*) malloc ( sizeof(v[m]->part) + 1);
    strcpy(e, v[m]->part);

    if(m+1<fine){
        f = (char*) malloc ( sizeof(v[m+1]->part) + 1 );
        strcpy(f, v[m+1]->part);
    }

    if((strncmp(strlwr(e), key, strlen(key)) == 0) && ((m+1 >= fine) || (m+1 < fine && strncmp(strlwr(f), key, strlen(key)) != 0))){
        return m;
    }
    else if(strncmp(strlwr(e), key, strlen(key)) > 0)
        return findlast(v, indice_inizio, m, key, fine);

    else if(strncmp(strlwr(e), key, strlen(key)) <= 0)
        return findlast(v, m+1, r, key, fine);

    printf("Errore funzione findlast.\n");
    return -2;
}



/*la funzione di ricerca lineare scandisce tutte le strutture i-esime puntate dal vettore v di struct e
memorizza gli indici dei puntatori alle struct in cui si trova la chiave in un altro vettore chiamato indici*/
int ricercaLineare(struct Corse **d, int tot, char *stazione, int n, int *indici){
    int i, j=0;
    for(i=0; i<tot; i++){
        if(strncmp(d[i]->part, stazione, n) == 0){
            indici[j]=i;
            j++;
        }
    }
    return j; //j rappresenta il numero di corrispondenze trovate nel vettore di struct
}

struct Corse *leggiFile(FILE *fp, char *file, int *tot){
    int i=0;
    struct Corse *c;

    fp=fopen(file, "r");
    if(fp == NULL){
        printf("Errore file.\n");
        return -1;
    }
    fscanf(fp, "%d", tot);
    c = (struct Corse *) malloc ( (*tot) * sizeof(struct Corse) );
    for(i=0; i< (*tot) ; i++){
        fscanf(fp, "%s %s %s %02d/%02d/%02d %02d:%02d %02d:%02d %d", c[i].cod, c[i].part, c[i].dest,
               &c[i].giorno, &c[i].mese, &c[i].anno, &c[i].ora_p, &c[i].min_p,
                    &c[i].ora_a, &c[i].min_a, &c[i].ritardo);
    }
    fclose(fp);

    if( *tot != i){
        printf("Errore file corse.txt");
        return -1;
    }

    return c;
    }
