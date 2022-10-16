#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "graph.h"
#include "ST.h"

#define MAXC 31
#define maxWT 0

typedef struct node *link;

struct graph {
    int V;
    int E;
    int **madj;
    link* ladj;
    link z;
    ST tab;
};

struct node {
    int v;
    link next;
};

static Edge  EDGEcreate(int v, int w, int wt);
static int **MATRIXint(int r, int c, int val);
static link NEWnode(int v, link next);
static void  insertE(Graph G, Edge e);

static Edge EDGEcreate(int v, int w, int wt) {
  Edge e;
  e.v = v;
  e.w = w;
  e.wt = wt;
  return e;
}

int **MATRIXint(int r, int c, int val) {
  int i, j;
  int **t = malloc(r * sizeof(int *));
  if (t==NULL)
    return NULL;

  for (i=0; i < r; i++) {
    t[i] = calloc(c, sizeof(int));
    if (t[i]==NULL)
      return NULL;
  }
  for (i=0; i < r; i++)
    for (j=0; j < c; j++)
      t[i][j] = val;
  return t;
}

static link NEWnode(int v, link next){
    link x = malloc(sizeof(*x));
    x->v = v;
    x->next = next;
    return x;
}

Graph GRAPHinit(int V) {
  Graph G = malloc(sizeof *G);
  if (G == NULL) return NULL;
  G->V = V;
  G->E = 0;
  G->madj = MATRIXint(V, V, maxWT);
  if (G->madj == NULL) return NULL;
    G->ladj = malloc(sizeof(*G->ladj)*V);
    G->z = NEWnode(-1, NULL);
    for(int i = 0; i < G->V; i++)
        G->ladj[i] = G->z;
  G->tab = STinit(V);
  if (G->tab == NULL) return NULL;
  return G;
}

void GRAPHfree(Graph G) {
  int i;

  for (i=0; i<G->V; i++)
    free(G->madj[i]);
  free(G->madj);
  free(G->ladj);
  STfree(G->tab);
  free(G);
}

int vert(Graph G){
    return G->V;
}

Graph GRAPHload(FILE *fin) {
    int i=0, id1, id2, wt, edges=0;
    char label1[MAXC], label2[MAXC], tmp[150];
    Graph G;
    while(fgets(tmp, "%s", fin)!=NULL)
        edges++;
    G=GRAPHinit(edges*2);
    rewind(fin);
    while(fgets(tmp, "%s", fin)!=NULL){
        sscanf(tmp, "%s %*s %s %*s %d", label1, label2, &wt);
        id1 = STsearch(G->tab, label1);
        id2 = STsearch(G->tab, label2);
        if (id1 < 0){
            STinsert(G->tab, label1, i);
            id1 = i;
            i++;
        }
        if (id2 < 0){
            STinsert(G->tab, label2, i);
            id2 = i;
            i++;
        }
        GRAPHinsertE(G, id1, id2, wt);
    }
    G->V=STsize(G->tab);
    return G;
}

void GRAPHinsertE(Graph G, int id1, int id2, int wt) {
    insertE(G, EDGEcreate(id1, id2, wt));
}

static void  insertE(Graph G, Edge e) {
    int v = e.v, w = e.w, wt = e.wt;
    if (G->madj[v][w] == maxWT)
        G->E++;
    G->madj[v][w] = wt;
    G->madj[w][v] = wt;
}

void  GRAPHedges(Graph G, Edge *a) {
  int v, w, E = 0;
  for (v=0; v < G->V; v++)
    for (w=v+1; w < G->V; w++)
      if (G->madj[v][w] != maxWT)
        a[E++] = EDGEcreate(v, w, G->madj[v][w]);
}

void GRAPHstore(Graph G, FILE *fout) {
  int i;
  Edge *a;

  a = malloc(G->E * sizeof(Edge));
  if (a == NULL)
    return;

  GRAPHedges(G, a);

  fprintf(fout, "%d\n", G->V);
  for (i = 0; i < G->V; i++)
    fprintf(fout, "%s\n", STsearchByIndex(G->tab, i));
    printf("\n");
  for (i = 0; i < G->E; i++)
    fprintf(fout, "%s  %s %d\n", STsearchByIndex(G->tab, a[i].v), STsearchByIndex(G->tab, a[i].w), a[i].wt);
  free(a);
}

int GRAPHgetIndex(Graph G, char *label, char *label2) {
  int id;
  id = STsearch(G->tab, label);
  if (id == -1) {
    id = STsize(G->tab);
    STinsert(G->tab, label, id);
  }
  return id;
}

void GRAPHStampaOrdinato(Graph G){
    int n = G->V, m = (G->V)-1, t, i, k, indice;
    char **vertici = malloc(n*sizeof(char *));
    char **archiIncidenti = malloc(m*sizeof(char *));
    for(i = 0; i < n; i++)              //copia della tabella di simboli in un vettore di stringhe
        vertici[i] = strdup(STsearchByIndex(G->tab, i));
    MergeSort(vertici, n);              //ordinamento alfabetico
    for(i = 0; i < n; i++){
        t = 0;
        printf("Vertice:\t%s\n", vertici[i]);
        indice = STsearch(G->tab, vertici[i]);
        for(k = 0; k < G->V; k++){
            if(G->madj[indice][k] != 0){
                archiIncidenti[t] = strdup(STsearchByIndex(G->tab, k));
                t++;
            }
        }
        MergeSort(archiIncidenti, t);   //ordinamento degli archi trovati per ogni vertice
        printf("Archi adiacenti:\n");
        for(k = 0; k < t; k++){
            printf("%s\n", archiIncidenti[k]);
        }
        printf("\n");
    }
    printf("\n");
    return;
}

void Merge(char **A, char **B, int l, int q, int r) {
  int i, j, k;
  i = l;
  j = q+1;
  for(k = l; k <= r; k++)
    if (i > q)
      strcpy(B[k], A[j++]);
    else if (j > r)
      strcpy(B[k], A[i++]);
    else if (ITEMleq(A[i], A[j]))
      strcpy(B[k], A[i++]);
    else
      strcpy(B[k], A[j++]);
  for ( k = l; k <= r; k++ )
    strcpy(A[k], B[k]);
  return;
}

void MergeSortR(char **A, char **B, int l, int r) {
  int q;
  if (r <= l)
    return;
  q = (l + r)/2;
  MergeSortR(A, B, l, q);
  MergeSortR(A, B, q+1, r);
  Merge(A, B, l, q, r);
}

void MergeSort(char **A, int N) {
  int l=0, r=N-1;
  char **B;
  B=malloc(N*sizeof(char*));
  for(int i=0; i<N; i++){
    B[i]=malloc(31*sizeof(char));
  }
  MergeSortR(A, B, l, r);
  return;
}

void GRAPHgenerateLadj(Graph G){
    int V = G->V;
    int i, j;
    for(i = 0; i < V; i++){
        for(j = i+1; j < V; j++){
            if(G->madj[i][j] != 0){
                G->ladj[i] = NEWnode(j, G->ladj[i]);
                G->ladj[j] = NEWnode(i, G->ladj[j]);
            }
        }
    }
}

void GRAPHprintLadj(Graph G){
    int i;
    link x;
    for(i = 0; i < G->V; i++){
        printf("%s ", STsearchByIndex(G->tab, i));
        for(x = G->ladj[i]; x != G->z; x = x->next){
            printf("-> %s", STsearchByIndex(G->tab, x->v));
        }
        printf("\n");
    }
}

void GRAPHverifyM(Graph G, char words[][30]){
    int i, j;
    int n = 3;
    int flag = 1;
    int v[3];
    for(i = 0; i < n; i++)
        v[i] = STsearch(G->tab, words[i]);
    for(i = 0, j = 1; i < n; i++){
        if(i==n-1){
            if(G->madj[v[i]][v[0]] == 0){
                flag = 0;
                break;
            }
        }
        else{
            if(G->madj[v[i]][v[i+j]] == 0){
                flag=0;
                j++;
                break;
            }
        }
    }
    if(flag)
        printf("I tre vertici formano un sottografo completo.\n");
    else
        printf("I tre vertici non formano un sottografo completo.\n");
}

void GRAPHverifyL(Graph G, char words[][30]){
    int i, corretto;
    int n = 3;
    int flag = 1;
    int v[3];
    link x;
    for(i = 0; i < n; i++)
        v[i] = STsearch(G->tab, words[i]);
    for(i = 0; i < n; i++){
        corretto=0;
        if(i==n-1){
            for(x=G->ladj[v[i]]->next; x!=NULL; x=x->next)
                if(x->v == v[0]){
                    corretto=1;
                    break;
                }
            if(corretto==0){
                flag=0;
                break;
            }
        }
        else{
            for(x=G->ladj[v[i]]->next; x!=NULL; x=x->next)
                if(x->v == v[i+1]){
                    corretto=1;
                    break;
                }
            if(corretto==0){
                flag=0;
                break;
            }
        }
    }
    if(flag)
        printf("Anche attraverso la lista di adiacenze si dimostra che i tre vertici formano un sottografo completo.\n");
    else
        printf("Anche attraverso la lista di adiacenze si dimostra che i tre vertici non formano un sottografo completo.\n");
}
