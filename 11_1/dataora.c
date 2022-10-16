#include <stdio.h>
#include <stdlib.h>
#include "dataora.h"

DataOra DATAORAInit(){
    DataOra a;
    a.aa=a.mm=a.gg=a.o=a.m=0;
    return a;
}

DataOra NEWdataora(int aa, int mm, int gg, int o, int m){
    DataOra a;
    a.aa=aa; a.mm=mm; a.gg=gg; a.o=o; a.m=m;
    return a;
}

int DATAisnull(DataOra a){
    if(a.aa==0 && a.mm==0 && a.gg==0)
        return 1;
    return 0;
}

int AgtB(DataOra a, DataOra b){         //esegue il confronto considerando DATA E ORA!
    if(a.aa>b.aa) return 1;
    if(a.aa<b.aa) return 0;
    if(a.mm>b.mm) return 1;
    if(a.mm<b.mm) return 0;
    if(a.gg>b.gg) return 1;
    if(a.gg<b.gg) return 0;
    if(a.o>b.o) return 1;
    if(a.o<b.o) return 0;
    if(a.m>b.m) return 1;
    if(a.m<b.m) return 0;
    return -1; //ritorna 1 se a>b, 0 se a<b, -1 se a=b
}

int AgtBDATA(DataOra a, DataOra b){     //esegue il confronto considerando SOLO la data e non l'orario!
    if(a.aa>b.aa) return 1;
    if(a.aa<b.aa) return 0;
    if(a.mm>b.mm) return 1;
    if(a.mm<b.mm) return 0;
    if(a.gg>b.gg) return 1;
    if(a.gg<b.gg) return 0;
    return -1; //ritorna 1 se a>b, 0 se a<b, -1 se a=b
}

int AMGgt(int aa, int mm, int gg, DataOra a){         //esegue il confronto tra una data i cui parametri sono passati sottoforma di interi e una data sottoforma di DATAORA
    if ( aa>a.aa || (aa==a.aa&&mm>a.mm) || (aa==a.aa&&mm==a.mm&&gg>a.gg) )
        return 1;
    else if(aa<a.aa || (aa==a.aa&&mm<a.mm) || (aa==a.aa&&mm==a.mm&&gg<a.gg))
        return 0;
    else if(aa==a.aa && mm==a.mm && gg==a.gg)
        return -1;
}

void inserisciDate (DataOra *mi, DataOra *ma){
    char tmp[20];
    int aa=0, mm=0, gg=0;
    while(aa<0 || mm<1 || mm>12 || gg<1 || gg>31){
        printf("Inserisci data minima nel formato aaaa/mm/gg.\n");
        scanf("%s", tmp);
        sscanf(tmp, "%04d/%02d/%02d", &aa, &mm, &gg);
        mi->aa=aa; mi->mm=mm; mi->gg=gg; mi->o=0; mi->m=0;
    }
    aa=0; mm=0; gg=0;
    while(aa<0 || mm<1 || mm>12 || gg<1 || gg>31){
        printf("Inserisci data massima nel formato aaaa/mm/gg.\n");
        scanf("%s", tmp);
        sscanf(tmp, "%04d/%02d/%02d", &aa, &mm, &gg);
        ma->aa=aa; ma->mm=mm; ma->gg=gg; ma->o=23; ma->m=59;
    }
}
