#include "pgList.h"
#include <string.h>

struct pgList_s{        //ADT di prima classe di tipo pgList_s, nel .h ne dichiaro il rispettivo
    linkPg headPg;      //puntatore *pgList_t, nuovo tipo allocato dinamicamente
    linkPg tailPg;
    int nPg;
};


pgList_t pgList_init(){ //creazione e allocazione dell'ADT di 1 classe
    pgList_t a;
    a = malloc ( sizeof(*a) );
    a->headPg=NULL;
    a->tailPg=NULL;
    a->nPg=0;
    return a;
}

//inserimento dei personaggi da file nella lista
void scriviPersonaggi(char *nfile, pgList_t pgList){
    Pg_t pers;
    char tmp[MAXSTR];
    FILE *fp=fopen(nfile, "r");
    if (fp==NULL){
            printf("File %s vuoto.\n", nfile);
        return;
    }
    while(fgets(tmp, "%s", fp)!=NULL){
        sscanf(tmp, "%s %s %s %d %d %d %d %d %d", pers.codice, pers.nome, pers.classe,
               &pers.stat_t.hp, &pers.stat_t.mp, &pers.stat_t.atk, &pers.stat_t.def, &pers.stat_t.mag, &pers.stat_t.spr);
        pers.equip=vettEquip_init();
        pgList->headPg=SortListIns_Pg(pgList->headPg, pers);
        (pgList->nPg)++; //incremento del numero totale dei personaggi
    }
    findtail(pgList);
    fclose(fp);
    return;
}

void stampaTUTTO(pgList_t pgList, vettInv_t vettInv){
    printf("%d personaggi:\n\n", pgList->nPg);
    stampa_Pg(pgList->headPg, vettInv);
    stampa_Inv(vettInv);
    return;
}

linkPg newNode_Pg(Pg_t val, linkPg next) {
    linkPg x = malloc(sizeof *x);
    if (x==NULL)
        return NULL;
    else {
        x->val = val;
        x->next = next;
    }
    return x;
}

linkPg SortListIns_Pg(linkPg h, Pg_t val){
    linkPg x, p;
    if (h==NULL)
        return newNode_Pg(val, h);
    for (x=h->next, p=h; x!=NULL; p=x, x=x->next);
    p->next = newNode_Pg(val, x);
    return h;
}

void stampa_Pg(linkPg h, vettInv_t vettInv){        //stampa la lista intera data la testa della lista dei personaggi
    linkPg x;
    if(h==NULL){
        printf("Lista vuota.\n\n");
        return;
    }
    for(x=h; x!=NULL; x=x->next){
        stampaRiga_Pg(x->val, vettInv);
        printf("\n");
    }
    return;
}

void aggiungi(pgList_t pgList, vettInv_t vettInv){
    int flag=0, cont=0;
    Pg_t a;
    char tmp[MAXSTR]="\0", copia[MAXSTR]="\0";
    Pg_t val;
    while(flag==0){
        flag=1;
        if(cont==0){
            printf("Aggiungi il personaggio. Le statistiche devono essere strettamente positive. Non inserire personaggi gia' esistenti in lista.\n");
            printf("<PGXXXX> <nome> <classe> <hp> <mp> <atk> <def> <mag> <spr>\n");
            flag=0;
        }
        val.equip=EQUIPsetvoid();
        cont=1;
        gets(tmp);
        if(tmp[0]!='\0'){
            sscanf(tmp, "%s %s %s %d %d %d %d %d %d",val.codice,val.nome,val.classe,
                   &val.stat_t.hp,&val.stat_t.mp,&val.stat_t.atk,&val.stat_t.def,&val.stat_t.mag,&val.stat_t.spr);
            if(val.codice[0]=='P' && val.codice[1]=='G' && val.stat_t.hp>0 && val.stat_t.hp>0 && val.stat_t.mp>0 &&
                                    val.stat_t.atk>0 && val.stat_t.def>0 && val.stat_t.mag>0 && val.stat_t.spr>0){
                if( eqPG(a ,PGsetvoid(), vettInv) ){
                    flag=0;
                    printf("\nErrore inserimento personaggio.\n\n");
                    return;
                }//se il pers inserito non si trova gia in lista, la f ritorna PGsetvoid. Quindi se ritorna PGsetvoid posso inserirlo altrimenti no
                strcpy(copia, val.nome);
                if(eqPG(SortListSearch_Pg(pgList,strlwr(copia)), PGsetvoid(), vettInv)==0)
                    printf("\nPersonaggio gia' presente in lista!\n\n");

                else{
                    pgList->headPg=SortListIns_Pg(pgList->headPg, val);
                    printf("\nPersonaggio inserito correttamente!\n\n");
                    return;
                }
            }
        }
    }
    return;
}

Pg_t elimina(pgList_t pgList){
    char nome[MAX];
    Pg_t i;
    printf("Inserisci il nome del personaggio che vuoi eliminare dalla lista dei personaggi.\n");
    scanf("%s", nome);
    strlwr(nome);
    i = listExtrKeyP(&pgList->headPg, nome);
    return i;
}

Pg_t SortListSearch_Pg(pgList_t pgList, char k[]) { //ricerca in lista non ordinata per codice inserito da tastiera
    linkPg h=pgList->headPg, x;
    char copia[MAX];

    for (x=h; x!=NULL; x=x->next){
        strcpy(copia, x->val.nome);
        strlwr(copia);
        if ( strcmp(copia, k) == 0 )
            return x->val;
    }
    return PGsetvoid();
}

Pg_t listExtrKeyP(linkPg *hp, char k[]) {  //estrazione da lista non ordinata per nome da tastiera
    linkPg *xp, t;
    char a[MAX];
    Pg_t i = PGsetvoid();
    for (xp=hp; (*xp)!=NULL; xp=&((*xp)->next)) {
        strcpy(a, (*xp)->val.nome);
        strlwr(a);
        if (strcmp(a, k) == 0){
            t = *xp;
            *xp = (*xp)->next;
            i = t->val;
            free(t);
            break;
        }
    }
    return i;
}

void agg_eq(pgList_t pgList, vettInv_t vettInv){
    int pos;
    char nome[MAX], ogg[MAX];
    Pg_t pg=PGsetvoid();
    int eqp=-1;
    linkPg h = pgList->headPg;

/*assegna al puntatore a Pg_t l'indirizzo del personaggio nella lista, corrispondente al nome
inserito da tastiera cosi' da modificare il campo equip di esso*/
    while(eqPG(pg, PGsetvoid(), vettInv)){
        printf("Scegli un personaggio a cui equipaggiare un oggetto.\n");
        scanf("%s", nome);
        strlwr(nome);
        pg=SortListSearch_Pg(pgList, nome);
        if(eqPG(pg,PGsetvoid(),vettInv))
            printf("Personaggio non trovato.\nRiprova.\n");
    }
    if( pieno(pg.equip) ){
        printf("Non puoi piu' equipaggiare questo personaggio perche' ha gia' raggiunto il massimo.\n");
        return;
    }

/*assegna al puntatore a tabEqui_t l'indirizzo dell'oggetto nel vettore Inv_t, corrispondente al nome
inserito da tastiera cosi' da assegnarlo poi al campo equip.vettEq[i] di Pg_t*/

    printf("\nScegli un oggetto da equipaggiare.\n");
    scanf("%s", ogg);
    strlwr(ogg);
    eqp=SortListSearch_Inv(vettInv, ogg);

    if( eqp==-1 ){
        printf("\nOggetto da equipaggiare non trovato nell'inventario.\n");
        return;
    }
    pos=findempty(pg.equip);
    aggiornaEquip(pg.equip, pos, eqp, 1);
    printf("\nOggetto equipaggiato con successo!\n");
    stampa_Equip(pg.equip, pos, vettInv);

    return;
}

void rim_eq(pgList_t pgList, vettInv_t vettInv){
    int eqp=-1;
    char nome[MAX], ogg[MAX];
    Pg_t pg=PGsetvoid();
    linkPg h = pgList->headPg;

    while(eqPG(pg, PGsetvoid(), vettInv)){
        printf("Scegli un personaggio a cui rimuovere un oggetto.\n");
        scanf("%s", nome);
        strlwr(nome);
        pg=SortListSearch_Pg(pgList, nome);
        if(eqPG(pg, PGsetvoid(), vettInv))
            printf("\nPersonaggio non trovato.\nRiprova.\n");
        else if(eqEQUIP(pg.equip, EQUIPsetvoid(), vettInv)){ // posso rimuovere un oggetto a chi non ne ha nessuno
            printf("Il personaggio scelto non e' equipaggiato con alcun oggetto.\n");
            return;
        }
     }
     while(eqp==-1){
        printf("\nScegli un oggetto da rimuovere.\n");
        scanf("%s", ogg);
        strlwr(ogg);
        eqp=SortListSearch_Inv(vettInv, ogg);
        if( eqp==-1 )
            printf("L'oggetto scelto non e' presente nell'inventario.\nRiprova.\n");
        else{
            eqp=SortListSearch_Equip(pg.equip, ogg, vettInv);
            if( eqp==-1 )
                printf("L'oggetto scelto non e' presente nell'equipaggiamento del personaggio scelto.\nRiprova.\n");
        }
    }

    stampa_Equip(pg.equip, eqp, vettInv);
    aggiornaEquip(pg.equip, 0, eqp, -1);
    printf("\n");
    printf("\nElemento rimosso dall'equipaggiamento.\n");
    return;
}

void stampaStats(pgList_t pgList, vettInv_t vettInv){
    char nome[MAX];
    Pg_t pg;
    linkPg h = pgList->headPg;
    printf("Inserisci il nome del personaggio.\n");
    scanf("%s", nome);
    strlwr(nome);
    pg=SortListSearch_Pg(pgList, nome);
    if( !eqPG (pg, PGsetvoid(), vettInv) ){
        printf("\n");
        stampaRiga_Pg(pg, vettInv);
        printf("\n");
    }
    else
        printf("\nPersonaggio non trovato.\n\n");
    return;
}

void findtail(pgList_t pgList){ //trova l'ultimo elemento della lista e lo salva in pgList
    linkPg x, h=pgList->headPg;
    for(x=h; x!=NULL; x=x->next){
        if(x->next==NULL){
            pgList->tailPg=x;
            return;
        }
    }
    return;
}

void stampaTesta_Pg(pgList_t pgList, vettInv_t vettInv){
    stampaRiga_Pg(pgList->headPg->val, vettInv);
    return;
}

void stampaCoda_Pg(pgList_t pgList, vettInv_t vettInv){
    stampaRiga_Pg(pgList->tailPg->val, vettInv);
    return;
}

void liberaList(pgList_t pgList){
    free(pgList);
    return;
}
