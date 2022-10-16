#ifndef GRAPH_H_INCLUDED
#define GRAPH_H_INCLUDED

#include "ST.h"

typedef struct edge {
    int v;
    int w;
    int wt;
} Edge;

typedef struct graph *Graph;

Graph GRAPHinit(int V);
void  GRAPHfree(Graph G);
Graph GRAPHload(FILE *);
void  GRAPHinsertE(Graph G, int id1, int id2, int wt);
int   GRAPHgetIndex(Graph G, char *label, char *label2);
void  GRAPHstore(Graph G, FILE *fout);
void  GRAPHedges(Graph G, Edge *a);
void GRAPHStampaOrdinato(Graph G);
void Merge(char **A, char **B, int l, int q, int r);
void MergeSortR(char **A, char **B, int l, int r);
void MergeSort(char **A, int N);
void GRAPHverifyM(Graph G, char words[][30]);
void GRAPHverifyL(Graph G, char words[][30]);

#endif // GRAPH_H_INCLUDED
