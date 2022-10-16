#include <stdio.h>
#include <stdlib.h>
#define MAX 50
#define nome_file1 "tiles.txt"
#define nome_file2 "board.txt"

typedef struct tiles{
    char colore1;
    int pt1;
    char colore2;
    int pt2;
} tubi_t;

typedef struct board{
    int num;        //indica il numero della posizione della tesera nell'elenco completo delle tessere
    tubi_t *indice; //puntatore a elemento dell'elenco nella lista completa delle tessere
    int rot;        //indica la rotazione della cella
} cella_t;


cella_t **malloc2dR(int r, int c);
void free2d(cella_t **m, int r);
void stampaElenco(tubi_t *a, int r);
void stampaScacchiera(cella_t **a, int r, int c);
void disp_sempl(int pos, tubi_t *val, cella_t **sol, int *mark, int n, int k, int c_tot, int r, int c, int r_tot);//r_tot inutile
cella_t board(tubi_t *val, int i, int rotazione);
int calcoloPunti(cella_t **sol, int r, int c);

int punti_max=0; //variabili globali utilizzate per ritornare la soluzione dalle disp semplici
int ricorsione=0;
cella_t **sol_max;

int main()
{
//T numero di tubi totali presenti nel file tiles.txt
//R e C dimensioni della scacchiera in esame
//occupate indica il numero di caselle occupate nella scacchiera letta da file e indica, nella funzione disp_sempl, la pos
//mark e' un vettore creato in relazione al vettore di tubi. Ad ogni posizione i, contiene 0 se il tubo i-esimo e' gia' utilizzato o meno

    int i, j, T, R, C, occupate, *mark, punti;
    char tmp[MAX], colore;
    tubi_t *tubi; //vettore di tubi (elenco totale)
    cella_t **m;
    FILE *fp=NULL;

    fp=fopen(nome_file1, "r");
    if(fp==NULL){
        printf("Errore file %s.\n", nome_file1);
        return -1;
    }
    fscanf(fp, "%d\n", &T);
    tubi=(tubi_t*)malloc(T*sizeof(tubi_t));
    mark=(int*)calloc(T,sizeof(int));
    for(i=0; i<T; i++){
        fgets(tmp,"%s",fp);
        sscanf(tmp,"%c %d %c %d",&tubi[i].colore1,&tubi[i].pt1,&tubi[i].colore2,&tubi[i].pt2);
    }
    fclose(fp);
    stampaElenco(tubi, T);

    fp=fopen(nome_file2, "r");
    if(fp==NULL){
        printf("Errore file %s.\n", nome_file2);
        return -1;
    }
    fgets(tmp,"%s",fp);
    sscanf(tmp, "%d %d", &R, &C);
    m=malloc2dR(R, C);
    sol_max=malloc2dR(R, C);
    occupate=R*C;
    for(i=0;i<R;i++){
        for(j=0;j<C;j++){
            fscanf(fp, "%d/%d", &m[i][j].num, &m[i][j].rot);
            if( (m[i][j].num==-1 && m[i][j].rot!=-1) || (m[i][j].num!=-1 && m[i][j].rot==-1) ){ //errore se un valore e' -1 e l'altro no
                printf("Valori errati nel file %s.\n", nome_file2);
                return -1;
            }
            if(m[i][j].num==-1 && m[i][j].rot==-1){ //se la cella e' vuota, e' disponibile e diminuisco il numero di caselle tot occupate
                m[i][j].indice=NULL;
                occupate--;
            }
            else{ //altrimenti analizzo la rotazione della cella e inizializzo i valori della casella in base all'indice a cui punta nel vettore di tessere
                if(m[i][j].rot==0)
                    m[i][j].indice=&tubi[(m[i][j].num)];
                if(m[i][j].rot==1){ //se la tessera e' ruotata, allora inverto i colori e i punti dei due tubi presenti nella tessera puntata nell'vettore di tessere
                    m[i][j].indice=&tubi[(m[i][j].num)];
                    colore=m[i][j].indice->colore1;
                    m[i][j].indice->colore1=m[i][j].indice->colore2;
                    m[i][j].indice->colore2=colore;
                    punti=m[i][j].indice->pt1;
                    m[i][j].indice->pt1=m[i][j].indice->pt2;
                    m[i][j].indice->pt2=punti;
                }
                mark[(m[i][j].num)]=1;
            }
        }
        fscanf(fp,"\n");
    }
    fclose(fp);
    printf("Scacchiera iniziale:\n");
    stampaScacchiera(m, R, C);

    disp_sempl(occupate, tubi, m, mark, T, R*C, C, 0, 0, R);
    printf("\nPunteggio massimo: %d\n\n", punti_max);
    stampaScacchiera(sol_max, R, C);

    free(tubi);
    free2d(m, R);
    free2d(sol_max, R);

    return 0;
}

cella_t **malloc2dR(int r, int c){
    cella_t **m;
    int i;
    m=(cella_t*)malloc(r*sizeof(cella_t));
    for(i=0;i<r;i++)
        m[i]=(cella_t*)malloc(c*sizeof(cella_t));
    return m;
}

void free2d(cella_t **m, int r){
    int i;
    for(i=0;i<r;i++)
        free(m[i]);
    free(m);
    return;
}

void stampaElenco(tubi_t *a, int r){
    int i;
    printf("Elenco completo delle tessere esistenti:");
    for(i=0; i<r; i++){
        printf("%c %d %c %d\n", a[i].colore1, a[i].pt1, a[i].colore2, a[i].pt2);
    }
    printf("\n");
    return;
}

void stampaScacchiera(cella_t **a, int r, int c){
    int i, j;
    for(i=0; i<r; i++){
        for(j=0; j<c; j++){
            printf("%d/%d ", (a[i][j].num), a[i][j].rot);
        }
        printf("\n");
    }
    return;
}

void disp_sempl(int pos, tubi_t *val, cella_t **sol, int *mark, int n, int k, int c_tot, int r, int c, int r_tot) {
    int i, j, punti=0;

    if (pos >= k){
        punti=calcoloPunti(sol, r_tot, c_tot);
        if(punti>punti_max){
            punti_max=punti;
            for(i=0; i<r_tot; i++){
                for(j=0; j<c_tot; j++){
                    sol_max[i][j]=sol[i][j];
                }
            }
        }
        return;
    }

    for (i=0; i<n; i++) {
        if(sol[r][c].num==-1){
            if (mark[i] == 0) {
                mark[i] = 1;
                sol[r][c] = board(val, i, 0);
                disp_sempl(pos+1, val, sol, mark, n, k, c_tot, r, c, r_tot);
                //rotazione della casella
                sol[r][c] = board(val, i, 1);
                disp_sempl(pos+1, val, sol, mark, n, k, c_tot, r, c, r_tot);
                mark[i]=0; //backtrack
                sol[r][c].num=-1;
                sol[r][c].indice=NULL;
                sol[r][c].rot=-1;
            }
        }
        else{ //trovo la cella vuota incrementando gli indici r e c e ricordandomi della i che aumenterebbe a ogni ciclo quindi la decremento
            if(c!=c_tot)
                c++;
            else{
                r++;
                c=0;
            }
            i--;
        }
    }
    return;
}

cella_t board(tubi_t *val, int i, int rotazione){
    cella_t a;
    char colore;
    int punti;
    if(rotazione==0){
        a.num=i;
        a.indice=&(val[i]);
        a.rot=0;
    }
    else if(rotazione==1){ //scambio i valori di colori e punti cosi' da avere il colore e i punti da prendere in considerazione sempre come primi della cella
        a.num=i;
        a.indice=&(val[i]);
        colore=a.indice->colore1;
        a.indice->colore1=a.indice->colore2;
        a.indice->colore2=colore;
        punti=a.indice->pt1;
        a.indice->pt1=a.indice->pt2;
        a.indice->pt2=punti;
        a.rot=1;
    }
    return a;
}

int calcoloPunti(cella_t **sol, int r, int c){
    int i, j, tot=0, check;
    for(i=0; i<r; i++){ //calcolo per righe
        check=1;
        for(j=0; j<c; j++){
            if(j>0 && sol[i][j].indice->colore1!=sol[i][j-1].indice->colore1){ // verifico che non ci siano lettere diverse in una riga
                check=0;
            }
        }
        if(check==1){ //COLORE 1 E PUNTI 1
            for(j=0; j<c; j++)
                tot+=sol[i][j].indice->pt1;
        }
    }
    for(j=0; j<c; j++){ //calcolo per colonne
        check=1;
        for(i=0; i<r; i++){
            if(i>0 && sol[i][j].indice->colore2!=sol[i-1][j].indice->colore2){ // verifico che non ci siano lettere diverse in una colonna
                check=0;
            }
        }
        if(check==1){ //COLORE 2 E PUNTI 2
            for(i=0; i<r; i++)
                tot+=sol[i][j].indice->pt2;
        }
    }
    return tot;
}

