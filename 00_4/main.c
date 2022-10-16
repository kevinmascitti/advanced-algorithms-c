#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include <ctype.h>
#include <string.h>
#define MAX 20

int main()
{
    int i=0, nr=0, nc=0, riga=0, parola=0, sum=0, dim=0, k=0, minimo=0, posi=0, posj=0, max=0,
                    w=0, colonna=0, ciclo=0, j=0, su[MAX][MAX]={0};
    char nfile[20+1], temp[20+1];
    FILE *fp;

    printf("Nome file:\n");
    scanf("%s", nfile);

    fp=fopen(nfile, "r");
    fgets(temp,"%s",fp);
    sscanf(temp, "%d %d", &nr, &nc);
    int m[nr][nc];
    while(fscanf(fp,"%d",&m[i][j])!=EOF){
        j++;
        if(j==nc){
            i++;
            j=0;
        }
    }
    fclose(fp);

    if(nr>=nc)
        minimo=nc;
    if(nr<nc)
        minimo=nr;

    while(dim!=100){
        printf("Inserisci un valore compreso tra 1 e %d. Inserisci 100 per interrompere.\n", minimo);
        scanf("%d", &dim);

        if(dim>=1 && dim<=minimo){
            ciclo=1;
        }
        else{
            ciclo=0;
        }

        if(ciclo!=0){
            for(i=0;i<=nr-dim;i++){
                for(j=0;j<=nc-dim;j++){
                    su[0][0]=0;
                    for(k=i;k<i+dim;k++){
                        for(w=j;w<j+dim;w++){
                            printf("%d ", m[k][w]);
                            su[i][j]=su[i][j]+m[k][w];
                        }
                        printf("\n");
                    }
                    printf("\n");
                    if(i==0 && j==0){
                        max=su[i][j];
                        posi=0;
                        posj=0;
                    }
                    else{
                        if(j!=0){
                            if(su[i][j]>su[i][j-1]){
                                max=su[i][j];
                                posi=i;
                                posj=j;
                            }
                        }
                        else{
                            if(su[i][j]>su[i-1][nc-dim]){
                                max=su[i][j];
                                posi=i;
                                posj=j;
                            }
                        }
                    }
                }
            }
            printf("Matrice con somma valori piu' alta = %d :\n\n", max);
            for(k=posi;k<posi+dim;k++){
                for(w=posj;w<posj+dim;w++){
                    printf("%d ", m[k][w]);
                }
                printf("\n");
            }
            printf("\n");
        }
        if(ciclo==0)
            printf("Valore inserito non valido.\n\n");
    }
    return 0;
}
