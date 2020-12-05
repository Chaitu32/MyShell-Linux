#include "header.h"

void history(int num){
    if(num>10){
        num=10;
    }
    const char fnam[]="myshell_his.txt";
    int fd = open(fnam,O_RDWR | O_CREAT |O_APPEND,0644); 
    if(fd<0){
        perror("Error opening file");
        exit(1);
    }
    char buffer[1000055];
    long long int sz = read(fd,buffer,1000055);
    if(sz<0){
        perror("Error reading file");
        exit(1);
    }
    int args=0;
    char *tok;
    const char de[]="\n";
    tok = strtok(buffer,de);
    while(tok!=NULL&&args<num){
        printf("%s\n",tok);
        args++;
        tok = strtok(NULL,de);
    }
    close(fd);
}

void write_cmd(char* buff){
    const char fnam[]="myshell_his.txt";
    int fd = open(fnam,O_RDWR | O_CREAT |O_APPEND,0644); 
    if(fd<0){
        perror("Error opening file");
        exit(1);
    }
    char buffer[1000055];
    long long int sz = read(fd,buffer,1000055);
    if(sz<0){
        perror("Error reading file");
        exit(1);
    }
    int args=0;
    char *argv[100005];
    char *tok;
    const char de[]="\n";
    tok = strtok(buffer,de);
    while(tok!=NULL){
        argv[args]=tok;
        args++;
        tok = strtok(NULL,de);
    }
    if(args>=20){
        args=19;
    }
    close(fd);
    fd = open(fnam,O_RDWR | O_CREAT |O_TRUNC,0644); 
    if(fd<0){
        perror("Error opening file");
        exit(1);
    }
    long long int len=strlen(buff),len2;
    char inse[1000055];
    strcpy(inse,buff);
    long long int j = strlen(inse);
    for(int i=0;i<args;i++){
        len = strlen(argv[i])+j;
        len2 = j;
        while(j<len){
            inse[j]=argv[i][j-len2];
            j++;
        }
        inse[j++]='\n';
    }
    inse[j]='\0';
    long long int sz3=write(fd,inse,strlen(inse));
    if(sz3<0){
        perror("Error at write");
        exit(1);
    }
    close(fd);
}