#include "inventario.h"

tabInv_t *scriviInventario(char *nfile, tabInv_t *tabInv){
    int i=0;
    char tmp[MAXSTR];
    FILE *fp=fopen(nfile, "r");
    if (fp==NULL){
            printf("File %s vuoto.\n", nfile);
        return;
    }
    //inserimento dell'inventario completo in un vettore di oggetti detti Inv_t
    fgets(tmp, "%s", fp);
    sscanf(tmp,"%d",&tabInv->nInv);
    tabInv->maxInv=maxeq;
    tabInv->vettInv = (Inv_t*) malloc ( tabInv->nInv * sizeof(Inv_t) );
    while(fgets(tmp,"%s",fp)!=NULL){
        sscanf(tmp,"%s %s %d %d %d %d %d %d",tabInv->vettInv[i].nome,tabInv->vettInv[i].tipo,
            &tabInv->vettInv[i].stat_inv.hp,&tabInv->vettInv[i].stat_inv.mp,&tabInv->vettInv[i].stat_inv.atk,
            &tabInv->vettInv[i].stat_inv.def,&tabInv->vettInv[i].stat_inv.mag,&tabInv->vettInv[i].stat_inv.spr);
        i++;
    }
    if(i!=tabInv->nInv){
        printf("Errore file inventario.txt\n");
        return;
    }
    fclose(fp);
    return tabInv;
}

void stampa_Inv(Inv_t *h, int tot_ogg){
    int i;
    if(h==NULL){
        printf("Inventario vuoto.\n\n");
        return;
    }
    for(i=0;i<tot_ogg;i++){
        stampaRiga_Inv(h[i]);
        printf("\n");
    }
    return;
}

void stampaRiga_Inv(Inv_t val){  //stampa un elemento del vettore di strutture che contengono gli oggetti
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

Inv_t SortListSearch_Inv(Inv_t a[], char k[], int tot_ogg){
    int i=0;
    char copia[MAX];
    for(i=0; i<tot_ogg; i++){
        strcpy(copia, a[i].nome);
        strlwr(copia);
        if(strcmp(copia, k)==0)
            return a[i];
    }
    return INVsetvoid();
}

Inv_t *PSortListSearch_Inv(Inv_t *a, char k[], int tot_ogg){
    int i=0;
    char copia[MAX];
    for(i=0; i<tot_ogg; i++){
        strcpy(copia, a[i].nome);
        strlwr(copia);
        if(strcmp(copia, k)==0)
            return &(a[i]);
    }
    return NULL;
}

int findempty(Inv_t **a){
    int pos;
    for(pos=0; pos<maxeq; pos++)
        if(a[pos]==NULL)
            return pos;
    return -1;
}
