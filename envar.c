#include "header.h"

int senv(char *tok){
    char buff[10005];
    strcpy(buff,tok);
    char *argv[15];
    int argc=0;
    char *tok2;
    const char de[2]=" ";
    tok2 = strtok(buff,de);
    argv[2]=NULL;
    while(tok2!=NULL && argc<3){
        argv[argc]=tok2;
        argc++;
        tok2= strtok(NULL,de);
    }
    if(argc>3){
        printf("Invaild arguments\n");
    }
    else if(argc<2){
        printf("Less arguments\n");
    }
    else{
        char* check = getenv(argv[1]);
        int ch=0;
        if(check!=NULL)
            ch=1;
        int stat = setenv(argv[1],argv[2],ch);
        if(stat<0){
            perror("Error at setting var");
            return 0;
        }
    }
    return 0;
}

int unsev(char *tok){
    char buff[10005];
    strcpy(buff,tok);
    char *argv[15];
    int argc=0;
    char *tok2;
    const char de[2]=" ";
    tok2 = strtok(buff,de);
    while(tok2!=NULL && argc<2){
        argv[argc++]=tok2;
        tok2 = strtok(NULL,de);
    }
    if(argc>2){
        printf("Invaild arguments\n");
    }
    else if(argc<2){
        printf("Less arguments\n");
    }
    else{
        int stat = unsetenv(argv[1]);
        if(stat<0){
            perror("Error at setting var");
            return 0;
        }
    }
    return 0;
}