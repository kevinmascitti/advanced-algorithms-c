#include "personaggi.h"

void stampaRiga_Pg(Pg_t val, vettInv_t vettInv){  //stampa un elemento della lista (struttura)
    vettEquip_t vuoto = EQUIPsetvoid();
    int i, hp=val.stat_t.hp, mp=val.stat_t.mp, atk=val.stat_t.atk, def=val.stat_t.def, mag=val.stat_t.mag, spr=val.stat_t.spr;
    if( !eqEQUIP (val.equip, vuoto, vettInv) ){
        printf("%s\n%s\n%s\n", val.codice, val.nome, val.classe);
        for(i=0;i<maxeq;i++){
            stampaEquipaggiamento(val.equip, &hp, &mp, &atk, &def, &mag, &spr, i, vettInv);
        }
        if(hp<1) hp=1; if(mp<1) mp=1; if(atk<1) atk=1; if(def<1) def=1; if(mag<1) mag=1; if(spr<1) spr=1;
        printf("%d %d %d %d %d %d\n", hp, mp, atk, def, mag, spr);
    }
    else
        printf("%s\n%s\n%s\n%s\n%d %d %d %d %d %d\n", val.codice, val.nome, val.classe, "Nessun equipaggiamento", hp, mp, atk, def, mag, spr);
    return;
}

Pg_t PGsetvoid(){
    Pg_t a;
    a.codice[0]='\0';
    a.nome[0]='\0';
    a.classe[0]='\0';
    a.equip=EQUIPsetvoid();
    a.stat_t.hp=a.stat_t.mp=a.stat_t.atk=a.stat_t.def=a.stat_t.mag=a.stat_t.spr=0;
    return a;
}

int eqPG(Pg_t a, Pg_t b, vettInv_t vettInv){
    if(strcmp(a.codice,b.codice)==0&&strcmp(a.nome,b.nome)==0&&strcmp(a.classe,b.classe)==0&&eqEQUIP(a.equip,b.equip,vettInv)&&eqSTAT(a.stat_t,b.stat_t))
        return 1; //se sono uguali
    return 0; //se sono diversi
}
