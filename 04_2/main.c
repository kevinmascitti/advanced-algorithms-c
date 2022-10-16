#include <stdio.h>
#include <stdlib.h>
#define M 10


/*la funzione majority ordina il vettore tramite l'aloritmo ricorsivo del QuickSort,
che e' in loco, e analizza ogni elemento del vettore ordinato. Se ogni elemento del
vetttore e' seguito dallo stesso elemento in posizione i+1, aumenta il valore delle
occorrenze. Qualora esso sia maggiore di N/2, esso e' un elemento maggioritario
e viene restituito alla funzione chiamante, altrimenti si prosegue fino alla fine
del vettore. Se non viene trovato nessun elemento maggioritario, viene restituito -1.*/

int majority(int *a, int N){
    int i=0, cont=0;
    QuickSort(a,N);
    for(i=0;i<N-1;i++){
        if(a[i]==a[i+1]){
            cont++;
            if(cont>N/2)
                return a[i];
        }
        else{
            cont=1;
        }
    }
    return -1;
}

void QuickSort(int *a, int N) {
    int l=0, r=N-1;
    QuickSortR(a, l, r);
}

void QuickSortR(int *a, int l, int r) {
    int q;
    if (r <= l)
        return;
    q = partition(a, l, r);
    QuickSortR(a, l, q-1);
    QuickSortR(a, q+1, r);
    return;
}

int partition (int *a, int l, int r) {
    int i, j;
    int x = a[r];
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

void Swap(int *a, int n1, int n2)
{
    int temp;
    temp  = a[n1];
    a[n1] = a[n2];
    a[n2] = temp;
    return;
}

int ITEMlt(int A, int B) {
    return (A < B);
}

int ITEMgt(int A, int B) {
    return (A > B);
}

int main()
{
    int i=0, v[M]={2,2,2,4,5,0,2,2,2,1}, maggioritario=0;

    maggioritario=majority(v,M);
    for(i=0;i<10;i++){
        printf("%d ", v[i]);
    }
    printf("\n");

    if(maggioritario!=-1){
        printf("L'elemento maggioritario esiste ed e' %d.\n", maggioritario);
    }
    else{
        printf("L'elemento maggioritario non esiste.\n");
    }
    return 0;
}
