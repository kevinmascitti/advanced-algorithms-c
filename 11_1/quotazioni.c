#include "quotazioni.h"

typedef struct quotazione{
    DataOra i;
    int N;
    int D;
};

typedef struct BSTnode {
    Quotazione item;
    linkBST l;
    linkBST r;
    int N;
};

typedef struct quotazioni{
    linkBST root;
    linkBST z;
    int tot;
};





BST BSTInit(){
    BST bst = malloc(sizeof *bst);
    bst->root = bst->z = NEWlinkbst(QUOTInit(), NULL, NULL, 0);
    bst->tot=0;
    return bst;
}

BST NEWlinkbst(Quotazione quot, linkBST l, linkBST r, int N){
    linkBST x = malloc(sizeof *x);
    x->item=quot;
    x->l=l;
    x->r=r;
    x->N=N;
    return x;
}

Quotazione QUOTInit(){
    Quotazione a = malloc(sizeof *a);
    a->i=DATAORAInit();
    a->N = 0;
    a->D = 0;
    return a;
}

Quotazione NEWquot(DataOra dataora, int val, int num){
    Quotazione a = malloc(sizeof *a);
    a->i=dataora;
    a->N=val*num;
    a->D=num;
    return a;
}

void BSTfree(BST bst) {
  if (bst == NULL)
    return;
  treeFree(bst->root, bst->z);
  free(bst->z);
  free(bst);
}

void treeFree(linkBST h, linkBST z) {
  if (h == z)
    return;
  treeFree(h->l, z);
  treeFree(h->r, z);
  free(h);
}

linkBST insertR(linkBST h, Quotazione x, linkBST z) {
  if (h == z)
    return NEWlinkbst(x, z, z, 1);
  if (AgtB(KEYget(x), KEYget(h->item))==0)       //A<B
    h->l = insertR(h->l, x, z);
  else                                           //A>=B
    h->r = insertR(h->r, x, z);
  (h->N)++;
  return h;
}

void BSTinsert_leafR(BST bst, Quotazione x) {
  bst->root = insertR(bst->root, x, bst->z);
}

DataOra KEYget(Quotazione x){           //estrae il campo DATAORA da una quotazione
    return x->i;
}

int BSTisnull(BST a){
    if(a->tot==0 && QUOTisnull(a->root->item)==1 && a->root->l==NULL && a->root->r==NULL && a->root->N==0 && QUOTisnull(a->z->item)==1 && a->z->l==NULL && a->z->r==NULL && a->z->N==0)
        return 1;
    return 0;
}

void BSTvisit(BST a){                       //Stampa l'intero BST passato alla funzione
    if(BSTisnull(a))
        return;
    treePrintR(a->root, a->z, 0);
}

void treePrintR(linkBST h, linkBST z, int strategy) {
  if (h == z)
    return;
  if (strategy == -1)
    QUOTstamp(h->item);
  treePrintR(h->l, z, strategy);
  if (strategy == 0)
    QUOTstamp(h->item);
  treePrintR(h->r, z, strategy);
  if (strategy == 1)
    QUOTstamp(h->item);
}

Quotazione searchR(linkBST h, linkBST z, DataOra data) {
  if (h == z)
    return QUOTInit();

  if(AgtBDATA(data, h->item->i)==-1)                //data == h->item->i
    return h->item;

  else if (AgtBDATA(data, h->item->i)==0)           //data < h->item->i
    return searchR(h->l, z, data);
  else if (AgtBDATA(data, h->item->i)==1)           //data > h->item->i
    return searchR(h->r, z, data);
}

Quotazione searchRWrap(Quotazione quot, BST bst){
    return searchR(bst->root, bst->z, quot->i);
}

Quotazione minR(linkBST h, linkBST z, DataOra data) {
    if (h == z)
        return QUOTInit();
    if (AgtB(data, DATAORAInit())==0 || AgtB(data, DATAORAInit())==1) //se la data non e' nulla uso un metodo che eventualmente si ferma prima di arrivare alla foglia finale
        if (h->l == z || AgtB(data, h->l->item->i)==1)
            return (h->item);
    if (AgtB(data, DATAORAInit())==-1)      //se la data e' nulla uso un altro metodo e cerco il minimo assoluto dell'albero
        if (h->l == z)
            return (h->item);
    return minR(h->l, z, data);
}

Quotazione BSTmin(BST bst, DataOra data) {
  return minR(bst->root, bst->z, data);
}

Quotazione maxR(linkBST h, linkBST z, DataOra data) {
    if (h == z)
        return QUOTInit();
    if (AgtB(data, DATAORAInit())==0 || AgtB(data, DATAORAInit())==1) //se la data non e' nulla uso un metodo che, eventualmente si ferma prima di arrivare alla foglia finale
        if (h->r == z || AgtB(h->r->item->i, data)==1)
            return (h->item);
    if (AgtB(data, DATAORAInit())==-1)      //se la data e' nulla uso un altro metodo e cerco il massimo assoluto dell'albero
        if (h->r == z)
            return (h->item);
    return maxR(h->r, z, data);
}

Quotazione BSTmax(BST bst, DataOra data) {
  return maxR(bst->root, bst->z, data);
}

void camminoR(linkBST h, linkBST z, int pos, int *minimo, int *massimo){
    if(h == z){                     //terminazione ricorsione
        if (pos<*minimo)
            *minimo=pos;
        if (pos>*massimo)
            *massimo=pos;
        return;
    }
    camminoR(h->l, z, pos+1, minimo, massimo);
    camminoR(h->r, z, pos+1, minimo, massimo);
    return;
}

int cammino(BST bst, int camm, int *minimo, int *massimo){
    camminoR(bst->root, bst->z, camm, minimo, massimo);
    return *massimo-*minimo;
}

linkBST balanceR(linkBST h, linkBST z) {
  int r;
  if (h == z)
    return z;
  r = (h->N+1)/2-1;
  h = partR(h, r);
  h->l = balanceR(h->l, z);
  h->r = balanceR(h->r, z);
  return h;
}

void BSTbalance(BST bst) {
  bst->root = balanceR(bst->root, bst->z);
}

void inserisciQUOT(Quotazione a, Quotazione b){
    b->i=a->i;
    (b->N)+=a->N;
    (b->D)+=a->D;
}

int QUOTisnull(Quotazione a){
    if(a->N==0 && a->D==0 && DATAisnull(a->i))
        return 1;
    return 0;
}

linkBST partR(linkBST h, int r) {
  int t  = h->l->N;
  if ( t > r) {
    h->l = partR(h->l, r);
    h = rotR(h);
  }
  if ( t < r) {
    h->r = partR(h->r, r-t-1);
    h = rotL(h);
  }
  return h;
}

linkBST rotR(linkBST h) {
  linkBST x = h->l;
  h->l = x->r;
  x->r = h;
  x->N = h->N;
  h->N = 1;
  h->N += (h->l) ? h->l->N : 0;
  h->N += (h->r) ? h->r->N : 0;
  return x;
}

linkBST rotL(linkBST h) {
  linkBST x = h->r;
  h->r = x->l;
  x->l = h;
  x->N = h->N;
  h->N = 1;
  h->N += (h->l) ? h->l->N : 0;
  h->N += (h->r) ? h->r->N : 0;
  return x;
}

void QUOTstamp(Quotazione a){
    printf("Quotazione giornaliera: %.03f.     Data: %04d/%02d/%02d.\n", ((float)a->N/(float)a->D), a->i.aa, a->i.mm, a->i.gg);
}

