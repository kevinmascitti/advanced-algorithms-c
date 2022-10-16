#include <stdio.h>
#include <stdlib.h>

typedef struct attivita{
    int s, f, d;
} att_t;

void LIS(att_t *a, int tot);
void stampaLIS(att_t *a, int *P, int i);
void stampaAttivita(att_t *a, int tot);
void Swap( att_t *a, int n1, int n2);
int partition ( att_t *a, int l, int r );
void QuickSortR( att_t *a, int l, int r );
void QuickSort(att_t *a, int N);
int ITEMlt(att_t a, att_t b);
int ITEMgt(att_t a, att_t b);

int main()
{
    int i, j, tot;              //L vettore per memorizzare durata totale LIS,
                                //P vettore per l'indice dell'elemento precedente nella LIS,
                                //last per l'indice dell'ultimo elemento nella LIS
    att_t *a;
    char tmp[5];
    //LETTURA FILE
    FILE *fp=fopen("attivita.txt", "r");
    fscanf(fp, "%d", &tot);
    a=malloc(tot*sizeof(*a));
    for(i=0; i<tot; i++){
        fscanf(fp, "%d %d", &a[i].s, &a[i].f);
        a[i].d=a[i].f-a[i].s;
    }
    if(i!=tot) { printf("Errore file attivita.txt\n"); return -1; }
    printf("Lista completa delle attivita' ordinata per fine:\n");
    fclose(fp);
    QuickSort(a, tot); //ordinamento del vettore in base alla fine delle attivita'
    stampaAttivita(a, tot);
    LIS(a, tot);

    return 0;
}

void LIS(att_t *a, int tot){
    int i, j, ris, L[tot], P[tot], last=1;
    L[0]=a[0].f-a[0].s;
    P[0]=-1;
    for(i=1; i<tot; i++){
        L[i]=ris=a[i].d;
        P[i]=-1;
        for(j=i-1; j>=0; j--)                           //ciclo di analisi delle precedenti attivita' a partire da quella piu a "destra"
            if( a[j].f<=a[i].s && L[i]<a[i].d+L[j] ){   //condizione 1: le attivita' non devono intersecarsi
                                                        //condizione 2: si prendono le attivita' ottimali che massimizzano la durata
                L[i]=a[i].d+L[j];
                P[i]=j;
            }
        if(ris<L[i]){
            ris=L[i];
            last=i;
        }
    }
    printf("\nLa sequenza di attivita' massima e':\n");
    stampaLIS(a, P, last);
    printf("\nLe attivita' hanno durata totale %d.\n", ris);
    return;
}

void stampaLIS(att_t *a, int *P, int i){
    if(P[i]==-1){    //se la precedente attivita' di quella che sto analizzando non esiste, allora stampo la corrente e non stampo piu' niente
        printf("%d %d\n", a[i].s, a[i].f);
        return;
    }
    stampaLIS(a, P, P[i]); //ricerco la prima attivita' da stampare, quella quando P[last]==-1
    printf("%d %d\n", a[i].s, a[i].f); //trovata la prima attivita', ritorno e stampo la successiva, ricorsivamente fino alla fine
    return;
}

void stampaAttivita(att_t *a, int tot){
    int i;
    for(i=0; i<tot; i++)
        printf("%d %d\n", a[i].s, a[i].f);
    return;
}

void Swap(att_t *a, int n1, int n2) {
    att_t temp;
    temp = a[n1];
    a[n1] = a[n2];
    a[n2] = temp;
    return;
}

int partition ( att_t *a, int l, int r ) {
    int i, j;
    att_t x = a[r];
    i = l-1;
    j = r;
    for ( ; ; ) {
        while(ITEMlt(a[++i], x));
        while(ITEMgt(a[--j], x))
        if (j == l)
            break;
        if (i >= j)
            break;
        Swap(a, i, j);
    }
    Swap(a, i, r);
    return i;
}

void QuickSortR( att_t *a, int l, int r ) {
    int q;
    if (r <= l)
        return;
    q = partition(a, l, r);
    QuickSortR(a, l, q-1);
    QuickSortR(a, q+1, r);
    return;
}

void QuickSort(att_t *a, int N) {
    int l=0, r=N-1;
    QuickSortR(a, l, r);
}

int ITEMlt(att_t a, att_t b) {
  return (a.f < b.f);
}

int ITEMgt(att_t a, att_t b) {
  return (a.f > b.f);
}
