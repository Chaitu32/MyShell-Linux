#include "header.h"

int pid_job[10005];
int ppid_job[10005];
int pid_no_j;
extern int pidg;
char cmd_pid[105][1005];

void sigchild_h(int sig){
    int wtstatus ,exi=1;
    pid_t pid2 = waitpid(-1,&wtstatus,WNOHANG);
    if(WIFEXITED(wtstatus)){
        exi=0;
    }
    if(pid2>0){
        int temp;
        for(int i=0;i<pid_no_j;i++){
            if(pid_job[i]==pid2){
                temp=i;
                break;
            }
        }
        if(exi==0){
            fprintf(stderr,"\n%s with pid %d is exited normally",cmd_pid[temp],pid2);
        }
        else{
            fprintf(stderr,"\n%s with pid %d is exited abnormally",cmd_pid[temp],pid2);
        }
    }
}

void change_back(int sig){
    pid_job[pid_no_j] = getpid();
    fprintf(stdout,"\nProcess with pid %d is push to background to job number %d",pid_job[pid_no_j],pid_no_j);
    pid_no_j++;
}

void syscmd(char* buff){
    char b[100003];
    strcpy(b,buff);
    char *cmd;
    char *lastarg;
    char *tok;
    const char d[]=" \0";
    tok = strtok(b,d);
    cmd = tok;
    char *args[100003];
    int i=0;
    while(tok!=NULL){
        lastarg=tok;
        args[i]=tok;
        i++;
        tok = strtok(NULL,d);
    }
    args[i]=NULL;
    char end[]="&\0";
    int check=0,check2=0;
    if(strcmp(lastarg,end)==0 && i>1){
        args[i-1]=NULL;
        check=1;
    }
    int fd_p[2];
    if(check ==1){
        int r = pipe(fd_p);
        if(r<0){
            perror("Error at pipe");
            return;
        }
    }
    int pid = fork();
    int sz;
    if(pid<0){
        perror("Fail to create child");
        return;
    }
    if(pid==0){
        if(check==0){
            signal(SIGTSTP,change_back);
            signal(SIGINT,SIG_DFL);
            sz = execvp(cmd,args);
            if(sz<0){
                perror("Error at cmd");
                exit(1);
            } 
        }
        else{
            sz = execvp(cmd,args);
            if(sz<0){
                perror("Error at cmd");
                exit(1);
            }
            
        }
        exit(0);
    }
    else if(check==0){
        pidg=pid;
        waitpid(pid,NULL,WUNTRACED);
    }
    else{
        strcpy(cmd_pid[pid_no_j],cmd);
        signal(SIGCHLD,sigchild_h);
        pid_job[pid_no_j++]=pid;
    }
}