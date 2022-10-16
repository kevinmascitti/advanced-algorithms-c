#include <stdio.h>
#include <stdlib.h>
#define MAX 50

int alt(int m[][50], int i, int j);
int lar(int m[][50], int i, int j);

int main()
{
    int i=0, j=0, k=0, w=0, tmp=0, m[MAX][MAX], lettura=0, nr=0, nc=0,
        dx=1, dy=1, altezza, larghezza, area, altmax=0, larmax=0, areamax=0,
        ilarmax=0, jlarmax=0, ialtmax=0, jaltmax=0, iareamax=0, jareamax=0,
        alt_larmax=0, area_larmax=0, lar_altmax=0, area_altmax=0, lar_areamax=0, alt_areamax=0;
    FILE *fp;

/*inizializzo matrice*/
    for(i=0;i<MAX;i++){
        for(j=0;j<MAX;j++){
            m[i][j]=0;
        }
    }
    i=0;
    j=0;

/*salvo la matrice in memoria ricordando che il primo valore e' il numero di righe e il secondo e' quello delle colonne*/
    fp=fopen("matrice.txt","r");
    while(fscanf(fp, "%d", &tmp)!=EOF){
        lettura++;
        if(lettura==1){
            nr=tmp;
        }
        if(lettura==2){
            nc=tmp;
        }
        if(lettura>2){
            m[i][j]=tmp;
            j++;
        }
        if(lettura>2 && j==nc){
            i++;
            j=0;
        }
    }
    fclose(fp);

/*stampa matrice*/
    printf("\n");
    for(i=0;i<nr;i++){
        printf("   ");
        for(j=0;j<nc;j++){
                printf("%d   ", m[i][j]);
        }
        printf("\n\n");
    }
    printf("\n");

    for(i=0;i<nr;i++){
        for(j=0;j<nc;j++){

/*Se il numero nella casella vale 0, non fa parte di una regione; se vale 2 l'ho gia' controllata. In entrambi i casi, vado alla casella successiva.*/
            if(m[i][j]==0 || m[i][j]==2)
                continue;

            if(m[i][j]==1){
                m[i][j]=2;  /*segnalo che ho analizzato quella casella sostituendo il valore 1 con il 2*/

                altezza=alt(m,i,j);
                larghezza=lar(m,i,j);
                area=larghezza*altezza;

/*ricerca di massimo per l'altezza, la base e l'area*/
                if(altezza>altmax){
                        altmax=altezza;
                        ialtmax=i;
                        jaltmax=j;
                }
                if(larghezza>larmax){
                        larmax=larghezza;
                        ilarmax=i;
                        jlarmax=j;
                    }
                if(area>areamax){
                    areamax=area;
                    iareamax=i;
                    jareamax=j;
                }

/*Trasformo in 2 tutti i valori (obbligatoriamente uguali a 1, supposto corretto il formato della matrice da file)
che si trovano all'"interno" di un rettangolo di lati gia' controllati, i cui valori sono gia' stati trasformati in 2 dalle funzioni precedenti.*/
                for(w=i+1;w<i+dy;w++){
                    for(k=j+1;k<j+dx;k++){
                        m[w][k]=2;
                    }
                }

            }

        }
    }

/*Ora calcolo base, altezza e area per ognuna dele regioni che soddisfino il criterio di altezza, base e area massima.*/
    lar_altmax=lar(m,ialtmax,jaltmax);
    area_altmax=lar_altmax*altmax;

    alt_larmax=alt(m,ilarmax,jlarmax);
    area_larmax=larmax*alt_larmax;

    lar_areamax=lar(m,iareamax,jareamax);
    alt_areamax=alt(m,iareamax,jareamax);

    printf("Max base   : estr. sup. SX = <%d,%d> b = %d, h= %d, Area= %d. \n", ilarmax, jlarmax, larmax, alt_larmax, area_larmax);
    printf("Max altezza: estr. sup. SX = <%d,%d> b = %d, h= %d, Area= %d. \n", ialtmax, jaltmax, lar_altmax, altmax, area_altmax);
    printf("Max area   : estr. sup. SX = <%d,%d> b = %d, h= %d, Area= %d. \n", iareamax, jareamax, lar_areamax, alt_areamax, areamax);

    return 0;

}



int alt(int m[][50], int i, int j)
{
int dy=1, altezza=1;
/*Controllo verso il basso. Se non dovesse esserci lo zero,
ci sarebbe obbligatoriamente 1 perche' le righe sottostanti non le ho ancora controllate e non possono valere 2.*/
    while(m[i+dy][j]!=0){
            m[i+dy][j]=2;
            altezza++;
            dy++;
    }
    return altezza;
}



int lar(int m[][50], int i, int j)
{
int dx=1, larghezza=1;
/*Controllo verso destra. Se non dovesse esserci lo zero,
ci sarebbe obbligatoriamente 1 perche' le colonne a destra non le ho ancora controllate e non possono valere 2.*/
    while(m[i][j+dx]!=0){
            m[i][j+dx]=2;
            larghezza++;
            dx++;
    }
    return larghezza;
}
