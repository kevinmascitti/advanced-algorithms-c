#include <stdlib.h>
#include <stdio.h>
#include "ST.h"
#include "graph.h"

#define MAXC 11

struct graph {
    int V;
    int E;
    int **madj;
    int *vertici;
    ST tab;
};

static Edge  EDGEcreate(int v, int w);
static int **MATRIXint(int r, int c, int val);
static void  insertE(Graph G, Edge e);
static void  removeE(Graph G, Edge e);

static Edge EDGEcreate(int v, int w) {
  Edge e;
  e.v = v;
  e.w = w;
  return e;
}

static int **MATRIXint(int r, int c, int val) {
  int i, j;
  int **t = malloc(r * sizeof(int *));
  if (t==NULL)
    return NULL;

  for (i=0; i < r; i++) {
    t[i] = malloc(c * sizeof(int));
    if (t[i]==NULL)
      return NULL;
  }
  for (i=0; i < r; i++)
    for (j=0; j < c; j++)
      t[i][j] = val;
  return t;
}

Graph GRAPHinit(int V) {
  int i;
  Graph G = malloc(sizeof *G);
  if (G == NULL)
    return NULL;
  G->V = V;
  G->E = 0;
  G->madj = MATRIXint(V, V, 0);
  if (G->madj == NULL)
    return NULL;
  G->vertici = malloc(V*sizeof(int));
  for(i=0; i<V; i++)
    G->vertici[i]=1;
  G->tab = STinit(V);
  if (G->tab == NULL)
    return NULL;
  return G;
}

void GRAPHfree(Graph G) {
  int i;
  for (i=0; i<G->V; i++)
    free(G->madj[i]);
  free(G->madj);
  free(G->vertici);
  STfree(G->tab);
  free(G);
}

Graph GRAPHload(FILE *fin) {
  int V, i, id1, id2;
  char label1[MAXC], label2[MAXC];
  Graph G;

  fscanf(fin, "%d", &V);
  G = GRAPHinit(V);

  for (i=0; i<V; i++) {
    fscanf(fin, "%s", label1);
    STinsert(G->tab, label1, i);
  }

  while(fscanf(fin, "%s %s", label1, label2) == 2) {
    id1 = STsearch(G->tab, label1);
    id2 = STsearch(G->tab, label2);
    if (id1 >= 0 && id2 >=0)
      GRAPHinsertE(G, id1, id2);
  }
  return G;
}

static void  insertE(Graph G, Edge e) {
  int v = e.v, w = e.w;

  if (G->madj[v][w] == 0)
    G->E++;
  G->madj[v][w] = 1;
  G->madj[w][v] = 1;
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

  for (i = 0; i < G->E; i++)
    fprintf(fout, "%s  %s\n", STsearchByIndex(G->tab, a[i].v), STsearchByIndex(G->tab, a[i].w));

  free(a);
}

void GRAPHinsertE(Graph G, int id1, int id2) {
  insertE(G, EDGEcreate(id1, id2));
}

void GRAPHremoveE(Graph G, int id1, int id2) {
  removeE(G, EDGEcreate(id1, id2));
}

static void  removeE(Graph G, Edge e) {
  int v = e.v, w = e.w;
  if (G->madj[v][w] == 1)
    G->E--;
  G->madj[v][w] = 0;
  G->madj[w][v] = 0;
}

void  GRAPHedges(Graph G, Edge *a) {
  int v, w, E = 0;
  for (v=0; v < G->V; v++)
    for (w=v+1; w < G->V; w++)
      if (G->madj[v][w] == 1)
        a[E++] = EDGEcreate(v, w);
}

int GRAPHcc(Graph G){
    int v, id=0, *cc;
    cc=malloc(G->V*sizeof(int));
    for(v=0; v<G->V; v++)
        cc[v]=-1;
    for(v=0; v<G->V; v++)
        if(cc[v]==-1)
            dfsRcc(G, v, id++, cc);
    free(cc);
    return id;
}

void dfsRcc(Graph G, int v, int id, int *cc){
    int j;
    cc[v]=id;
    for(j=0; j<G->V; j++)
        if(G->madj[v][j]!=0 && cc[j]==-1)
            dfsRcc(G, j, id, cc);
}


//FUNZIONI SVILUPPATE DA ME NON STANDARD

void Kcore(Graph G, int k){
    int i;
    int *gradi=calloc(G->V, sizeof(int));
    Edge *removedEdges=malloc(G->E * sizeof(Edge));
    for(i=0; i<G->E; i++){
        removedEdges[i].v=-1;
        removedEdges[i].w=-1;
    }
    calcolaGradi(G, gradi);
    while(min(gradi, G)<k && emptyV(G)==0){
        removeV(G, k, removedEdges, gradi);
        calcolaGradi(G, gradi);
    }
    if(emptyV(G))
        printf("Non esiste il %d-core.\n", k);
    else{
        printf("Esiste il %d-core.\n", k);
        for(i=0; i<G->V; i++)
            if(G->vertici[i]==1)
                printf("%s\n", STsearchByIndex(G->tab, i));
    }
    ripristina(G, removedEdges);
    free(gradi);
    free(removedEdges);
}

int min(int *a, Graph G){
    int i, min;
    int DIM = G->V;
    for(i=0; i<DIM; i++)
        if(a[i]<min)
            if(G->vertici[i]==1)
                min=a[i];
    return min;
}

int emptyV(Graph G){
    int i;
    for(i=0; i<G->V; i++){
        if(G->vertici[i]==1)
            return 0;
    }
    return 1;
}

void ripristina(Graph G, Edge *removedEdges){
    int i, DIM;
    DIM=G->E;
    for(i=0; i<G->V; i++)
        G->vertici[i]=1;
    for(i=0; i<DIM; i++)
        if(!EDGEisnull(removedEdges[i])){
            G->madj[removedEdges[i].v][removedEdges[i].w]=1;
            G->madj[removedEdges[i].w][removedEdges[i].v]=1;
        }
}

int EDGEisnull(Edge e){
    if(e.v == -1 && e.w == -1)
        return 1;
    return 0;
}

void calcolaGradi(Graph G, int *gradi){
    int i, j;
    for(i=0; i<G->V; i++){
        gradi[i]=0;
        if(G->vertici[i]==1){
            for(j=0; j<G->V; j++){
                if(G->vertici[j]==1 && G->madj[i][j]!=0)
                    gradi[i]++;
            }
        }
    }
    return;
}

void removeV(Graph G, int k, Edge *removedEdges, int *gradi){
    int i;
    for(i=0; i<G->V; i++){
        if(G->vertici[i]==1 && gradi[i]<k){
            G->vertici[i]=0;
            rimuoviArchi(G, i, removedEdges);
        }
    }
    return;
}

void rimuoviArchi(Graph G, int id, Edge *removedEdges){
    int j, k;
    for(j=0; j<G->V; j++){
        if(G->madj[id][j]!=0){
            k=findempty(removedEdges, G->E);
            removedEdges[k]=EDGEcreate(id, j);
            G->madj[id][j]=0;
            G->madj[j][id]=0;
        }
    }
    return;
}

int findempty(Edge *a, int DIM){
    int i;
    for(i=0; i<DIM; i++){
        if(a[i].v == -1 && a[i].w == -1)
            return i;
    }
    return -1;
}



void EDGEconnected(Graph G, int j){
    int i;
    Edge *sol=malloc(G->E*sizeof(Edge));
    Edge *a=malloc(G->E*sizeof(Edge));
    GRAPHedges(G, a);

    for(i=0; i<j; i++)
        if(EDGEverify(G, i, a, sol, 0, 0)==0){
            printf("\nIl grafo, quindi, non e' %d-edge-connected poiche' esistono insiemi di archi di cardinalita' minore di %d in grado di disconnetterlo.\n", j, j);
            return;
        }
    if(EDGEfind(G, j, a, sol, 0, 0)==1){
        printf("\nIl grafo e', quindi, %d-edge-connected e questo esclude l'esistenza di insiemi di archi di cardinalita' minore di %d in grado di disconnetterlo.\n", j, j);
        printf("\nIl grafo sconnesso e':\n");
        GRAPHstore(G, stdout);
    }
    else
        printf("\nIl grafo non e' %d-edge-connected.\n", j);

    free(sol);
    free(a);
    return;
}

int EDGEverify(Graph G, int i, Edge *a, Edge *sol, int k, int start){
    int j, w;
    if(k>=i){
        for(j=0; j<k; j++)
            removeE(G, sol[j]);
        if(GRAPHcc(G)!=1){
            printf("Errore. Il grafo e' %d-edge-connected.\n", k);
            return 0;
        }
        for(j=0; j<k; j++)
            insertE(G, sol[j]);
        return 1;
    }

    for(w=start; w<G->E; w++){
        sol[k]=a[w];
        int res = EDGEverify(G, i, a, sol, k+1, start+1);
        if(res==0)
            return 0;
    }
    return 1;
}

int EDGEfind(Graph G, int j, Edge *a, Edge *sol, int k, int start){
    int i, w;
    if(k>=j){
        for(w=0; w<k; w++)
            removeE(G, sol[w]);
        if(GRAPHcc(G)!=1){
            printf("Il grafo e' un %d-edge-connected.\nGli archi da rimuovere affinche' esso venga disconnesso sono:\n", j);
            for(i=0; i<k; i++)
                printf( "%s   -   %s\n", STsearchByIndex(G->tab, sol[i].v), STsearchByIndex(G->tab, sol[i].w) );
            return 1;
        }
        for(w=0; w<k; w++)
            insertE(G, sol[w]);
        return 0;
    }

    for(w=start; w<G->E; w++){
        sol[k]=a[w];
        int res = EDGEfind(G, j, a, sol, k+1, start+1);
        if(res==1)
            return 1;
    }
    return 0;
}
