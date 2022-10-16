#include <stdio.h>
#include <stdlib.h>
#include <math.h>

int gcd(int a, int b);

int main()
{
    int a, b, tmp, mcd;
    for(; ;){ //il ciclo prosegue finche' l'utente non inserisce 0 come primo valore da tastiera
        printf("Inserisci due numeri interi strettamente positivi di cui vuoi calcolare il massimo comun divisore:\n(Inserisci 0 per terminare il programma)\n");
        scanf("%d", &a);
        if(a==0)
            return 0;
        scanf("%d", &b);
        while(a<1||b<1){
            printf("Valori inseriti errati.\nInserisci due numeri interi strettamente positivi di cui vuoi calcolare il massimo comun divisore:\n(Inserisci 0 per terminare il programma)\n");
            scanf("%d", &a);
            if(a==0)
                return 0;
            scanf("%d", &b);
        }
        mcd=gcd(a,b);
        printf("Massimo comun divisore: %d\n", mcd);
    }
    return 0;
}

int gcd(int a, int b){
    int mcd, tmp;

    if(a<b) //per soddisfare la condizione a>b
        return gcd(b, a);

    if(a%b==0) //condizione di terminazione se il valore minore e' un sottomultiplo del maggiore
        return b;
    if(b==0) //condizione di terminazione
        return a;
//definizione ricorsiva del massimo comun divisore
    if(a%2==0 && b%2==0) // a pari, b pari
        return 2*gcd( a/2, b/2 );
    else if( a%2==1 && b%2==0 ) // a dispari, b pari
        return gcd( a, b/2 );
    else if( a%2==1 && b%2==1 ) // a dispari, b dispari
        return gcd( (a-b)/2, b );
    else if( a%2==0 && b%2==1 ) // a pari, b dispari
        return gcd( a/2, b);
}
