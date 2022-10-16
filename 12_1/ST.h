#ifndef ST_H_INCLUDED
#define ST_H_INCLUDED

typedef struct symboltable *ST;

ST    STinit(int maxN);
void  STfree(ST st);
int   STsize(ST st);
void  STinsert(ST st, char *str, int i);
int   STsearch(ST st, char *str);
char *STsearchByIndex(ST st, int i);


#endif // ST_H_INCLUDED
