#include "header.h"

extern int pid_job[10005];
extern int pid_no_j;

void jobs(){
    for(int k=0;k<pid_no_j;k++){
        char ad[10005]="/proc/";
        int p=pid_job[k],i=0,chi=(int)'0';
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
        char ex1[]="/cmdline";
        strcat(ad,st);
        strcat(ad2,ex1);
        int fd = open(ad,O_RDONLY);
        if(fd<0){
            continue;
        }
        char buffile[100000];
        long long int sz=read(fd,buffile,100000);
        if(sz<0){
            perror("Error at reading process");
            return;
        }
        const char de[]=" ";
        char *tok;
        tok = strtok(buffile,de);
        tok = strtok(NULL,de);
        tok = strtok(NULL,de);
        const char r[]="R";
        const char s[]="S";
        int stat_r=0;
        if(strcmp(tok,r)==0 || strcmp(tok,s)==0)
            stat_r=1;
        fd = open(ad2,O_RDONLY);
        sz=read(fd,buffile,100000);
        if(sz<0){
            perror("Error at reading process");
            return;
        }
        printf("[%d] ",k);
        if(stat_r)
            printf("Running ");
        else
            printf("Stopped ");
        printf("%s [%d]\n",buffile,pid_job[k]);
    }
}

void kjobs(char* tok){
    char buf[10005];
    strcpy(buf,tok);
    const char de[]=" ";
    char *argv[5];
    int argc=0;
    char *tok2;
    tok2 = strtok(buf,de);
    while(tok2!=NULL && argc<4){
        argv[argc++]=tok2;
        tok2 = strtok(NULL,de);
    }
    if(argc!=3){
        printf("Invalid args\n");
        return ;
    }
    int jno=0,signo=0;
    int len1=strlen(argv[1]),len2=strlen(argv[2]);
    for(int i=0;i<len1;i++){
        jno*=10;
        jno+=(int)(argv[1][i]-'0');
    }
    for(int i=0;i<len2;i++){
        signo*=10;
        signo+=(int)(argv[2][i]-'0');
    }
    if(jno>=pid_no_j){
        printf("Invaild job number\n");
        return;
    }
    int ret= kill(pid_job[jno],signo);
    if(ret<0){
        perror("Error at signal");
        return ;
    }
}

void fg(char *tok, int check){
    char buf[10005];
    strcpy(buf,tok);
    const char de[]=" ";
    char *argv[5];
    int argc=0;
    char *tok2;
    tok2 = strtok(buf,de);
    while(tok2!=NULL && argc<3){
        argv[argc++]=tok2;
        tok2 = strtok(NULL,de);
    }
    if(argc!=2){
        printf("Invalid args \n");
        return ;
    }
    int jno=0;
    int len1=strlen(argv[1]);
    for(int i=0;i<len1;i++){
        jno*=10;
        jno+=(int)(argv[1][i]-'0');
    }
    if(jno>=pid_no_j){
        printf("Invaild job number\n");
        return;
    }
    int ret= kill(pid_job[jno],SIGCONT);
    if(ret<0){
        perror("Error at signal");
        return ;
    }
    if(check==1){
        waitpid(pid_job[jno],NULL,0);
    }
}

void overkill(){
    for(int i=0;i<pid_no_j;i++){
        int ret= kill(pid_job[i],9);
    }
}