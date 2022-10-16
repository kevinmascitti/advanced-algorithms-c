#include <stdio.h>
#include <stdlib.h>

void stampCodifica(void *p, int size, int endian);

int main()
{
    int i=0, j=0, pos=0, sizef, sized, sizeld, intero=1, uno=1, big=0, ciclo=0;
    float af=0;
    double ad=0;
    long double ald=0;
    char num[200];


/*utilizzo gli operatori bitwise per confrontare il numero intero
scelto da me ('intero', letto utilizzando un puntatore di tipo unsigned
char) e il numero 1 (nella variabile intera chiamata 'uno') codificato
su 4 byte (32bit). Confronto quindi il primo byte (8 bit) di 'intero' (presenti
in c[0]) con il primo byte del numero 'uno'. Ho assegnato ad 'intero' il numero 1
cosi' il confronto, effettutato tramite l'operatore AND bit a bit,
mi ritorna 1 se il numero 1 si trova nell'ultima posizione
dell'indirizzo di memoria (littleEndian), altrimenti ritorna 0 (bigEndian)*/

    unsigned char *ch=(unsigned char*) &intero;
    if(ch[0] & uno == 1)
        big=0;
    else
        big=1;
    printf("Il calcolatore lavora in %s.\n", (big==1)? "bigEndian":"littleEndian");

    printf("Inserisci un numero reale.\n");
    scanf("%s", num);
    printf("\n\n");
    sscanf(num, "%f", &af);
    sscanf(num, "%lf", &ad);
    sscanf(num, "%Lf", &ald);

    sizef=sizeof(af);
    sized=sizeof(ad);
    sizeld=sizeof(ald); //=12 byte sul mio calcolatore

    printf("Dimensioni in byte del numero in aritmetica float: %d (%d bit).\n", sizef, sizef*8);
    printf("Dimensioni in byte del numero in aritmetica double: %d (%d bit).\n", sized, sized*8);
    printf("Dimensioni in byte del numero in aritmetica long double: %d (%d bit).\n\n\n", sizeld, sizeld*8);

    printf("FLOAT\nBit di segno:        ");
    stampaCodifica( (void *) &af, sizef, big);
    printf("\n\n\n");
    printf("DOUBLE\nBit di segno:        ");
    stampaCodifica( (void *) &ad, sized, big);
    printf("\n\n\n");
    printf("LONG DOUBLE\nBit di segno:        ");
    stampaCodifica( (void *) &ald, sizeld, big);
    printf("\n\n\n");

    return 0;
}

/*Nel caso del long double il primo bit della mantissa e' un 1. Dopo aver chiesto chiarimenti al professore,
        mi e' stato spiegato che deriva auomaticamente dallo standard.*/

void stampaCodifica(void *p, int size, int endian){
    int i=0, j=0, pos=0, end=0;

    unsigned char *c=(unsigned char*)p;

    if(size==sizeof(long double))    //evito i bit di padding che si trovano negli ultimi (2, nel mio caso) byte del numero in formato long double
            size=10;

/*Se lavoro in little endian, i byte sono salvati in memoria dal meno significativo al piu' significativo,
quindi l'indice i inizia da size-1 e punta all'ultimo vettore di char (in cui ci sono gli 8 bit), cosi'
da stampare poi i bit in ordine, dal MSB al LSB.*/

    if(endian==0){
        for(i=size-1;i>=0;i--){
            for(j=7;j>=0;j--){
                    printf("%d", (c[i]>>j) & 1);
                    switch (size){
                        case sizeof(float):
                              if ( i == size-1 && j == 7 )
                                    printf("\nBit di esponente:    ");
                              if ( i == size-2 && j == 7 )
                                    printf("\nBit di mantissa:     ");
                              break;
                         case sizeof(double):
                              if ( i == size-1 && j == 7 )
                                    printf("\nBit di esponente:    ");
                              if ( i == size-2 && j == 4 )
                                    printf("\nBit di mantissa:     ");
                              break;
                         case 10:
                              if ( i == size-1 && j == 7 )
                                    printf("\nBit di esponente:    ");
                              if ( i == size-2 && j == 0 )
                                    printf("\nBit di mantissa:     ");
                              break;
                    }
            }
        }
    }

/*Se lavoro in bigEndian, i byte sono salvati in memoria dal piu' significativo al
meno significativo.*/

    else{
        if(size==10){   //evito i bit di padding che si trovano nei primi (2, nel mio caso) byte del numero in long double
            pos=2;
            end=size+2;
        }
        else{
            pos=0;
            end=size;
        }
        for(i=pos;i<end;i++){
            for(j=7;j>=0;j--){
                    printf("%d", (c[i]>>j) & 1);
                    switch (size){
                        case sizeof(float):
                              if ( i == 0 && j == 7 )
                                    printf("\nBit di esponente:    ");
                              if ( i == 1 && j == 7 )
                                    printf("\nBit di mantissa:     ");
                              break;
                         case sizeof(double):
                              if ( i == 0 && j == 7 )
                                    printf("\nBit di esponente:    ");
                              if ( i == 1 && j == 4 )
                                    printf("\nBit di mantissa:     ");
                              break;
                         case sizeof(long double):
                              if ( i == 0 && j == 7 )
                                    printf("\nBit di esponente:    ");
                              if ( i == 1 && j == 0 )
                                    printf("\nBit di mantissa:     ");
                              break;
                    }
            }
        }
    }
}
