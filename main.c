#include "header.h"
#include "imple.h"
#include "prompt.h"
#include "history.h"
#include "pipe.h"

extern int pid_no_j;
extern int pid_job[10005];
int pidg;


int main(){
    int status=0;
    char curadd[100005]="~";
    char revcuradd[100005];
    getcwd(revcuradd,100000);
    pid_no_j=0;
    pidg=0;
    signal(SIGTSTP,SIG_IGN);
    signal(SIGINT,SIG_IGN);
    while(!status){
        prompt(curadd);
        char *buffer;
        char buff2[100005];
        size_t size_buff = 100005;
        buffer = (char *) (malloc(size_buff*(sizeof(char))));
        size_t rechar;
        rechar = getline(&buffer,&size_buff,stdin);
        if(rechar==-1){
            status=1;
            continue;
        }
        write_cmd(buffer);
        buffer[rechar-1]='\0';
        rechar--;
        char *tok2;
        const char deli[2]=";";
        char *re;
        strcpy(buff2,buffer);
        re = buff2;
        tok2 = strtok_r(re,deli,&re);  
        while(tok2!=NULL){
            int fd=dup(STDIN_FILENO),fd2=dup(STDOUT_FILENO);
            if(fd<0||fd2<0){
                perror("Error at dup");
            }
            status = pip(tok2,curadd,revcuradd);
            fd= dup2(fd,STDIN_FILENO);
            fd2 = dup2(fd2,STDOUT_FILENO);
            if(fd<0||fd2<0){
                perror("Error at dup2");
            }
            tok2 = strtok_r(re,deli,&re);
        }
        free(buffer);
    }
    return 0;
}