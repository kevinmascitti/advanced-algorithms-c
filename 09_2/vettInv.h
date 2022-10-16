#ifndef VETTINV_H
#define VETTINV_H

#include "inventario.h"

//ADT di prima classe
typedef struct vettInv_s *vettInv_t;

vettInv_t vettInv_init();
void scriviInventario(char *nfile, vettInv_t vettInv);
void stampa_Inv(vettInv_t vettInv);
int SortListSearch_Inv(vettInv_t vettInv, char k[]);
int eqEqINV(int a, int b, vettInv_t vettInv);
void stampaEqINV(vettInv_t vettInv, int pos);
void modificaPunti(int equip, int *hp, int *mp, int *atk, int *def, int *mag, int *spr, int i, vettInv_t vettInv);
void prendiNomeDatoIndice(char k[], vettInv_t vettInv, int i);
void liberaInv(vettInv_t vettInv);

#endif // VETTINV_H
