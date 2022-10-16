#include <stdio.h>
#include <stdlib.h>

int ****malloc4d(int a, int b, int c, int d);
int fz(int ****m1, int ****m2, int ****m3, int ****m4, int i, int j, int k, int w);
int fr(int ****m1, int ****m2, int ****m3, int ****m4, int i, int j, int k, int w);
int ft(int ****m1, int ****m2, int ****m3, int ****m4, int i, int j, int k, int w);
int fs(int ****m1, int ****m2, int ****m3, int ****m4, int i, int j, int k, int w);
int ****malloc4d(int a, int b, int c, int d);
int MAX(int a, int b, int c, int d);
int max(int a, int b);

int main()
{
    int z, r, t, s, max1, max2, max3, max4, lettura=0, tot_test, ****m1, ****m2, ****m3, ****m4;
    FILE *fp=fopen("hard_test.txt", "r");

    if (fp==NULL)   return -1;
    fscanf(fp, "%d", &tot_test);
    while(fscanf(fp,"%d %d %d %d", &z, &r, &t, &s)!=EOF){ //nel file sono scritti in ordine diverso da come sono inseriti nel vettore
        m1 = malloc4d (z, r, t, s);
        m2 = malloc4d (z, r, t, s);
        m3 = malloc4d (z, r, t, s);
        m4 = malloc4d (z, r, t, s);
        lettura++;
        printf("TEST #%d\n", lettura);
        max1=fz(m1, m2, m3, m4, z, r, t, s);
        max2=fr(m1, m2, m3, m4, z, r, t, s);
        max3=ft(m1, m2, m3, m4, z, r, t, s);
        max4=fs(m1, m2, m3, m4, z, r, t, s);
        printf("%d %d %d %d", max1, max2, max3, max4);
        printf("Collana massima di lunghezza: %d.\n\n", MAX(max1,max2,max3,max4));
    }
    if(tot_test!=lettura){
        printf("Errore file.");
        return -1;
    }
    fclose(fp);

    return 0;
}

int ****malloc4d(int a, int b, int c, int d){
    int ****m, i, j, k, l;
    m = malloc((a+1)*sizeof(int ***));
    for (i = 0; i <= a; i++) {
        m[i] = malloc((b+1)*sizeof(int **));
        for (j = 0; j <= b; j++) {
            m[i][j] = malloc((c+1)*sizeof(int *));
            for (k = 0; k <= c; k++){
                m[i][j][k] = malloc((d+1)*sizeof(int));
                for(l = 0; l <= d; l++){
                    m[i][j][k][l]=-1;
                }
            }
        }
    }
    return m;
}

int fz(int ****m1, int ****m2, int ****m3, int ****m4, int i, int j, int k, int w){
    if(i<=0)
        return 0;
    if(m1[i][j][k][w]!=-1)
        return m1[i][j][k][w];
    return 1 + max(fz(m1,m2,m3,m4,i-1,j,k,w), fr(m1,m2,m3,m4,i-1,j,k,w));
}

int fr(int ****m1, int ****m2, int ****m3, int ****m4, int i, int j, int k, int w){
    if(j<=0)
        return 0;
    if(m2[i][j][k][w]!=-1)
        return m2[i][j][k][w];
    return 1 + max(ft(m1,m2,m3,m4,i,j-1,k,w), fs(m1,m2,m3,m4,i,j-1,k,w));
}

int ft(int ****m1, int ****m2, int ****m3, int ****m4, int i, int j, int k, int w){
    if(k<=0)
        return 0;
    if(m3[i][j][k][w]!=-1)
        return m3[i][j][k][w];
    return 1 + max(fz(m1,m2,m3,m4,i,j,k-1,w), fr(m1,m2,m3,m4,i,j,k-1,w));
}

int fs(int ****m1, int ****m2, int ****m3, int ****m4, int i, int j, int k, int w){
    if(w<=0)
        return 0;
    if(m4[i][j][k][w]!=-1)
        return m4[i][j][k][w];
    return 1 + max(ft(m1,m2,m3,m4,i,j,k,w-1), fs(m1,m2,m3,m4,i,j,k,w-1));
}

int MAX(int a, int b, int c, int d){
    if(a>=b && a>=c && a>=d)
        return a;
    else if(b>=a && b>=c && b>=d)
        return b;
    else if(c>=a && c>=b && c>=d)
        return c;
    else if(d>=a && d>=b && d>=c)
        return d;
    printf("Errore funzione Max.\n");
    return 0;
}

int max(int a, int b) {
    if (a > b)
        return a;
    return b;
}
