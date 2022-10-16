#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define maxriga 20

typedef struct{
    char p;
    int tot;
} pietra;

int disp_ripet(int pos, pietra *val, int *sol, int n, int k, int *gemme, int res);
int check1(int *sol, int pos, int i);
void pietreusate(char sol, int *gemme);
int check2(int *gemme, pietra val);
void backtrack(int *usate, char *sol, int pos);

int main()
{
    int z, s, r, t, i, lettura=0, tot_test, tot, k, gemme[4];
    pietra v[4];
    int *sol;
    char nome_file[maxriga]="easy_test.txt";
    FILE *fp=fopen(nome_file, "r");

    v[0].p='z'; //ad ogni posizione del vettore corrisponde un tipo di pietra diverso
    v[1].p='s';
    v[2].p='r';
    v[3].p='t';

    if (fp==NULL)   return -1;
    fscanf(fp, "%d", &tot_test);
    while(fscanf(fp,"%d %d %d %d", &z, &r, &t, &s)!=EOF){ //nel file ono scritti in ordine diverso da come sono inseriti nel vettore
        v[0].tot=gemme[0]=z;
        v[1].tot=gemme[1]=s;
        v[2].tot=gemme[2]=r;
        v[3].tot=gemme[3]=t;
        lettura++;
        tot=z+s+r+t;
        printf("TEST #%d\n", lettura);
        for(k=tot; k>0; k--){ //ciclo da lunghezza massima a minima finche' non ne trovo una
            sol = (int*) calloc( k, sizeof(int) ); //nel vettore di interi sol ci metto il numero corrispondente alla pietra
            if(disp_ripet(0, v, sol, 4, k, gemme, 0)==1) //effettuo le disposizioni ripetute con pruning di check
                break;
            free(sol);
        }
        printf("Zaffiro=%d, rubino=%d, topazio=%d, smeraldo=%d, TOT=%d\n", v[0].tot-gemme[0], v[2].tot-gemme[2], v[3].tot-gemme[3], v[1].tot-gemme[1], v[0].tot-gemme[0]+v[2].tot-gemme[2]+v[3].tot-gemme[3]+v[1].tot-gemme[1]);
        printf("Collana massima di lunghezza: %d.\n\n", k);
        for (i=0; i<k; i++)
            printf("%c", v[sol[i]].p);
        printf("\n\n");
    }
    if(tot_test!=lettura){
        printf("Errore file.");
        return -1;
    }
    fclose(fp);

    return 0;
}

int disp_ripet(int pos, pietra *val, int *sol, int n, int k, int *gemme, int res) {
    int i;
    if (pos >= k) {
        return 1;
    }
    for (i = 0; i < n; i++) {
        if(gemme[i]>0){
            if(pos==0 || check1(sol, pos, i)==1){
                gemme[i]--;
                sol[pos] = i;
                res=disp_ripet(pos+1, val, sol, n, k, gemme, res);
                if(res==1)
                    return 1;
                gemme[i]++;
            }
        }
    }
    return 0;
}

int check1(int *sol, int pos, int i){ //controllo se posso inserire quella determinata pietra, rispetto alla precedente pietra inserita
    switch(i){
    case 0:   if(sol[pos-1]==0 || sol[pos-1]==2)
                    return 1;
                break;
    case 1:   if(sol[pos-1]==1 || sol[pos-1]==3)
                    return 1;
                break;
    case 2:   if(sol[pos-1]==1 || sol[pos-1]==3)
                    return 1;
                break;
    case 3:    if(sol[pos-1]==0 || sol[pos-1]==2)
                    return 1;
                break;
    default:    printf("Errore nella funzione void check1.\n");
                break;
    }
    return 0;
}
