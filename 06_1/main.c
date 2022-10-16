#include <stdio.h>
#include <stdlib.h>

typedef struct{
    int nodo1;
    int nodo2;
} arco;


int powerset_comb_semp(int* val, int n, int* sol, arco *a, int tot_archi);
int powerset_r(int* val, int n, int* sol, int i, int pos, int start, arco *a, int tot_archi);
int check (int* sol, arco *a, int i, int tot_archi);

int main()
{
    int N, E, i=0, count, *val, *sol;
    arco *a;
    FILE *fp;

    fp=fopen("grafo.txt","r");
    fscanf(fp, "%d %d", &N, &E);
    printf("Numero totale di nodi: %d\nNumero totale di archi: %d\n\nArchi:\n", N, E);
    a = (arco*) malloc ( E * sizeof(arco) );
    while( fscanf (fp, "%d %d", &a[i].nodo1, &a[i].nodo2) != EOF ){
        printf("%d %d\n", a[i].nodo1, a[i].nodo2);
        i++;
    }
    printf("\n");
    fclose(fp);

    val = (int*) malloc ( N * sizeof(int) );
    for(i=0; i<N; i++){
        val[i]=i;
    }
    sol = (int*) calloc ( N, sizeof(int) );
    count = powerset_comb_semp(val, N, sol, a, E);
    printf("\nVertex cover possibili: %d.\n", count);

    free(a);
    free(val);
    free(sol);

    return 0;
}

/*Utilizzo il powerset per elencare tutte le possibili soluzioni del problema.
Poi attraverso la funzione check, che restituisce un flag, verifico che i vettori di soluzioni
trovati siano effettivamente delle soluzioni accettabili per il problema dato oppure no.*/
int powerset_comb_semp(int* val, int n, int* sol, arco *a, int tot_archi){
   int count = 0, i;
   for(i = 1; i <= n; i++){ //questo ciclo for trova tutti i possibili sottoinsiemi di i elementi, quindi i va da 1 (el. min) a n (insieme stesso)
      count += powerset_r(val, n, sol, i, 0, 0, a, tot_archi);
   }
   return count;
}

int powerset_r(int* val, int n, int* sol, int i, int pos, int start, arco *a, int tot_archi){
    int count = 0, j, flag=0;

    if (pos == i){
        flag = check(sol, a, i, tot_archi);
        if(flag==1){
            printf("{ ");
            for (j = 0; j < i; j++)
                printf("%d ", sol[j]);
            printf("}\n");
            return 1;
        }
    }

    for (j = start; j < n; j++){
        sol[pos] = val[j];
        count += powerset_r(val, n, sol, i, pos+1, j+1, a, tot_archi);
    }

    return count;
}

/*condizione di controllo: analizzo ogni posizione del vettore sol di cardinalita' i.
Per ogni valore di sol, verifico quali archi 'copre'. Per ogni arco 'coperto', salvato nella struttura
i-esima del vettore di strutture a, inserisco un flag=1 alla posizione j-esima del vettore
dinamico v i cui valori iniziali sono 0 e la cui dimensione corrisponde al numero totale di archi.
A ciascun arco corrisponde dunque un valore 0 se l'arco non e' coperto dai nodi del vettore sol
e un valore 1 se invece lo è.
Alla fine, verifico se quella soluzione e' accettabile scandendo il vettore v, verificando che
in ogni posizione di esso ci sia 1. Se e' vero, i nodi del vettore sol sono accettabili e
sol e' un vertex cover del grafo G.*/

int check (int* sol, arco *a, int i, int tot_archi){
    int j, k, flag, *v;
    v = (int*) calloc ( tot_archi, sizeof(int) );

    for(j=0; j<i; j++){
        for(k=0; k<tot_archi; k++){
            if( (sol[j] == a[k].nodo1 || sol[j] == a[k].nodo2) && v[k]==0 )
                v[k]=1;
        }
    }

    flag=1;
    for(j=0; j<tot_archi; j++){
        if(v[j]!=1)
            flag=0;
    }

    if (flag==1)
        return 1;
    return 0;
}
