#include "personaggi.h"

tabPg_t *scriviPersonaggi(char *nfile, tabPg_t *tabPg){
    Pg_t pers;
    char tmp[MAXSTR];
    FILE *fp=fopen(nfile, "r");
    if (fp==NULL){
        printf("File %s vuoto.\n", nfile);
        return tabPg;
    }
    //inserimento dei personaggi da file nella lista in tabPg
    while(fgets(tmp, "%s", fp)!=NULL){
        sscanf(tmp, "%s %s %s %d %d %d %d %d %d", pers.codice, pers.nome, pers.classe,
               &pers.stat_t.hp, &pers.stat_t.mp, &pers.stat_t.atk, &pers.stat_t.def, &pers.stat_t.mag, &pers.stat_t.spr);
        pers.equip=EQUIPsetvoid();//campo EQUIP inizialmente vuoto
        tabPg->headPg=SortListIns_Pg(tabPg->headPg, pers);
        (tabPg->nPg)++; //incremento del numero totale dei personaggi
    }
    tabPg->tailPg=findtail(tabPg->headPg);
    fclose(fp);
    return tabPg;
}


void stampaTUTTO(tabPg_t *tabPg, tabInv_t *tabInv){
    printf("%d personaggi:\n\n", tabPg->nPg);
    stampa_Pg(tabPg->headPg);
    printf("%d oggetti nell'inventario:\n\n", tabInv->nInv);
    stampa_Inv(tabInv->vettInv, tabInv->nInv);
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

void stampa_Pg(linkPg h){        //stampa la lista intera data la testa della lista dei personaggi
    linkPg x;
    if(h==NULL){
        printf("Lista vuota.\n\n");
        return;
    }
    for(x=h; x!=NULL; x=x->next){
        stampaRiga_Pg(x->val);
        printf("\n");
    }

    return;
}

void stampaRiga_Pg(Pg_t val){  //stampa un elemento della lista (struttura)
    tabEquip_t vuoto = EQUIPsetvoid();
    int i, hp=val.stat_t.hp, mp=val.stat_t.mp, atk=val.stat_t.atk, def=val.stat_t.def, mag=val.stat_t.mag, spr=val.stat_t.spr;
    if( !eqEQUIP (val.equip, vuoto) ){
        printf("%s\n%s\n%s\n", val.codice, val.nome, val.classe);
        for(i=0;i<maxeq;i++){
            if( val.equip.vettEq[i]!=NULL ){
                printf("%s %s %d %d %d %d %d %d\n",val.equip.vettEq[i]->nome,val.equip.vettEq[i]->tipo,
                       val.equip.vettEq[i]->stat_inv.hp,val.equip.vettEq[i]->stat_inv.mp,val.equip.vettEq[i]->stat_inv.atk,
                       val.equip.vettEq[i]->stat_inv.def,val.equip.vettEq[i]->stat_inv.mag,val.equip.vettEq[i]->stat_inv.spr);
                hp+=val.equip.vettEq[i]->stat_inv.hp; mp+=val.equip.vettEq[i]->stat_inv.mp; atk+=val.equip.vettEq[i]->stat_inv.atk;
                def+=val.equip.vettEq[i]->stat_inv.def; mag+=val.equip.vettEq[i]->stat_inv.mag; spr+=val.equip.vettEq[i]->stat_inv.spr;
            }
        }
        if(hp<1) hp=1; if(mp<1) mp=1; if(atk<1) atk=1; if(def<1) def=1; if(mag<1) mag=1; if(spr<1) spr=1;
        printf("%d %d %d %d %d %d", hp, mp, atk, def, mag, spr);
    }
    else
        printf("%s\n%s\n%s\n%d %d %d %d %d %d\n", val.codice, val.nome, val.classe, hp, mp, atk, def, mag, spr);
    return;
}


tabEquip_t EQUIPsetvoid(){
    tabEquip_t a;
    int i;
    a.inUso=0;
    for(i=0;i<maxeq;i++)
        a.vettEq[i]=NULL;
    return a;
}

Pg_t PGsetvoid(){
    Pg_t a;
    a.codice[0]='\0';
    a.nome[0]='\0';
    a.classe[0]='\0';
    a.equip=EQUIPsetvoid();
    a.stat_t.hp=a.stat_t.mp=a.stat_t.atk=a.stat_t.def=a.stat_t.mag=a.stat_t.spr=0;
    return a;
}


int eqEQUIP( tabEquip_t a, tabEquip_t b ){
    if(a.inUso==b.inUso){
        for(int i=0;i<maxeq;i++){
            if( a.vettEq[i]==NULL && b.vettEq[i]==NULL );
            else if( ((strcmp(a.vettEq[i]->nome,b.vettEq[i]->nome))!=0 || (strcmp(a.vettEq[i]->tipo,b.vettEq[i]->tipo))!=0 || (eqSTAT(a.vettEq[i]->stat_inv,b.vettEq[i]->stat_inv))==0) )
                return 0;
        }
        return 1;
    }
    return 0;
}


int eqPG(Pg_t a, Pg_t b){
    if(strcmp(a.codice,b.codice)==0&&strcmp(a.nome,b.nome)==0&&strcmp(a.classe,b.classe)==0&&eqEQUIP(a.equip,b.equip)&&eqSTAT(a.stat_t,b.stat_t))
        return 1;
    return 0;
}

linkPg aggiungi(linkPg h){
    int flag=0, cont=0;
    Pg_t a;
    char tmp[MAXSTR]="\0";
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
                if(eqPG( a ,PGsetvoid() )){
                    flag=0;
                    printf("\nErrore inserimento personaggio.\n\n");
                    return h;
                }//se il pers inserito non si trova gia in lista, la f ritorna PGsetvoid. Quindi se ritorna PGsetvoid posso inserirlo altrimenti no
                if(eqPG(SortListSearch_Pg(h,strlwr(val.nome)), PGsetvoid())==0)
                    printf("\nPersonaggio gia' presente in lista!\n\n");

                else{
                    h=SortListIns_Pg(h,val);
                    printf("\nPersonaggio inserito correttamente!\n\n");
                    return h;
                }
            }
        }
    }
    return h;
}

Pg_t elimina(linkPg h){
    char nome[MAX];
    Pg_t i;
    printf("Inserisci il nome del personaggio che vuoi eliminare dalla lista dei personaggi.\n");
    scanf("%s", nome);
    strlwr(nome);
    i = listExtrKeyP(&h, nome);
    return i;
}

Pg_t SortListSearch_Pg(linkPg h, char k[]) { //ricerca in lista non ordinata per codice inserito da tastiera
    linkPg x=h;
    char copia[MAX];

    for (x=h; x!=NULL; x=x->next){
        strcpy(copia, x->val.nome);
        strlwr(copia);
        if ( strcmp(copia, k) == 0 )
            return x->val;
    }
    return PGsetvoid();
}

Pg_t *PSortListSearch_Pg(linkPg h, char k[]) { //ricerca in lista non ordinata per codice inserito da tastiera
    linkPg x=h;
    char copia[MAX];

    for (x=h; x!=NULL; x=x->next){
        strcpy(copia, x->val.nome);
        strlwr(copia);
        if ( strcmp(copia, k) == 0 )
            return &(x->val);
    }
    return NULL;
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

void agg_eq(linkPg h, Inv_t a[], int tot_ogg){
    int pos;
    char nome[MAX], ogg[MAX];
    Pg_t *pg=NULL;
    Inv_t *eqp=NULL;

/*assegna al puntatore a Pg_t l'indirizzo del personaggio nella lista, corrispondente al nome
inserito da tastiera cosi' da modificare il campo equip di esso*/
    while(pg==NULL){
        printf("Scegli un personaggio a cui equipaggiare un oggetto.\n");
        scanf("%s", nome);
        strlwr(nome);
        pg=PSortListSearch_Pg(h, nome);
        if(pg==NULL)
            printf("Personaggio non trovato.\nRiprova.\n");
    }
    if(pg->equip.inUso>=maxeq){
        printf("Non puoi piu' equipaggiare questo personaggio perche' ha gia' raggiunto il massimo.\n");
        return;
    }

/*assegna al puntatore a tabEqui_t l'indirizzo dell'oggetto nel vettore Inv_t, corrispondente al nome
inserito da tastiera cosi' da assegnarlo poi al campo equip.vettEq[i] di Pg_t*/

    printf("\nScegli un oggetto da equipaggiare.\n");
    scanf("%s", ogg);
    strlwr(ogg);
    eqp=PSortListSearch_Inv(a, ogg, tot_ogg);

    if( eqp==NULL ){
        printf("\nOggetto da equipaggiare non trovato nell'inventario.\n");
        return;
    }
    pos=findempty(pg->equip.vettEq);
    pg->equip.inUso++;
    pg->equip.vettEq[pos]=eqp;
    printf("\nOggetto equipaggiato con successo!\n");

    return;
}

void rim_eq(linkPg h){
    int i;
    char nome[MAX], ogg[MAX];
    Pg_t *pg=NULL;
    Inv_t *eqp=NULL;
    while(pg==NULL){
        printf("Scegli un personaggio a cui rimuovere un oggetto.\n");
        scanf("%s", nome);
        strlwr(nome);
        pg=PSortListSearch_Pg(h, nome);
        if(pg==NULL)
            printf("\nPersonaggio non trovato.\nRiprova.\n");
    }
    printf("\nScegli un oggetto da rimuovere.\n");
    scanf("%s", ogg);
    strlwr(ogg);
    for(i=0; i<maxeq; i++){
        eqp=PSortListSearch_Inv(pg->equip.vettEq[i], ogg, maxeq);
        if(eqp!=NULL)
            break;
    }

    if( eqp==NULL ){
        printf("L'oggetto scelto non e' nel suo equipaggiamento.\n");
        return;
    }
    pg->equip.inUso--;
    printf("\nElemento eliminato dall'equipaggiamento.\n\n");
    stampaRiga_Inv(*eqp);
    printf("\n");
    pg->equip.vettEq[i]=NULL;
    return;
}

void stampaStats(linkPg h){
    char nome[MAX];
    Pg_t pg;
    printf("Inserisci il nome del personaggio.\n");
    scanf("%s", nome);
    strlwr(nome);
    pg=SortListSearch_Pg(h, nome);
    if( !eqPG (pg, PGsetvoid()) ){
        printf("\n");
        stampaRiga_Pg(pg);
        printf("\n");
    }
    else
        printf("\nPersonaggio non trovato.\n\n");
    return;
}

linkPg findtail(linkPg h){
    linkPg tail, x;
    for(x=h; x!=NULL; x=x->next){
        if(x->next==NULL){
            tail=x;
            return tail;
        }
    }
    return NULL;
}
