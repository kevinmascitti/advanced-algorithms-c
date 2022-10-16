#include "vettInv.h"
#include <stdio.h>
#include <stdlib.h>

struct vettInv_s{       //ADT di prima classe di tipo vettInv_s, nel .h ne dichiaro il rispettivo
    Inv_t* array;       //puntatore *vettInv_t, nuovo tipo allocato dinamicamente
    int nInv;
    int maxInv;
};

vettInv_t vettInv_init(){ //creazione e allocazione dell'ADT di 1 classe
    vettInv_t a;
    a = malloc(sizeof(*a));
    a->array=NULL;
    a->nInv=0;
    a->maxInv=maxeq;
    return a;
}

//inserimento dell'inventario completo in una variabile di tipo vettInv_t, il tipo ADT prima definito
void scriviInventario(char *nfile, vettInv_t vettInv){
    int i=0, j;
    char tmp[MAXSTR];
    FILE *fp=fopen(nfile, "r");
    if (fp==NULL){
            printf("File %s vuoto.\n", nfile);
        return;
    }
    fgets(tmp, "%s", fp);
    sscanf(tmp, "%d", &vettInv->nInv);
    vettInv->array = malloc ((vettInv->nInv)*sizeof(Inv_t));
    while(fgets(tmp,"%s",fp)!=NULL){
        sscanf(tmp,"%s %s %d %d %d %d %d %d",vettInv->array[i].nome,vettInv->array[i].tipo,
            &vettInv->array[i].stat_inv.hp,&vettInv->array[i].stat_inv.mp,&vettInv->array[i].stat_inv.atk,
            &vettInv->array[i].stat_inv.def,&vettInv->array[i].stat_inv.mag,&vettInv->array[i].stat_inv.spr);
        i++;
    }
    if(i!=vettInv->nInv){
        printf("Errore file inventario.txt\n");
        return;
    }
    fclose(fp);
    return;
}

void stampa_Inv(vettInv_t vettInv){ //stampa tutte le righe dell'inventario
    int i, tot_ogg=vettInv->nInv;
    if(tot_ogg==0){
        printf("Inventario vuoto.\n\n");
        return;
    }
    printf("%d oggetti nell'inventario:\n\n", vettInv->nInv);
    for(i=0;i<tot_ogg;i++){
        stampaRiga_Inv(vettInv->array[i]);
        printf("\n");
    }
    return;
}

int SortListSearch_Inv(vettInv_t vettInv, char k[]){
    int i=0;
    char copia[MAX];
    for(i=0; i<vettInv->nInv; i++){
        strcpy(copia, vettInv->array[i].nome);
        strlwr(copia);
        if(strcmp(copia, k)==0)
            return i;
    }
    return -1;
}

int eqEqINV(int a, int b, vettInv_t vettInv){ //verifica che due equipaggiamenti siano uguali e lo fa guardando
    if(eqINV(vettInv->array[a], vettInv->array[b])) //l'indice di riferimento all'interno dell'inventario. Se sono uguali ok.
        return 1;
    return 0;
}

void stampaEqINV(vettInv_t vettInv, int pos){ //stampa un equipaggiamento, dato l'indice di riferimento nell'inventario
    stampaRiga_Inv(vettInv->array[pos]);
    return;
}

void modificaPunti(int equip, int *hp, int *mp, int *atk, int *def, int *mag, int *spr, int i, vettInv_t vettInv){
    *hp+=vettInv->array[equip].stat_inv.hp; //modifica i valori del personaggio per la fase di stampa delle statistiche di un pg
    *mp+=vettInv->array[equip].stat_inv.mp;
    *atk+=vettInv->array[equip].stat_inv.atk;
    *def+=vettInv->array[equip].stat_inv.def;
    *mag+=vettInv->array[equip].stat_inv.mag;
    *spr+=vettInv->array[equip].stat_inv.spr;
    return;
}

void prendiNomeDatoIndice(char k[], vettInv_t vettInv, int i){ //ritorna il nome di un oggetto in inventario, dato l'indice
    strcpy(k, vettInv->array[i].nome);                         //che ne indica la posizione nell'elenco di tutti gli oggetti
    return;
}

void liberaInv(vettInv_t vettInv){
    free(vettInv->array); //perche' ho allocato dinamicamente array precedentemente
    free(vettInv);
    return;
}
