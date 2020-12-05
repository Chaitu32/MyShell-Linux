#include "header.h"
#include "redir.h"

int pip(char *tok,char *curadd,char *revcuradd){
    char buff[10005];
    strcpy(buff,tok);
    char *tok2;
    const char de[2]="|";
    char* ref;
    ref = buff;
    tok2 = strtok_r(ref,de,&ref);
    char *last_cmd;
    int last_fd=-1,last_fdl=-1,sta=0;
    while(tok2!=NULL ){
        if(sta!=0)
            break;
        last_cmd= tok2;
        tok2=strtok_r(ref,de,&ref);
        if(tok2!=NULL){
            int pipe_fd[2];
            int fd = pipe (pipe_fd);
            if(fd<0){
                perror("Error at pipe");
                return 0;
            }
            int pid = fork();
            if(pid<0){
                perror("Error at fork");
                return 0;
            }
            if(pid==0){
                close(pipe_fd[0]);
                int fd2 = dup(STDOUT_FILENO);
                if(fd2<0){
                    perror("Error at dup");
                    return 0;
                }
                int fd3 = dup2(pipe_fd[1],STDOUT_FILENO);
                if(fd3<0){
                    perror("Error at dup2");
                    return 0;
                }
                sta= redir(last_cmd,curadd,revcuradd);
                int re =dup2(fd2,STDOUT_FILENO);
                if(re<0){
                    perror("Error at dup2");
                    return 0;
                }
                exit(0);
            }
            else{
                wait(NULL);
                close(pipe_fd[1]);
                last_fd= dup(STDIN_FILENO);
                if(last_fd<0){
                    perror("Error at dup");
                    return 0;
                }
                if(last_fdl=-1){
                    last_fdl=last_fd;
                }
                int fd3 = dup2(pipe_fd[0],STDIN_FILENO);
                if(fd3<0){
                    perror("Error at dup2");
                    return 0;
                }
            }
        }
    }
    if(sta==0){
        sta = redir(last_cmd,curadd,revcuradd);
    }
    if(last_fdl!=-1){
        int re= dup2(last_fdl,STDIN_FILENO);
        if(re<0){
            perror("Error at dup2");
            return 0;
        }
    }
    return sta;
}