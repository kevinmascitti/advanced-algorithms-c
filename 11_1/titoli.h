#ifndef TITOLI_H_INCLUDED
#define TITOLI_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "quotazioni.h"

typedef struct titolo *Titolo;      //ADT di prima classe
typedef struct node *link;

typedef struct node{
    Titolo val;
    link next;
};

typedef struct titoli *Titoli;




Titoli TitoliInit();
Titolo TitoloInit();
int Titoliisnull(Titoli lista);
int Titoloisnull(Titolo a);

void LeggiFile(Titoli lista);
link newNode(Titolo val, link next);
link SortListIns(link h, Titolo val);
Titolo RicercaTitolo(link h, char *str);
Titolo RicercaT(Titoli lista, char *str);
void displayTitolo(Titolo a);
Quotazione RicercaQuot(Titolo tit);
Quotazione BSTminT(Titolo sel, DataOra data);
Quotazione BSTmaxT(Titolo sel, DataOra data);
int camminoT(Titolo sel);
void balanceT(Titolo sel);

#endif // TITOLI_H_INCLUDED
