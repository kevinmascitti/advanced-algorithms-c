#include <stdio.h>
#include <stdlib.h>
#define MAX 30

void ruota(int v[MAX], int N, int P, int dir);

int main()
{
    int i=0, j=0, nr=0, nc=0, numero=0, m[MAX][MAX], indice=0, posizioni=0, stop=0, valid=0, vet=0, dir=0, vettore[MAX];
    char nome_file[21], car, string[101], selettore[8], direzione[9];
    FILE *fp;

    printf("Inserisci il nome del file:\n");
    scanf("%s", nome_file);

    fp=fopen(nome_file, "r");
    fscanf(fp, "%d %d", &nr, &nc);
    while(fscanf(fp, "%d%c", &numero, &car) != EOF){
        m[i][j]=numero;
        j++;
        if(car=='\n'){
            i++;
            j=0;
        }
    }
    fclose(fp);

    printf("\n");
    for(i=0;i<nr;i++){
        for(j=0;j<nc;j++){
                printf("  %d", m[i][j]);
        }
        printf("\n");
    }

    while(stop==0){
        printf("\nScegli quali righe o colonne vuoi ruotare, la direzione di rotazione e il numero di posizioni.\n");
        printf("Utilizza il formato <selettore> <indice> <direzione> <posizioni>\nPer il selettore, digita riga, colonna o fine.\nPer la direzione, digita destra, sinistra, su o giu.\n\n");
        valid=0;

        while(valid==0){
            printf("Selettore: ");
            scanf("%s", selettore);
            if(strcmp(selettore, "riga")==0){
                valid=1;
                vet=1;
            }
            else if(strcmp(selettore, "colonna")==0){
                valid=1;
                vet=2;
            }
            else if(strcmp(selettore, "fine")==0){
                stop=1;
                break;
            }
            else{
                printf("Selettore non valido. Riprova.\n");
                valid=0;
            }
        }

        while(valid==1){
            printf("Massimo indice di riga: %d. Massimo indice di colonna: %d.\n", nr-1, nc-1);
            printf("Inserisci indice di %s: ", selettore);
            scanf("%d", &indice);
            if(vet==1 && indice>=nr){
                printf("Indice di %s non valido. Riprova.\n", selettore);
                valid=1;
            }
            else if(vet == 2 && indice>=nc){
                printf("Indice di %s non valido. Riprova.\n", selettore);
                valid=1;
            }
            else{
                valid=2;
            }
        }

        while(valid==2){
            printf("Direzione di spostamento della %s di indice %d: ", selettore, indice);
            scanf("%s", direzione);
            if(strcmp(direzione, "sinistra")==0){
                valid=3;
                dir=-1;
            }
            else if(strcmp(direzione, "destra")==0){
                valid=3;
                dir=1;
            }
            else if(strcmp(direzione, "su")==0){
                valid=3;
                dir=-1;
            }
            else if(strcmp(direzione, "giu")==0){
                valid=3;
                dir=1;
            }
            else{
                printf("Direzione non valida. Riprova.\n");
                valid=2;
            }
        }

        if(valid==3){
            printf("Posizioni verso %s: ", direzione);
            scanf("%d", &posizioni);
            if(vet==1){
                while(posizioni>=nr){
                    posizioni=posizioni-nr;
                }
            }
            else if(vet==2){
                while(posizioni>=nc){
                    posizioni=posizioni-nc;
                }
            }

            if(vet==1){
                for(j=0;j<nc;j++){
                    vettore[j]=m[indice][j];
                }
            }
            else if(vet==2){
                for(i=0;i<nr;i++){
                    vettore[i]=m[i][indice];
                }
            }

            if(vet==1){
                ruota(vettore, nr, posizioni, dir);
            }
            else if(vet==2){
                ruota(vettore, nc, posizioni, dir);
            }

            if(vet==1){
                for(j=0;j<nc;j++){
                    m[indice][j]=vettore[j];
                }
            }
            else if(vet==2){
                for(i=0;i<nr;i++){
                    m[i][indice]=vettore[i];
                }
            }

            printf("\n");
            for(i=0;i<nr;i++){
                for(j=0;j<nc;j++){
                    printf("  %d", m[i][j]);
                }
                printf("\n");
            }
        }
    }

    return 0;
}


void ruota(int v[MAX], int N, int P, int dir){
    int i=0, copia[P], j=0, k=0;

        if(dir==-1){
            P=N-P;
        }

        for(i=N-P;i<N;i++){
            copia[j]=v[i];
            j++;
        }

        j=0;
        for(i=N-P-1;i>=0;i--){
            v[P+i]=v[i];
        }

        for(i=0;i<P;i++){
            v[i]=copia[i];
        }
}
