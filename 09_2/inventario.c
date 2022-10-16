#include "inventario.h"

void stampaRiga_Inv(Inv_t val){  //stampa un elemento del vettore di strutture che contiene gli oggetti
    printf("%s\n%s\n%d %d %d %d %d %d\n",val.nome,val.tipo,val.stat_inv.hp,
           val.stat_inv.mp,val.stat_inv.atk,val.stat_inv.def,val.stat_inv.mag,val.stat_inv.spr);
    return;
}

Inv_t INVsetvoid(){
    Inv_t a;
    a.nome[0]='\0';
    a.tipo[0]='\0';
    a.stat_inv.hp=a.stat_inv.mp=a.stat_inv.atk=a.stat_inv.def=a.stat_inv.mag=a.stat_inv.spr=0;
    return a;
}

int eqINV(Inv_t a, Inv_t b){
    if(strcmp(a.nome, b.nome)==0 && strcmp(a.tipo, b.tipo)==0 && eqSTAT(a.stat_inv,b.stat_inv))
        return 1;
    return 0;
}

int eqSTAT( stat a, stat b ){
    if(a.hp==b.hp && a.mp==b.mp && a.atk==b.atk &&
       a.def==b.def && a.mag==b.mag && a.spr==b.spr)
        return 1;
    return 0;
}
