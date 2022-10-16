#include <stdio.h>
#include <stdlib.h>
#define MAX 30

//versione ottimizzata

int dimensione(int v[], int m);

int main () {
    int v[MAX], dimmax=0, dim=0, i=0, temp[MAX], flag=0, j=0, lunghezza=0, val=0;

    printf("Inserisci massimo 30 valori interi.\nDigita valore superiore a 100 per interrompere.\n");

    for(i=0;i<=MAX;i++){
        if(flag==0){
            scanf("%d", &val);
            if(val>100){
                flag=1;
                lunghezza=i-1;
                i=MAX;
            }
            else{
                v[i]=val;
            }
        }
    }

    printf("Il vettore e': ");
    for(i=0;i<=lunghezza;i++){
        printf("%d ", v[i]);
    }
    printf("\n");

    dimmax=dimensione(v, lunghezza);
    j=0, dim=0;

    for(i=0;i<=lunghezza;i++){
        if(v[i]==0){
            if(dim==dimmax){
                printf("Sottovettore:\n");
                for(j=0;j<dimmax;j++){
                    printf("%d ",temp[j]);
                }
                printf("\n");
            }
            else{
                for(j=0;j<=dim;j++){
                    temp[j]=0;
                }
            }
            j=0;
            dim=0;
        }
        if(v[i]!=0){
            temp[j]=v[i];
            j++;
            dim=j;
        }
    }
    return 0;
}
int dimensione(int v[], int m){
    int i=0, dimf=0, dimmaxf=0;
    for(i=0;i<=m;i++){
        if(v[i]!=0){
            dimf++;
        }
        if(v[i]==0||i==m){
            if(dimf>dimmaxf){
                dimmaxf=dimf;
            }
            dimf=0;
        }
    }
    return dimmaxf;
}

