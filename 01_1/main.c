#include <stdio.h>
#include <stdlib.h>
#define MAX 20

int squadra(int m[5][5], int giorno, int numsq);
int main()
{
    int i=0, j=0, nsquadre=0, ngiorni=0, sum[MAX], max=0, indice[MAX];
    char temp[50];
    FILE *fp;
    for(i=0;i<MAX;i++){
        sum[i]=0;
        indice[i]=0;
    }
    fp=fopen("partite.txt","r");

    fgets(temp,"%s",fp);
    sscanf(temp, "%d %d", &nsquadre, &ngiorni);
    int ma[nsquadre][ngiorni];
    i=0;
    while(fscanf(fp,"%d",&ma[i][j])!=EOF){
        j++;
        if(j==ngiorni){
            i++;
            j=0;
        }
    }

    fclose(fp);

    for(j=0;j<ngiorni;j++){
        for(i=0;i<nsquadre;i++){
            sum[i]=sum[i]+ma[i][j];
        }
        for(i=0;i<nsquadre;i++){
            if(sum[i]>max){
                max=sum[i];
                indice[j]=i;
            }
        }
        max=0;
    }

    for(j=0;j<ngiorni;j++){
            printf("Giornata numero %d. Squadra vincitrice numero %d.\n",j+1,indice[j]+1);
    }

    return 0;
}
