#include <stdio.h>
#include <stdlib.h>

int **malloc2dR(int nr, int nc);
void free2d(int **m, int nr);

int main()
{
    int nr, nc, i, j, cas_bianche, cas_nere;
    int **m;
    int *b, *n;
    FILE *fp;

    fp=fopen("mat.txt", "r");
    fscanf(fp, "%d %d", &nr, &nc);
    m = malloc2dR(nr, nc);
    i=0; j=0;
    while(fscanf(fp, "%d", &m[i][j]) != EOF){
        if(j==nc-1){
            i++;
            j=0;
        }
        else{
            j++;
        }
    }
    fclose(fp);

//stampa matrice
    for(i=0; i<nr; i++){
        for(j=0; j<nc; j++){
            printf("%d ", m[i][j]);
        }
        printf("\n");
    }

/*determino il numero di caselle bianche e di caselle nere, assegnando arbitrariamente
alla prima casella (0,0) della matrice una casella bianca
se la matrice ha numero totale di caselle dispari, il numero dele caselle bianche
e' maggiore del numero di caselle nere di 1, altrimenti sono uguali*/
    if ( ((nr * nc) % 2) == 1 ){
        cas_bianche = (nr * nc) / 2 + 1;
        cas_nere = (nr * nc) / 2;
    }
    else{
        cas_bianche = (nr * nc) / 2;
        cas_nere = (nr * nc) / 2;
    }
    b = (int*) malloc( cas_bianche * sizeof(int) );
    n = (int*) malloc( cas_nere * sizeof(int) );

    separa(m, nr, nc, b, n);

    free2d(m, nr);
    return 0;
}

int **malloc2dR(int nr, int nc){
    int **m;
    int i=0;
    m=malloc(nr* sizeof(int*) );
    for(i=0; i<nr; i++){
        m[i]=malloc(nc* sizeof(int) );
    }
    return m;
}

void free2d(int **m, int nr){
    int i;
    for(i=0; i<nr; i++){
        free(m[i]);
    }
    free(m);
}

void separa(int **mat, int nr, int nc, int *b, int *n){
    //prima casella bianca (indici (0,0), somma degli indici = 0+0=0 (pari) )
    //di conseguenza tutte le caselle la cui somma degli indici e' pari sono bianche, analogamente per le nere
    int i, j, k=0, w=0;

    //salvo il 'colore' della casella i, j. Se bianca, nel vettore b, altrimenti nel vettore n
    for(i=0; i<nr; i++){
        for(j=0; j<nc; j++){
            if( ( (i+j) % 2 ) == 0){
                b[k] = mat[i][j];
                k++;
            }
            else{
                n[w] = mat[i][j];
                w++;
            }
        }
    }

    printf("\nElementi bianchi:   ");
    for(i=0; i<k; i++){
        printf("%d ", b[i]);
    }
    free(b);
    printf("\nElementi neri:   ");
    for(i=0; i<w; i++){
        printf("%d ", n[i]);
    }
    free(n);

}
