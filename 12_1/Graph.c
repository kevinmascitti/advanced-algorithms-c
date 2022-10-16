#include <stdlib.h>
#include <stdio.h>
#include "Graph.h"

#define MAXC 31

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

static       Edge EDGEcreate(int v, int w, int wt);
static int   **MATRIXint(int r, int c, int val);
static void  insertE(Graph G, Edge e);
static void  removeE(Graph G, Edge e);
static link  NEWnode(int v, link next);
static void  TSdfsR(Graph G, int v, int w, int *pre, int *ts, int *time);
static int   parent(int *id, int i);

static Edge EDGEcreate(int v, int w, int wt) {
  Edge e;
  e.v = v;
  e.w = w;
  e.wt = wt;
  return e;
}

static int **MATRIXint(int r, int c, int val) {
  int i, j;
  int **t = malloc(r * sizeof(int *));
  if (t == NULL)
    return NULL;
  for (i=0; i < r; i++) {
    t[i] = malloc(c * sizeof(int));
    if (t[i] == NULL)
      return NULL;
  }
  for (i=0; i < r; i++)
    for (j=0; j < c; j++)
      t[i][j] = val;
  return t;
}

Graph GRAPHinit(int V) {
  Graph G = malloc(sizeof *G);
  if (G == NULL)
    return NULL;
  G->V = V;
  G->E = 0;
  G->madj = MATRIXint(V, V, 0);
  if (G->madj == NULL)
    return NULL;
  G->ladj = malloc(V*sizeof(link));
  if (G->ladj == NULL)
    return NULL;
  for (int v = 0; v < G->V; v++)
    G->ladj[v] = G->z;
  G->tab = STinit(V);
  if (G->tab == NULL)
    return NULL;
  return G;
}

void GRAPHfree(Graph G) {
  int i;
  link t, next;
  for (i=0; i < G->V; i++)
    for (t=G->ladj[i]; t != G->z; t = next) {
      next = t->next;
      free(t);
    }
  for (i=0; i<G->V; i++)
    free(G->madj[i]);
  free(G->madj);
  free(G->ladj);
  STfree(G->tab);
  free(G);
}

Graph GRAPHload(FILE *fin) {
  int V, i, id1, id2, wt;
  char label1[MAXC], label2[MAXC];
  Graph G;

  fscanf(fin, "%d", &V);
  G = GRAPHinit(V);

  for (i=0; i<V; i++) {
    fscanf(fin, "%s", label1);
    STinsert(G->tab, label1, i);
  }

  while(fscanf(fin, "%s %s %d", label1, label2, &wt) == 3) {
    id1 = STsearch(G->tab, label1);
    id2 = STsearch(G->tab, label2);
    if (id1 >= 0 && id2 >=0)
      GRAPHinsertE(G, id1, id2, wt);
  }

  GRAPHgenerateLadj(G);

  return G;
}

static void  insertE(Graph G, Edge e) {
  int v = e.v, w = e.w, wt = e.wt;

  if (G->madj[v][w] == 0)
    G->E++;
  G->madj[v][w] = wt;
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
    fprintf(fout, "\n");
    for (i = 0; i < G->E; i++)
        fprintf(fout, "%s - %s      Peso:   %d\n", STsearchByIndex(G->tab, a[i].v), STsearchByIndex(G->tab, a[i].w), a[i].wt);
    fprintf(fout, "\n");

    free(a);
}

int GRAPHgetIndex(Graph G, char *label) {
  int id;
  id = STsearch(G->tab, label);
  if (id == -1) {
    id = STsize(G->tab);
    STinsert(G->tab, label, id);
  }
  return id;
}

void GRAPHinsertE(Graph G, int id1, int id2, int wt) {
  insertE(G, EDGEcreate(id1, id2, wt));
}

void GRAPHremoveE(Graph G, int id1, int id2) {
  removeE(G, EDGEcreate(id1, id2, 0));
}

static void  removeE(Graph G, Edge e) {
  int v = e.v, w = e.w;
  if (G->madj[v][w] != 0)
    G->E--;
  G->madj[v][w] = 0;
}

void  GRAPHedges(Graph G, Edge *a) {
  int v, w, E = 0;
  for (v=0; v < G->V; v++)
    for (w=0; w < G->V; w++)
      if (G->madj[v][w] != 0)
        a[E++] = EDGEcreate(v, w, G->madj[v][w]);
}

static link NEWnode(int v, link next){
    link x = malloc(sizeof(*x));
    x->v = v;
    x->next = next;
    return x;
}

//genero la lista di adiacenze per poterla utilizzare nella funzione standard dfsR
void GRAPHgenerateLadj(Graph G){
    int V = G->V;
    int i, j;
    link t, next;
    if(G->ladj != NULL){
        for (i=0; i < V; i++)
            for (t=G->ladj[i]; t != G->z; t = next) {
                next = t->next;
                free(t);
            }
        free(G->ladj);
    }
    G->ladj = malloc(V*sizeof(link));
    for(i = 0; i < V; i++)
        for(j = 0; j < V; j++)
            if(G->madj[i][j] != 0)
                G->ladj[i] = NEWnode(j, G->ladj[i]);
}

int GRAPHciclico(Graph G){
    return GRAPHdfs(G, 0);
}

int GRAPHdfs(Graph G, int id){
    int v, time=0, *pre, *post, *st, flag=0;
    pre=malloc(G->V*sizeof(int));
    post=malloc(G->V*sizeof(int));
    st=malloc(G->V*sizeof(int));
    for(v=0; v<G->V; v++){
        pre[v]=-1;
        post[v]=-1;
        st[v]=-1;
    }
    dfsR(G, EDGEcreate(id, id, 0), &time, pre, post, st, &flag);
    for(v=0; v<G->V; v++)
        if(pre[v]==-1)
            dfsR(G, EDGEcreate(v, v, 0), &time, pre, post, st, &flag);
    free(pre);
    free(post);
    free(st);
    if(flag){
        return 1;
    }
    return 0;
}

void dfsR(Graph G, Edge e, int *time, int *pre, int *post, int *st, int *flag){
    link t;
    int v, w=e.w;

    st[e.w]=e.v;
    pre[w]=(*time)++;
    for(t=G->ladj[w]; t!=G->z; t=t->next){
        if(pre[t->v]==-1){
            dfsR(G, EDGEcreate(w, t->v, 0), time, pre, post, st, flag);
        }
        else{
            v=t->v;
            if(pre[w]<pre[v]){
                *flag=1;
                return;
            }
            if(post[v]==-1){
                *flag=1;
                return;
            }
        }
    }
    post[w]=(*time)++;
    return;
}

int edges(Graph G){
    return G->E;
}

int vertex(Graph G){
    return G->V;
}

void comb_sempl(int pos, Edge *val, Edge *sol, int k, int start, Graph G, int *massimo, Edge *sol_max){
    int i;

    if(pos>=k){
        GRAPHbuild(G, sol, k);
        if(GRAPHciclico(G)==0){
            printf("Insieme di archi a cardinalita' %d da rimuovere:\n", k);
            EDGESstore(sol, k, G, stdout);
            if(weightEDGES(sol, k)>(*massimo)){
                *massimo=weightEDGES(sol, k);
                for(i=0; i<k; i++)
                    sol_max[i]=sol[i];
            }
        }
        GRAPHrebuild(G, sol, k);
        return;
    }

    for(i=start; i<G->E; i++){
        sol[pos]=val[i];
        comb_sempl(pos+1, val, sol, k, i+1, G, massimo, sol_max);
    }
}

void GRAPHbuild(Graph G, Edge *sol, int k){
    int i;
    for(i=0; i<k; i++)
        removeE(G, sol[i]);
    GRAPHgenerateLadj(G);
}

void GRAPHrebuild(Graph G, Edge *sol, int k){
    int i;
    for(i=0; i<k; i++)
        insertE(G, sol[i]);
    GRAPHgenerateLadj(G);
}

int weightEDGES(Edge *a, int dim){
    int wt=0, i;
    for(i=0; i<dim; i++)
        wt+=a[i].wt;
    return wt;
}

void EDGESstore(Edge *a, int k, Graph G, FILE *fout) {
  int i;
  for (i = 0; i < k; i++)
    fprintf(fout, "%s - %s       Peso:   %d\n", STsearchByIndex(G->tab, a[i].v), STsearchByIndex(G->tab, a[i].w), a[i].wt);
  fprintf(fout, "\n");
}

void rimuoviArchi(Graph G, int N, Edge *sol_max){
    for(int i=0; i<N; i++){
        removeE(G, sol_max[i]);
    }
}

static void TSdfsR(Graph G, int v, int w, int *pre, int *ts, int *time){
    pre[w] = v;
    for(int i = 0; i < G->V; i++){
        if(G->madj[w][i] != 0)
            if(pre[i] == -1)
                TSdfsR(G, w, i, pre, ts, time);
    }
    ts[(*time)++] = w;
}

static int parent(int *pre, int i){  //trova l'antenato di un vertice
    if(pre[i] == i)
        return i;
    return parent(pre, pre[i]);
}
void DAGmaxPath(Graph G, int id){
    int *pre = malloc(sizeof(int)*G->V);
    int *ts = malloc(sizeof(int)*G->V);
    int time = 0;
    int i;
    for(i = 0; i < G->V; i++){
        pre[i] = ts[i] = -1;
    }
    TSdfsR(G, id, id, pre, ts, &time);
    for(i = 0; i < G->V; i++)
        if(pre[i] == -1)
            TSdfsR(G, i, i, pre, ts, &time);

    int *d = malloc(sizeof(int)*G->V);
    for(i = 0; i < G->V; i++){
        d[i] = 0;
    }
    for(i = time-1; i >= 0; i--){       //ordine topologico inverso perche' applico la relaxation al contrario per trovare il cammino massimo dal nodo sorgente
        for(int v = 0; v < G->V; v++){
            if(G->madj[ts[i]][v] != 0 && parent(pre, v) == id && parent(pre, ts[i]) == id){ //controllo che l'arco esista e che entrambi i vertici dell'arco trovato abbiano lo stesso antenato = nodo sorgente
                if(d[ts[i]] + G->madj[ts[i]][v] > d[v]){        //relaxation al contrario
                    d[v] = d[ts[i]] + G->madj[ts[i]][v];
                }
            }
        }
    }
    printf("Partendo dal nodo %s: (i nodi irraggiungibili non vengono mostrati)\n", STsearchByIndex(G->tab, id));
   for(i = 0; i < time; i++){
       if(d[ts[i]] != 0)
           printf("\t%s %d\n", STsearchByIndex(G->tab, ts[i]), d[ts[i]]);
    }
    free(pre);
    free(ts);
    free(d);
}

void stampaMATR(Graph G){
    for(int i=0; i<G->V; i++){
        for(int j=0; j<G->V; j++){
            printf("%d  ", G->madj[i][j]);
        }
        printf("\n");
    }
}
