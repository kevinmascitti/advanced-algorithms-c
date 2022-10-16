#ifndef PERSONAGGI_H
#define PERSONAGGI_H

#include "vettEquip.h"
#include "vettInv.h"
#include "inventario.h"
/*
typedef struct wrapEquip{
    int inUso;
    vettEquip_t vettEq; //ADT di prima classe in un quasi ADT
} tabEquip_t;
*/
typedef struct pg{
    char codice[MAX];
    char nome[MAX];
    char classe[MAX];
    vettEquip_t equip;
    stat stat_t;
} Pg_t;
/*
typedef struct nodoPg{
    Pg_t val;
    struct nodoPg *next;
} nodoPg, *linkPg;

typedef struct wrapPg{
    linkPg headPg;
    linkPg tailPg;
    int nPg;
} tabPg_t;
*/
/*tabPg_t *scriviPersonaggi(char *nfile, tabPg_t *tabPg);
void stampaTUTTO(tabPg_t *tabPg, tabInv_t *tabInv);
linkPg newNode_Pg(Pg_t val, linkPg next);
linkPg SortListIns_Pg(linkPg h, Pg_t val);
void stampa_Pg(linkPg h);*/
void stampaRiga_Pg(Pg_t val, vettInv_t vettInv);
//tabEquip_t EQUIPsetvoid();
Pg_t PGsetvoid();
//int eqEQUIP(tabEquip_t a, tabEquip_t b);
int eqPG(Pg_t a, Pg_t b, vettInv_t vettInv);
/*linkPg aggiungi(linkPg h);
Pg_t elimina(linkPg h);
Pg_t SortListSearch_Pg(linkPg h, char k[]);
Pg_t *PSortListSearch_Pg(linkPg h, char k[]);
Pg_t listExtrKeyP(linkPg *hp, char k[]);
void agg_eq(linkPg h, Inv_t a[], int tot_ogg);
void rim_eq(linkPg h);
linkPg findtail(linkPg h);
void stampaStats(linkPg h);*/

#endif // PERSONAGGI_H
