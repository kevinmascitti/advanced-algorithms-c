#include <stdio.h>
#include <stdlib.h>
#define MAXR 50

int alt(int m[][MAXR], int i, int j);
int lar(int m[][MAXR], int i, int j);

void leggiMatrice(int M[][MAXR], int size, int *righe, int *colonne);
int riconosciRegione(int M[][MAXR], int nr, int nc, int r, int c, int *base, int *height);

int main()
{
    int nr=0, nc=0, altezza, larghezza;
    int m[MAXR][MAXR], rett_trovato = 0, r = 0, c = 0;
    int *righe = &nr;
    int *colonne = &nc;
    int *base = &larghezza;
    int *height = &altezza;

    leggiMatrice (m, MAXR, righe, colonne);

/*si inseriscono da tastiera gli indici i e j di cui si vuole verificare se e' l'indice in alto a sinistra di un rettangolo*/
    printf("\nInserisci gli indici riga e colonna dove vuoi cercare un rettangolo.\n");
    scanf("%d %d", &r, &c);
    printf("Valore corrispondente agli indici dati: %d\n", m[r][c]);

    rett_trovato = riconosciRegione(m, nr, nc, r, c, base, height);
    if(rett_trovato != 0){
        printf("Rettangolo trovato. Indici <%d,%d>, base %d, altezza %d.\n", r, c, larghezza, altezza);
    }
    else{
        printf("Rettangolo non trovato in posizone con indici <%d,%d>.\n", r, c);
    }

    return 0;
}

//funzioni descritte nell'esercizio 1 del lab 2
int alt(int m[][MAXR], int i, int j)
{
int dy=1, altezza=1;
    while(m[i+dy][j]==1){
            m[i+dy][j]=2;
            altezza++;
            dy++;
    }
    return altezza;
}

int lar(int m[][MAXR], int i, int j)
{
int dx=1, larghezza=1;
    while(m[i][j+dx]==1){
            m[i][j+dx]=2;
            larghezza++;
            dx++;
    }
    return larghezza;
}

//nuove funzioni
void leggiMatrice(int M[][MAXR], int size, int *righe, int *colonne){
    int i=0, j=0, pos_i=0, pos_j=0, maxi=0, maxj=0;

    for(i=0;i<size;i++){
        for(j=0;j<size;j++){
            M[i][j]=0;
        }
    }
    i=0;
    j=0;
    printf("Inserisci i valori 0 o 1 nella matrice.\nInserisci un massimo di %d righe e colonne.\nInserisci un valore diverso per interrompere la riga.\n", size);
    for(i=0;i<size;i++){
        for(j=0;j<size;j++){
            scanf("%d", &M[i][j]);

            if(M[i][j]!=0 && M[i][j]!=1){   //se inserisco in posizione i,j un valore diverso da 0 e 1, interrompe la digitazione della data riga e rimangono tutti 0
                M[i][j]=0;
                break;
            }

            if(M[i][j]==1){                 //ricerco la posizone massima (in riga e in colonna) in cui ho inserito un 1, cosi' da ottenere il numero di righe e colonne effettivamente utilizzate
                pos_i=i;
                pos_j=j;
                if(pos_i>maxi)
                    maxi=pos_i;
                if(pos_j>maxj)
                    maxj=pos_j;
            }

        }
    }

    *righe=maxi+1;
    *colonne=maxj+1;

}


int riconosciRegione(int M[][MAXR], int nr, int nc, int r, int c, int *base, int *height){
    int find=0;

    if(M[r][c]==1){
        if(r==0 && c==0)
            find=1;
        else if(r!=0 && M[r-1][c]==0 && c==0)
            find=1;
        else if(r==0 && c!=0 && M[r][c-1]==0)
            find=1;
        else if(r!=0 && M[r-1][c]==0 && c!=0 && M[r][c-1]==0)
            find=1;
    }

    if(find==1){
        *height = alt(M,r,c);
        *base = lar(M,r,c);
    }

    return find;
}
