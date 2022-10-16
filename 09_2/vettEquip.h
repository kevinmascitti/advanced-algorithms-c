#ifndef VETTEQUIP_H
#define VETTEQUIP_H

#include "vettInv.h"

//ADT di prima classe
typedef struct vettEquip_s *vettEquip_t;

vettEquip_t vettEquip_init();
vettEquip_t EQUIPsetvoid();
int eqEQUIP( vettEquip_t a, vettEquip_t b, vettInv_t c);
void stampa_Equip(vettEquip_t vettEquip, int pos, vettInv_t vettInv);
void stampaEquipaggiamento(vettEquip_t a, int *hp, int *mp, int *atk, int *def, int *mag, int *spr, int i, vettInv_t vettInv);
void stampaStatsEQ(int val, vettInv_t vettInv);
void modificaPunti(int equip, int *hp, int *mp, int *atk, int *def, int *mag, int *spr, int i, vettInv_t vettInv);
int pieno(vettEquip_t a);
int findempty(vettEquip_t a);
void aggiornaEquip(vettEquip_t vettEquip, int pos, int eqp, int val);
int SortListSearch_Equip(vettEquip_t vettEquip, char k[], vettInv_t vettInv);
void liberaEquip(vettEquip_t vettEquip);

#endif // VETTEQUIP_H
