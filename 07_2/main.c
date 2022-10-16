#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>
#define maxriga 20

typedef struct{
    char p;
    int tot;
} pietra;

typedef struct{
    int comp[200];
    int val;
} collana;

void disp_ripet(int pos, pietra *val, int *sol, int n, int k, int *gemme, int res, int ricorrenza, int max_rip, int *valori);
int check1(int *sol, int pos, int i);

typedef struct wrapSol{
    collana coll;
    int max_val;
    int max_lun;
    int usate[4];
} best_t;

best_t best; //variabile globale usata per memorizzare e ritornare la soluzione della collana a maggior valore

int main()
{
    int z, s, r, t, i, lettura=0, tot_test, tot, k, gemme[4], valori[4], max_rip;
    pietra v[4];
    int *sol;
    char tmp[100];
    char nome_file[maxriga]="test.txt";
    FILE *fp=fopen(nome_file, "r");

    v[0].p='z';     //ad ogni posizione del vettore corrisponde un tipo di pietra diverso
    v[1].p='s';
    v[2].p='r';
    v[3].p='t';

    if (fp==NULL)   return -1;
    fgets(tmp, "%s", fp);
    sscanf(tmp, "%d", &tot_test);
    while(fgets(tmp, "%s", fp)!=NULL){

        sscanf(tmp, "%d %d %d %d %d %d %d %d %d", &z, &r, &t, &s, &valori[0], &valori[2], &valori[3], &valori[1], &max_rip);
        v[0].tot=gemme[0]=z;
        v[1].tot=gemme[1]=s;
        v[2].tot=gemme[2]=r;
        v[3].tot=gemme[3]=t;
        lettura++;
        tot=z+s+r+t;

        for(i=0; i<tot; i++) //inizializzazione della collana a un numero che non corrisponde a nessuna pietra
            best.coll.comp[i]=-1;

        printf("TEST #%d\n", lettura);
        for(k=0; k<tot; k++){ //ciclo per analizzare tutte le collane generate con disp ripetute e utilizzando pruning
            sol = (int*) calloc( k, sizeof(int) );  //nel vettore di interi sol ci metto il numero corrispondente alla pietra
            disp_ripet(0, v, sol, 4, k, gemme, 0, 0, max_rip, valori);  //effettuo le disposizioni ripetute con pruning di check
            free(sol);
        }
        printf("Zaffiro=%d, rubino=%d, topazio=%d, smeraldo=%d, TOT=%d, Ripetizioni massime=%d.\n", best.usate[0], best.usate[2], best.usate[3], best.usate[1], best.usate[0]+best.usate[2]+best.usate[3]+best.usate[1], max_rip);
        printf("Collana di valore massimo %d e di lunghezza %d.\n", best.max_val, best.max_lun);
        for (i=0; i<k; i++)
            if(best.coll.comp[i]!=-1)
                printf("%c", v[best.coll.comp[i]].p);
        printf("\n\n");

        best.max_val=0;
        best.max_lun=0;

        free(sol);
    }
    if(tot_test!=lettura){
        printf("Errore file.");
        return -1;
    }
    fclose(fp);

    return 0;
}

void disp_ripet(int pos, pietra *val, int *sol, int n, int k, int *gemme, int res, int ricorrenza, int max_rip, int *valori) {
    int i, corrente=0, ultima=0, valore=0;
    if (pos >= k) { //controllo su zaffiri e smeraldi, se lo supera e il valore della collana e' maggiore del valore massimo trovato, aggiona la collana massima
        if(val[0].tot-gemme[0] <= val[1].tot-gemme[1]){
            valore=valori[0]*(val[0].tot-gemme[0])+valori[2]*(val[2].tot-gemme[2])+valori[3]*(val[3].tot-gemme[3])+valori[1]*(val[1].tot-gemme[1]);
            if (valore>=best.max_val){
                best.max_val=valore;
                best.max_lun=pos;
                best.usate[0]=val[0].tot-gemme[0]; //val.tot e' il num tot di un tipo di pietra, mentre gemme rappresenta le pietre di un certo tipo rimaste
                best.usate[1]=val[1].tot-gemme[1];
                best.usate[2]=val[2].tot-gemme[2];
                best.usate[3]=val[3].tot-gemme[3];
                for(i=0; i<k; i++)
                    best.coll.comp[i]=sol[i]; //Il campo comp rappresenta la composizione con le pietre contrassegnate dai numeri da 0 a 3, inclusi.
            }
        }
        return;
    }
    for (i = 0; i < n; i++) {
        if(gemme[i]>0){
            if(pos==0 || check1(sol, pos, i)==1){
                //calcolo della ricorrenza 'consecutiva' di un determinato tipo di pietra che deve essere minore o uguale di max_rip
                corrente=i;
                if(pos==0)
                    ultima=corrente;
                else
                    ultima=sol[pos-1];
                if(corrente==ultima)
                    ricorrenza++;
                else
                    ricorrenza=1;
                if(ricorrenza<=max_rip){
                    gemme[i]--;
                    sol[pos] = i;
                    disp_ripet(pos+1, val, sol, n, k, gemme, res, ricorrenza, max_rip, valori);
                    gemme[i]++;
                }
            }
        }
    }
    return;
}

int check1(int *sol, int pos, int i){ //controllo se posso inserire quella determinata pietra, rispetto alla precedente pietra inserita
    switch(i){
    case 0:   if(sol[pos-1]==0 || sol[pos-1]==3) //zaffiro
                    return 1;
                break;
    case 1:   if(sol[pos-1]==1 || sol[pos-1]==2) //smeraldo
                    return 1;
                break;
    case 2:   if(sol[pos-1]==0 || sol[pos-1]==3) //rubino
                    return 1;
                break;
    case 3:    if(sol[pos-1]==1 || sol[pos-1]==2) //topazio
                    return 1;
                break;
    default:    printf("Errore nella funzione void check1.\n");
                break;
    }
    return 0;
}
