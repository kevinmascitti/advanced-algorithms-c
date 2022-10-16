#include "vettEquip.h"

struct vettEquip_s{           //ADT di prima classe di tipo vettEquip_s, nel .h ne dichiaro il rispettivo
    int array[maxeq];        //puntatore *vettEquip_t, nuovo tipo allocato dinamicamente
    int inUso;
};

vettEquip_t vettEquip_init(){ //creazione e allocazione dell'ADT di 1 classe
    vettEquip_t a;
    a = malloc(sizeof(*a));
    for(int i=0; i<maxeq; i++)
        a->array[i]=-1;
    a->inUso=0;
    return a;
}

vettEquip_t EQUIPsetvoid(){
    vettEquip_t a;
    a = malloc(sizeof(*a));
    a->inUso=0;
    for(int i=0;i<maxeq;i++)
        a->array[i]=-1;
    return a;
}

int eqEQUIP( vettEquip_t a, vettEquip_t b, vettInv_t vettInv){
    int i;
    if(a->inUso==b->inUso){
        for(i=0;i<maxeq;i++){
            if( eqEqINV(a->array[i], b->array[i], vettInv) != 1 )
                return 0;
        }
        return 1;
    }
    return 0;
}

void stampa_Equip(vettEquip_t vettEquip, int pos, vettInv_t vettInv){
    stampaEqINV(vettInv, vettEquip->array[pos]);
    return;
}

void stampaEquipaggiamento(vettEquip_t equip, int *hp, int *mp, int *atk, int *def, int *mag, int *spr, int i, vettInv_t vettInv){
    if( equip->array[i]!=-1 ){
        stampaEqINV(vettInv, equip->array[i]);
        modificaPunti(equip->array[i], hp, mp, atk, def, mag, spr, i, vettInv);
    }
    return;
}

int pieno(vettEquip_t a){
    if(a->inUso>=maxeq)
        return 1;   //se pieno
    return 0;       //se vuoto
}

int findempty(vettEquip_t a){ //trova la prima posizione libera del vettore equip di un personaggio, in cui posso inserire equip nuovo
    int pos;
    for(pos=0; pos<maxeq; pos++)
        if( a->array[pos]==-1 )
            return pos;
    return -1;
}

void aggiornaEquip(vettEquip_t vettEquip, int pos, int eqp, int val){ //val indica se voglio aggiungere o rimuovere equip
    if (val==1){                    //aggiungo equip a pg in posizione pos
        vettEquip->inUso++;
        vettEquip->array[pos]=eqp;
    }
    else if (val==-1){              //elimino equip da pg
        vettEquip->inUso--;
        vettEquip->array[eqp]=-1;
    }
    return;
}

int SortListSearch_Equip(vettEquip_t vettEquip, char k[], vettInv_t vettInv){
    int i=0;
    char copia[MAX];
    for(i=0; i<maxeq; i++){
        prendiNomeDatoIndice(copia, vettInv, vettEquip->array[i]); //dato l'indice, trovo il nome dell'oggetto
        strlwr(copia);                                             //nell'invetario a cui si fa riferimento
        if(strcmp(copia, k)==0)
            return i;
    }
    return -1;
}

void liberaEquip(vettEquip_t vettEquip){ //libera la memoria prima allocata dinamicamente
    free(vettEquip);
    return;
}
