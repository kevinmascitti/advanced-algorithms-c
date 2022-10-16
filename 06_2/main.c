#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define MAX 51
#define dimcod 6
#define dimdata 11
#define maxfile 50
#define FILE_I "anagrafica.txt"

typedef struct{
    int gg;
    int mm;
    int aa;
} Key;

typedef struct{
    char codice[dimcod];
    char nome[MAX];
    char cognome [MAX];
    Key data;
    char via[MAX];
    char citta[MAX];
    int cap;
} Item;

typedef struct node {
    Item val;
    struct node *next;
} node_t, *link;

int isnull(Item a);
Item ITEMsetvoid();
link leggi(link h);
link leggiFile(FILE *fp, char* nfile, link h);
void stampa(link h);
void stampaRiga(Item sol);
void stampaSuFile(FILE *fp, link h);
link newNode(Item val, link next);
link SortListIns(link h, Item val);
Item SortListSearch(link h, char* k);
Item listExtrKeyP(link *hp, char* k);
link estraiPerData(link h);
Item listExtrKeyData(link *hp, int g1, int g2, int m1, int m2, int a1, int a2);
Key KEYget(Item val);
int KEYgreater(Key k1, Key k2);
int KEYeq(Key k1, Key k2);
int KEYgeq(Key k1, Key k2);


int main()
{
    int i=0, N=1, dati, opzione;
    char tmp[250];
    Item *a, sol;
    link h = NULL, *head = &h;
    char chiave[dimcod], nfile[maxfile];
    Key data1;
    Key data2;
    FILE *fp;

    strcpy(nfile, FILE_I);
    h=leggiFile(fp, nfile, h);

    opzione=1;
    while(opzione!=0){
        printf("Scegli un'opzione:\n");
        printf("1   Inserisci nuovo elemento da tastiera.\n");
        printf("2   Inserisci nuovi elementi da file.\n");
        printf("3   Ricerca un elemento per codice.\n");
        printf("4   Estrai un elemento dalla lista per codice.\n");
        printf("5   Estrai elementi multipli dalla lista, in base alla data di nascita.\n");
        printf("6   Stampa la lista su un file.\n");
        printf("7   Stampa la lista a video.\n");   //opzione aggiuntiva non richiesta dalla traccia
        printf("INSERISCI 0 PER INTERROMPERE IL PROGRAMMA.\n\n");
        scanf("%d", &opzione);

        switch(opzione){
            case 1: h=leggi(h);
                    printf("\n");
                    break;
            case 2: printf("Inserisci il nome del nuovo file:\t");
                    scanf("%s", nfile);
                    h=leggiFile(fp, nfile, h);
                    printf("\n");
                    break;
            case 3: printf("Inserisci il codice:\t");
                    scanf("%s", chiave);
                    sol=SortListSearch(h, chiave);
                    if( isnull(sol)==1 ){
                        printf("La ricerca non ha prodotto alcun risultato.\n");
                    break;
                    }
                    printf("\nLa ricerca ha prodotto un risultato:\n");
                    stampaRiga(sol);
                    printf("\n");
                    break;
            case 4: printf("Inserisci il codice:\t");
                    scanf("%s", chiave);
                    sol=listExtrKeyP(head, chiave);
                    if( isnull(sol)==1 ){
                        printf("La ricerca non ha prodotto alcun risultato.\n\n");
                        break;
                    }
                    stampaRiga(sol);
                    printf("\n");
                    break;
            case 5: h=estraiPerData(h);
                    break;
            case 6: stampaSuFile(fp, h);
                    break;
            case 7: stampa(h); //opzione aggiuntiva non richiesta
                    break;
            case 0: return 0;
            default:    printf("Opzione non valida.\n");
                        break;
        }
    }
    return 0;
}

int isnull(Item a){
    if(a.codice[0]=='\0'&&a.nome[0]=='\0'&&a.cognome[0]=='\0'&&a.data.gg==0&&a.data.mm==0&&a.data.aa==0&&a.via[0]=='\0'&&a.citta[0]=='\0'&&a.cap==0)
        return 1;
    return 0;
}

Item ITEMsetvoid(){
    Item m;
    m.codice[0]='\0';
    m.nome[0]='\0';
    m.cognome[0]='\0';
    m.data.gg=m.data.mm=m.data.aa=0;
    m.via[0]='\0';
    m.citta[0]='\0';
    m.cap=0;
    return m;
}

link leggi(link h){     //legge una nuova riga da tastiera e la inserisce nella lista in modo ordinato restituendo il puntatore alla testa della lista
    Item a;
    char dat[11];
    printf("Inserisci elemento:\n<codice> <nome> <cognome> <gg/mm/aaaa> <via> <citta'> <cap>\n");
    scanf("%s %s %s %s %s %s %d", a.codice, a.nome, a.cognome, dat, a.via, a.citta, &a.cap);
    sscanf(dat, "%d/%d/%d", &a.data.gg, &a.data.mm, &a.data.aa);
    if(strlen(a.codice)!=dimcod-1 || a.codice[0]!='A'){
        printf("Errore codice: il codice deve contenere una A iniziale e 4 valori interi.\n\n");
        return h;
    }
    if(a.data.gg<1||a.data.gg>31||a.data.mm<1||a.data.mm>12||a.data.aa<0){
        printf("Errore data di nascita.\n\n");
        return h;
    }
    h = SortListIns(h, a);
    return h;
}

link leggiFile(FILE *fp, char* nfile, link h){  //legge una nuova riga da file il cui nome e' letto da tastiera e la inserisce nella lista in modo ordinato restituendo il puntatore alla testa della lista
    Item *a;
    int i=0, N=1, flag, dati;
    char tmp[250];
    fp=fopen(nfile, "r");
    if(fp==NULL){
        printf("Errore: file vuoto.\n");
        return h;
    }
    a = (Item*) calloc ( N, sizeof(Item) );
    printf("\nLista disordinata da file %s:\n", nfile);
    while(fgets(tmp, "%s", fp) != NULL){
        flag=1;
        if(i==N){
            N=N*2;
            a = (Item*) realloc ( a, N * sizeof(Item) );
        }
        sscanf(tmp, "%s %s %s %d/%d/%d %s %s %d", a[i].codice,
                        a[i].nome, a[i].cognome, &a[i].data.gg, &a[i].data.mm, &a[i].data.aa, a[i].via, a[i].citta, &a[i].cap);
        if(strlen(a[i].codice)!=dimcod-1 || a[i].codice[0]!='A'){
            printf("\nErrore codice nella riga %d del file %s: il codice deve contenere una A iniziale e 4 valori interi.\n\n", i+1, nfile);
            flag=0;
        }
        if(a[i].data.gg<1||a[i].data.gg>31||a[i].data.mm<1||a[i].data.mm>12||a[i].data.aa<0){
            printf("\nErrore data di nascita nella riga %d del file %s.\n\n", i+1, nfile);
            flag=0;
        }
        if(flag!=0)
            stampaRiga(a[i]);
        h = SortListIns(h, a[i]);
        i++;
    }
    dati=i;
    printf("\nLista ordinata:\n");
    stampa(h);
    fclose(fp);
    free(a);

    return h;
}

void stampa(link h){        //stampa la lista intera data la testa
    link x;
    if(h==NULL){
        printf("Lista vuota.\n\n");
        return;
    }
    for(x=h; x!=NULL; x=x->next){
        stampaRiga(x->val);
    }
    printf("\n");
    return;
}

void stampaRiga(Item sol){  //stampa un elemento della lista (struttura)
    printf("%s %s %s %02d/%02d/%02d %s %s %05d\n", sol.codice, sol.nome, sol.cognome, sol.data.gg, sol.data.mm, sol.data.aa, sol.via, sol.citta, sol.cap);
    return;
}

void stampaSuFile(FILE *fp, link h){    //stampa la lista sul file il cui nome e' passato da tastiera
    char file[50];
    link x;
    printf("Inserisci il nome del file su cui stampare la lista:\t");
    scanf("%s", file);
    fp=fopen(file, "w");
    if(h==NULL){
        fprintf(fp, "Lista vuota.\n\n");
        return;
    }
    for(x=h; x!=NULL; x=x->next){
        fprintf(fp, "%s %s %s %02d/%02d/%02d %s %s %05d\n", x->val.codice, x->val.nome, x->val.cognome, x->val.data.gg, x->val.data.mm, x->val.data.aa, x->val.via, x->val.citta, x->val.cap);
    }
    fclose(fp);
    return;
}

link newNode(Item val, link next) { //funzioni di lista
    link x = malloc(sizeof *x);
    if (x==NULL)
        return NULL;
    else {
        x->val = val;
        x->next = next;
    }
    return x;
}

link SortListIns(link h, Item val){
    link x, p;
    Key k = KEYget(val);
    if (h==NULL || KEYgreater(KEYget(h->val),k))
        return newNode(val, h);
    for (x=h->next, p=h; x!=NULL && KEYgreater(k,KEYget(x->val)); p=x, x=x->next);
    p->next = newNode(val, x);
    return h;
}

Item SortListSearch(link h, char* k) { //ricerca in lista non ordinata per codice inserito da tastiera
    link x;
    for (x=h; x!=NULL; x=x->next)
        if ( strcmp(x->val.codice, k) == 0)
            return x->val;
    return ITEMsetvoid();
}

Item listExtrKeyP(link *hp, char* k) {  //estrazione da lista non ordinata per codice da tastiera
    link *xp, t;
    Item i = ITEMsetvoid();
    for (xp=hp; (*xp)!=NULL; xp=&((*xp)->next)) {
        if (strcmp((*xp)->val.codice, k) == 0){
            t = *xp;
            *xp = (*xp)->next;
            i = t->val;
            free(t);
            break;
        }
    }
    return i;
}

link estraiPerData(link h){
    link x, *head=&h;
    Item a;
    int i=0;
    char data1[dimdata], data2[dimdata];
    int g1, g2, m1, m2, a1, a2;
    printf("Inserisci un intervallo di date di nascita:\n");
    scanf("%s", data1);
    scanf("%s", data2);
    sscanf(data1, "%d/%d/%d", &g1, &m1, &a1);
    sscanf(data2, "%d/%d/%d", &g2, &m2, &a2);
    while(g1<1||g2<1||g1>31||g2>31||m1<1||m2<1||m1>12||m2>12||a1<0||a2<0){
        printf("Errore date di nascita inserite.\nRiprova.\n\n");
        printf("Inserisci un intervallo di date di nascita:\n");
        scanf("%s", data1);
        scanf("%s", data2);
        sscanf(data1, "%d/%d/%d", &g1, &m1, &a1);
        sscanf(data2, "%d/%d/%d", &g2, &m2, &a2);
    }
    a.cap=1;
    while(isnull(a)!=1){
        a=listExtrKeyData(head,g1,g2,m1,m2,a1,a2);
        if(isnull(a)!=1)
            stampaRiga(a);
    }
    printf("\n");
    return h;
}

Item listExtrKeyData(link *hp, int g1, int g2, int m1, int m2, int a1, int a2) {    //estrazone da lista ordinata per date inserite da tastiera
    link *xp, t;
    Item i = ITEMsetvoid();
    for (xp=hp; (*xp)!=NULL; xp=&((*xp)->next)) {
        if ( ( (*xp)->val.data.aa>a1 && (*xp)->val.data.aa<a2 )
            || ( ( (*xp)->val.data.aa==a1 && (*xp)->val.data.mm>m1 ) || ( (*xp)->val.data.aa==a2 && (*xp)->val.data.mm<m2 ) )
            || ( ( (*xp)->val.data.aa==a1 && (*xp)->val.data.mm==m1 && (*xp)->val.data.gg>=g1 ) || ( (*xp)->val.data.aa==a2 && (*xp)->val.data.mm==m2 && (*xp)->val.data.gg<=g2 ) ) ){
            t = *xp;
            *xp = (*xp)->next;
            i = t->val;
            free(t);
            break;
        }
    }
    return i;
}

Key KEYget(Item val){
    return val.data;
}

int KEYgreater(Key k1, Key k2){
    if( (k1.aa>k2.aa) || (k1.aa==k2.aa && k1.mm>k2.mm) || (k1.aa==k2.aa && k1.mm==k2.mm && k1.gg>k2.gg) )
        return 1;
    return 0;
}

int KEYeq(Key k1, Key k2){
    if( k1.aa==k2.aa && k1.mm==k2.mm && k1.gg==k2.gg )
        return 1;
    return 0;
}

int KEYgeq(Key k1, Key k2){
    if( KEYgreater(k1, k2) && KEYeq(k1, k2) )
        return 1;
    return 0;
}
