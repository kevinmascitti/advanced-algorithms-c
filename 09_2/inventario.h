#ifndef INVENTARIO_H
#define INVENTARIO_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define MAXSTR 500
#define MAX 51
#define maxeq 8

typedef struct stats{
    int hp;
    int mp;
    int atk;
    int def;
    int mag;
    int spr;
} stat;

typedef struct ogg{
    char nome[MAX];
    char tipo[MAX];
    stat stat_inv;
} Inv_t;
/*
typedef struct tabInv{
    vettInv_t vettInv;
    int nInv;
    int maxInv;
} tabInv_t;
*/

//tabInv_t *scriviInventario(char *nfile, tabInv_t *tabInv);
void stampaRiga_Inv(Inv_t val);
Inv_t INVsetvoid();
int eqINV(Inv_t a, Inv_t b);
int eqSTAT(stat a, stat b);
/*
Inv_t SortListSearch_Inv(Inv_t a[], char k[], int tot_ogg);
Inv_t *PSortListSearch_Inv(Inv_t *a, char k[], int tot_ogg);
int findempty(Inv_t **a);
*/

#endif // INVENTARIO_H
