#include "header.h"

void pinfo(char* buff,char* homadd){
    char* token;
    const char d[2]=" ";
    token = strtok(buff,d);
    token = strtok(NULL,d);
    int pid=0;
    if(token==NULL){
        pid = getpid();
    }
    else{
        int len=strlen(token);
        int c=1;
        char ch='0';
        for(int i=len-1;i>=0;i--){
            pid+=((int)token[i]-(int)ch)*c;
            c=c*10;
        }
    }
    char ad[]="/proc/";
    int p=pid,i=0,chi=(int)'0';
    char pd[10000];
    while(p>0){
        pd[i]=(char)(chi+p%10);
        p=p/10;
        i++;
    }
    char pd2[i+1];
    for(int j=0;j<i;j++)
        pd2[j]=pd[i-j-1];
    pd2[i]='\0';
    strcat(ad,pd2);
    char ad2[10000];
    strcpy(ad2,ad);
    char st[]="/stat";
    char ex1[]="/exe";
    strcat(ad,st);
    strcat(ad2,ex1);
    int fd = open(ad,O_RDONLY);
    if(fd<0){
        perror("Error at pid");
    }
    char buffile[1000000];
    long long int sz=read(fd,buffile,1000000);
    if(sz<0){
        perror("Error at reading process");
        return;
    }
    buffile[sz]='\0';
    printf("pid -- %d\n",pid);
    char *token2;
    int executep=1,stat=2,vsize=22;
    char ex[100005],sta[10],vsiz[1000],ex2[100005];
    token2 =strtok(buffile,d);
    for(int j=1;j<=vsize;j++){
        token2 = strtok(NULL,d);
        if(j==executep){
            strcpy(ex2,token2);
        }
        else if (j==stat){
            strcpy(sta,token2);
        }
        else if (j==vsize){
            strcpy(vsiz,token2);
        }
    }
    char curadd[100005];
    long long int sa = readlink(ad2,ex,100000);
    if(sa<0){
        strcpy(curadd,ex2);
    }
    else{
        ex[sa]='\0';
        int lenofh = strlen(homadd);
        int lenofc = strlen(ex);
        if(lenofc>=lenofh){
            char s[100005];
            for(int i=0;i<lenofh;i++){
                s[i]=ex[i];
            }
            s[lenofh]='\0';
            int c= strcmp(s,homadd);
            if(c==0 && (ex[lenofh]=='/' || ex[lenofh]=='\0')){
                curadd[0]='~';
                for(int i=1;i<lenofc-lenofh+1;i++){
                    curadd[i]=ex[i+lenofh-1];
                }
                curadd[lenofc-lenofh+1]='\0';
            }
            else{
                strcpy(curadd,ex);
            }
            
        }
        else{
            strcpy(curadd,ex);
        }
    }
    close(fd);
    printf("Process status -- %s\nMemory -- %s\nExecutable Path -- %s\n",sta,vsiz,curadd);
}