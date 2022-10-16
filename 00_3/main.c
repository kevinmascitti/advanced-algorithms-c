#include <stdio.h>
#include <stdlib.h>
#define MAX 30

void ruota(int v[30], int N, int P, int dir);

int main()
{
    int N=31, i=0, dir=1, pos=1;
    int ve[MAX];

    for(i=0;i<MAX;i++){
        ve[i]=0;
    }

    printf("Inserisci un valore N minore di 30:\n");
    while(N>30){
        scanf("%d", &N);
        if(N>30){
            printf("Errore.\nInserisci un valore N minore di 30:\n");
        }
    }

    printf("Inserisci il vettore di %d elementi:\n", N);
    for(i=0;i<N;i++){
        scanf("%d", &ve[i]);
    }

    while(dir==1||dir==-1){
        printf("Per effettuare una rotazione del vettore verso destra digita 1, altrimenti digita -1.\n");
        scanf("%d", &dir);
        if(dir!=1&&dir!=-1)
            return 0;
        printf("Inserisci il numero di posizoni di cui vuoi ruotare il vettore:\n");
        scanf("%d", &pos);
        while(pos>=N){
            pos=pos-N;
        }
        ruota(ve,N,pos,dir);
    }

    return 0;
}

void ruota(int v[30], int N, int P, int dir){
    int i=0, copia[P], j=0, k=0;

        if(dir==-1){
            P=N-P;
        }

        for(i=N-P;i<N;i++){
            copia[j]=v[i];
            j++;
        }

        j=0;
        for(i=N-P-1;i>=0;i--){
            v[P+i]=v[i];
        }

        for(i=0;i<P;i++){
            v[i]=copia[i];
        }

        printf("\nIl vettore e':\n\n");
        for(i=0;i<N;i++){
            printf("%d ", v[i]);
        }
        printf("\n\n");
}
