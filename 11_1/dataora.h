#ifndef DATAORA_H_INCLUDED
#define DATAORA_H_INCLUDED

typedef struct dataora{
    int aa;
    int mm;
    int gg;
    int o;
    int m;
} DataOra;




DataOra DATAORAInit();
int DATAisnull(DataOra a);

DataOra NEWdataora(int aa, int mm, int gg, int o, int m);
int AgtB(DataOra a, DataOra b);
int AgtBDATA(DataOra a, DataOra b);
int AMGgt(int aa, int mm, int gg, DataOra a);
void inserisciDate (DataOra *mi, DataOra *ma);

#endif // DATAORA_H_INCLUDED
