#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED
#include <stdio.h>

typedef struct edge {
    int v;
    int w;
} Edge;

typedef struct graph *Graph;

Graph GRAPHinit(int V);
void  GRAPHfree(Graph G);
Graph GRAPHload(FILE *fin);
void  GRAPHstore(Graph G, FILE *fout);
void  GRAPHinsertE(Graph G, int id1, int id2);
void  GRAPHremoveE(Graph G, int id1, int id2);
void  GRAPHedges(Graph G, Edge *a);
int   GRAPHcc(Graph G);
void  dfsRcc(Graph G, int v, int id, int *cc);

void  Kcore(Graph G, int k);
int   min(int *a, Graph G);
int   emptyV(Graph G);
void  ripristina(Graph G, Edge *removedEdges);
int   EDGEisnull(Edge e);
void  calcolaGradi(Graph G, int *gradi);
void  removeV(Graph G, int k, Edge *removedEdges, int *gradi);
void  rimuoviArchi(Graph G, int id, Edge *removedEdges);
int   findempty(Edge *a, int DIM);
void  EDGEconnected(Graph G, int j);
int   EDGEverify(Graph G, int i, Edge *a, Edge *sol, int k, int start);
int   EDGEfind(Graph G, int j, Edge *a, Edge *sol, int k, int start);


#endif // GRAPH_H_INCLUDED
