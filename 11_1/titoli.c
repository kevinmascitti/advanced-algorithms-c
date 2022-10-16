#include "titoli.h"

typedef struct titolo{
    char nome[21];
    BST bst;                //transazioni o quotazioni di un dato titolo. La chiave di ordinamento del BST e' la data.
};

typedef struct titoli{      //questo dato serve a rappresentare la lista di N titoli
    link head;
    int N;
};




Titoli TitoliInit(){
    Titoli a = malloc (sizeof *a);
    a->head=NULL;
    a->N=0;
    return a;
}

Titolo TitoloInit(){
    Titolo a = malloc(sizeof(*a));
    a->nome[0]='\0';
    a->bst=BSTInit();
    return a;
}

int Titoliisnull(Titoli lista){
    if(lista->head==NULL && lista->N==0)
        return 1;
    return 0;
}

int Titoloisnull(Titolo a){
    if(a->nome[0] == '\0' && BSTisnull(a->bst))
        return 1;
    return 0;
}

void LeggiFile(Titoli lista){
    int tot, aa, mm, gg, o, m, val, num, iter, i, j;
    link x;
    char nome[50];
    Titolo titolo=TitoloInit();
    BST bst=BSTInit();
    DataOra dataora;
    Quotazione quot=QUOTInit();
    Quotazione quotfind=QUOTInit();

    printf("Inserisci nome del file:\n");
    scanf("%s", nome);
    FILE *fin=fopen(nome, "r");
    if(fin==NULL){ printf("Errore file di ingresso.\n"); return; }

    fscanf(fin, "%d", &iter);
    for(i=0; i<iter; i++){                                 //LEGGO TITOLI
        fscanf(fin, "%s", nome);
        fscanf(fin, "%d", &tot);
        titolo=RicercaTitolo(lista->head, nome);
        if(Titoloisnull(titolo)){
            strcpy(titolo->nome, nome);
            titolo->bst=BSTInit();
            lista->head=SortListIns(lista->head, titolo);
        }

        for(j=0; j<tot; j++){                             //LETTURA TRANSAZIONI
            fscanf(fin, "%d/%d/%d", &aa, &mm, &gg);
            fscanf(fin, "%d:%d", &o, &m);
            fscanf(fin, "%d", &val);
            fscanf(fin, "%d", &num);
            dataora=NEWdataora(aa, mm, gg, o, m);
            quot=NEWquot(dataora, val, num);
            quotfind=searchRWrap(quot, titolo->bst);      //Ricerca in BST
            if(QUOTisnull(quotfind))
                BSTinsert_leafR(titolo->bst, quot);
            else
                inserisciQUOT(quot, quotfind);            //aggiorno dove trovo la stessa data
        }
    }
    printf("Caricamento avvenuto con successo!\n\n");
    for(x=lista->head; x!=NULL; x=x->next)
        displayTitolo(x->val);
    printf("\n\n");
    fclose(fin);
}

link newNode(Titolo val, link next){
    link x=malloc(sizeof *x);
    if(x==NULL)
        return NULL;
    else{
        x->val=val;
        x->next=next;
    }
    return x;
}

link SortListIns(link h, Titolo val){
    link x, p;
    if(h==NULL || strcmp(val->nome, h->val->nome)==-1)
        return newNode(val, h);
    for(x=h->next, p=h; x!=NULL && strcmp(val->nome, h->val->nome)==1; p=x, x=x->next);
    p->next=newNode(val, x);
    return h;
}

Titolo RicercaTitolo(link h, char *str){
    link x;
    if (h==NULL)
        return TitoloInit();
    for(x=h; x!=NULL; x=x->next){
        if(strcmp(str, x->val->nome)==0)
            return x->val;
    }
    return TitoloInit();
}

Titolo RicercaT(Titoli lista, char *str){
    return RicercaTitolo(lista->head, str);
}

void displayTitolo(Titolo a){
    printf("Titolo:\t\t%s\n", a->nome);
    BSTvisit(a->bst);
    printf("\n");
}

Quotazione RicercaQuot(Titolo tit){
    int aa, mm, gg;
    DataOra data;
    Quotazione q=QUOTInit();
    char tmp[11];
    printf("Inserisci una data:\n");
    scanf("%s", tmp);
    sscanf(tmp, "%d/%d/%d", &aa, &mm, &gg);
    data=NEWdataora(aa, mm, gg, 0, 0);
    q=NEWquot(data, 0, 0);
    return searchRWrap(q, tit->bst);
}

Quotazione BSTminT(Titolo sel, DataOra data) {
    return BSTmin(sel->bst, data);
}

Quotazione BSTmaxT(Titolo sel, DataOra data) {
    return BSTmax(sel->bst, data);
}

int camminoT(Titolo sel) {
    int camm=-1, minimo=1000, massimo=-1;        //valori arbitrari 'infiniti' che verranno sicuramente aggiornati nella funzione cammino
    return cammino(sel->bst, camm, &minimo, &massimo);
}

void balanceT(Titolo sel){
    BSTbalance(sel->bst);
}
