#ifndef QUOTAZIONI_H_INCLUDED
#define QUOTAZIONI_H_INCLUDED

#include <stdio.h>
#include <stdlib.h>
#include "dataora.h"

typedef struct quotazione *Quotazione;          //ADT di prima classe
typedef struct BSTnode *linkBST;                //ADT di prima classe
typedef struct quotazioni *BST;                 //ADT di prima classe





BST BSTInit();
Quotazione QUOTInit();
BST NEWlinkbst(Quotazione quot, linkBST l, linkBST r, int N);
Quotazione NEWquot(DataOra dataora, int val, int num);
void BSTfree(BST bst);
void treeFree(linkBST h, linkBST z);
linkBST insertR(linkBST h, Quotazione x, linkBST z);
void BSTinsert_leafR(BST bst, Quotazione x);
DataOra KEYget(Quotazione x);
int BSTisnull(BST a);
void BSTvisit(BST a);
void treePrintR(linkBST h, linkBST z, int strategy);
Quotazione searchR(linkBST h, linkBST z, DataOra data);
Quotazione searchRWrap(Quotazione quot, BST bst);
Quotazione minR(linkBST h, linkBST z, DataOra data);
Quotazione BSTmin(BST bst, DataOra data);
Quotazione maxR(linkBST h, linkBST z, DataOra data);
Quotazione BSTmax(BST bst, DataOra data);
void camminoR(linkBST h, linkBST z, int pos, int *minimo, int *massimo);
int cammino(BST bst, int camm, int *minimo, int *massimo);
linkBST balanceR(linkBST h, linkBST z);
void BSTbalance(BST bst);
void inserisciQUOT(Quotazione a, Quotazione b);
int QUOTisnull(Quotazione a);
linkBST partR(linkBST h, int r);
linkBST rotR(linkBST h);
linkBST rotL(linkBST h);
void QUOTstamp(Quotazione a);

#endif // QUOTAZIONI_H_INCLUDED
