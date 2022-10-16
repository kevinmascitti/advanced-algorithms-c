    #include <stdio.h>
    #include <stdlib.h>
    #include <ctype.h>
    #include <string.h>

    int conta(char s[], int n);

    int main(){
        int i=0, lung=0, numero=0, parole=0, righe=0, tot=0;
        char file[20+1], info[20+1];
        FILE *fp;

        printf("Inserisci nome del file:\n");
        scanf("%s",file);
        printf("Inserisci la lunghezza n delle sottostringhe cercate:\n");
        scanf("%d",&lung);

        fp=fopen(file,"r");

        while(fscanf(fp,"%s",info)!=EOF){
            if(righe>0){
                numero=conta(info,lung);
            }
            else{
                sscanf(info,"%d",&righe);
            }
            tot=tot+numero;
        }

        fclose(fp);

        printf("Il numero totale di sottostringhe contenute nelle %d parole contenute nel file e' %d.\n", righe, tot);

        return 0;
    }

    int conta(char s[], int n){
        int k=0, j=0, vocali=0, sottostringhe=0;
            for(k=0;k<=(strlen(s)-n);k++){
                for(j=k;j<k+n;j++){
                    if((tolower(s[j])=='a')||(tolower(s[j])=='e')||(tolower(s[j])=='i')||(tolower(s[j])=='o')||(tolower(s[j])=='u')){
                        vocali++;
                    }
                }
                if(vocali==2){
                    printf("Una sottostringa e': \"");
                    for(j=k;j<k+n;j++){
                        printf("%c", s[j]);
                    }
                    printf("\"\n");
                    sottostringhe++;
                }
                vocali=0;
            }
        return sottostringhe;
    }
