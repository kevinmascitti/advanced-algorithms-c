#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#define max 256
#define MAX 5

typedef struct{
    int tot;
    char brano[MAX][max];
} amico;

int main()
{
    int i=0, j=0, amici, count=0;
    char **sol;
    amico *a;
    FILE *fp;

    //salvo il contenuto del file in un vettore di strutture, di tipo amico, allocato dinamicamente
    //la cui i-esima struct contiene il numero intero di brani scelti dall'amico i e i rispettivi titoli

    fp=fopen("brani.txt", "r");
    fscanf(fp, "%d", &amici);
    a = (amico*) malloc ( amici * sizeof(amico) );

    for(i=0; i<amici; i++){
        fscanf(fp, "%d", &a[i].tot);
        for(j=0; j<a[i].tot; j++){
            fscanf(fp, "%s", a[i].brano[j]);
        }
    }
    fclose(fp);

    sol = (char**) malloc ( MAX * sizeof(char*) );
    for(i=0; i<amici; i++){
        sol[i] = (char*) malloc ( 256 * sizeof(char) );
    }
    count = princ_molt(0, a, sol, MAX, count);
    printf("\nNumero di combinazioni totali: %d.\n", count);
    free(a);
    for(i=0; i<MAX; i++)
        free(sol[i]);
    free(sol);

    return 0;
}

//eseguo il principio di moltiplicazione sugli elementi del multiinsieme per stampare tutte le possibili soluzioni
int princ_molt(int pos, amico *val, char **sol, int n, int count){
    int i;

    if(pos>=n){
        for(i=0; i<n; i++){
            printf("%s ", sol[i]);
        }
        printf("\n");
        return count+1;
    }

    for(i=0; i<val[pos].tot; i++){
        strcpy(sol[pos], val[pos].brano[i]);
        count = princ_molt(pos+1, val, sol, n, count);
    }
    return count;
}
