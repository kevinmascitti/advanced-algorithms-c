#ifndef PGLIST_H
#define PGLIST_H

#include "personaggi.h"

typedef struct nodo{
    Pg_t val;
    struct nodo *next;
} nodoPg, *linkPg;

typedef struct pgList_s *pgList_t;

/*
typedef struct nodoPg{
    Pg_t val;
    struct nodoPg *next;
} nodoPg, *linkPg;

typedef struct wrapPg{
    linkPg headPg;
    linkPg tailPg;
    int nPg;
} tabPg_t;*/

pgList_t pgList_init();
void scriviPersonaggi(char *nfile, pgList_t pgList);
void stampaTUTTO(pgList_t pgList, vettInv_t vettInv);
linkPg newNode_Pg(Pg_t val, linkPg next);
linkPg SortListIns_Pg(linkPg h, Pg_t val);
void stampa_Pg(linkPg h, vettInv_t vettInv);
void aggiungi(pgList_t pgList, vettInv_t vettInv);
Pg_t elimina(pgList_t pgList);
Pg_t SortListSearch_Pg(pgList_t pgList, char k[]);
Pg_t *PSortListSearch_Pg(linkPg h, char k[]);
Pg_t listExtrKeyP(linkPg *hp, char k[]);
void agg_eq(pgList_t pgList, vettInv_t vettInv);
void rim_eq(pgList_t pgList, vettInv_t vettInv);
void findtail(pgList_t pgList);
void stampaStats(pgList_t pgList, vettInv_t vettInv);

void stampaTesta_Pg(pgList_t pgList, vettInv_t vettInv);
void stampaCoda_Pg(pgList_t pgList, vettInv_t vettInv);
void liberaList(pgList_t pgList);

#endif // PGLIST_H
