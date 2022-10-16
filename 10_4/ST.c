#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "ST.h"

struct symboltable {
    char *a[31];
    int maxN;
    int N;
};

ST STinit(int maxN) {
  ST st;
  st = malloc(sizeof (*st));
  if (st == NULL) {
    printf("Memory allocation error\n");
    return NULL;
  }
  if (st->a == NULL) {
    printf("Memory allocation error\n");
    free(st);
    return NULL;
  }
  st->maxN = maxN;
  st->N = 0;
  return st;
}

void STfree(ST st) {
  int i;
  if (st==NULL)
    return;
  for (i=0; i<st->N; i++)
    if (st->a[i] != NULL)
      free(st->a[i]);
  free(st->a);
  free(st);
}

int STsize(ST st) {
  return st->N;
}

void STinsert(ST st, char *str, int i) {
  if (i >= st->maxN) {
    if (st->a == NULL)
      return;
    st->maxN = 2*st->maxN;
  }
  st->a[i] = strdup(str);
  st->N++;
}

int STsearch(ST st, char *str) {
  int i;
  for (i = 0; i  < st->N; i++)
    if (st->a[i]!=NULL && strcmp(str, st->a[i])==0)
      return i;
  return -1;
}

char *STsearchByIndex(ST st, int i){
  if (i < 0 || i >= st->N)
    return NULL;
  return (st->a[i]);
}

int ITEMleq(char *A, char *B){
    if(strcmp(A,B)==-1||strcmp(A,B)==0)
        return 1;
    return 0;
}
