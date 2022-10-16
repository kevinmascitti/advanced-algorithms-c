#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include <stdio.h>
#include "ST.h"

typedef struct edge {
    int v;
    int w;
    int wt;
} Edge;

typedef struct graph *Graph;

Graph GRAPHinit(int V);
void  GRAPHfree(Graph G);
Graph GRAPHload(FILE *fin);
void  GRAPHstore(Graph G, FILE *fout);
int   GRAPHgetIndex(Graph G, char *label);
void  GRAPHinsertE(Graph G, int id1, int id2, int wt);
void  GRAPHremoveE(Graph G, int id1, int id2);
void  GRAPHedges(Graph G, Edge *a);
void  GRAPHgenerateLadj(Graph G);
void  GRAPHprintLadj(Graph G);
int   GRAPHciclico(Graph G);
int   GRAPHdfs(Graph G, int id);
void  dfsR(Graph G, Edge e, int *time, int *pre, int *post, int *st, int *flag);

int   edges(Graph G);
int   vertex(Graph G);
void  comb_sempl(int pos, Edge *val, Edge *sol, int k, int start, Graph G, int *massimo, Edge *sol_max);
void  GRAPHbuild(Graph G, Edge *sol_max, int k);
void  GRAPHrebuild(Graph G, Edge *sol, int k);
int   weightEDGES(Edge *a, int dim);
void  EDGESstore(Edge *a, int k, Graph G, FILE *fout);
void  rimuoviArchi(Graph G, int N, Edge *sol_max);
void  DAGmaxPath(Graph G, int id);

void  stampaMATR(Graph G);
int   PATHdfsR(Edge *tot, int *sol, int id1, int id2, int fine, int k, Graph G, int *sol_max, int *v);
int   esisteEdge(int id1, int id2, Edge *a, int E);
void  PATH(Graph G, int a, int b, Edge *tot);

#endif // GRAPH_H_INCLUDED
