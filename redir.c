#include "header.h"
#include "imple.h"

const char in[2]="<";
const char op[2]=">";

int in_redir(char* tok){
    int fd1;
    char* tok3;
    tok3 = (char*)malloc(strlen(tok)*sizeof(char));
    strcpy(tok3,tok);
    fd1=open(tok3,O_APPEND|O_RDWR);
    if(fd1<0){
        perror("Error at input_file");
        return -1;
    }
    int fd2 =dup(STDIN_FILENO),fd3;
    fd3=dup2(fd1,STDIN_FILENO);
    if(fd3<0){
        perror("Error at dup");
        return -1;
    }
    return fd2;
}

int out_redir(char* tok, int flag_ap){
    int fd1;
    char* tok3;
    tok3 = (char*)malloc(strlen(tok)*sizeof(char));
    strcpy(tok3,tok);
    if(flag_ap==0)
        fd1=open(tok3,O_TRUNC | O_CREAT |O_RDWR,0644 );
    else 
        fd1=open(tok3,O_APPEND |O_CREAT |O_RDWR, 0664 );
    if(fd1<0){
        perror("Error at output_file");
        return -1;
    }
    int fd2 =dup(STDOUT_FILENO),fd3;
    fd3=dup2(fd1,STDOUT_FILENO);
    if(fd3<0){
        perror("Error at dup");
        return -1;
    }
    return fd2;
}

int redir(char* tok2,char* curadd,char* revcuradd){
    char buff2[100005];
    strcpy(buff2,tok2);
    const char de[2]=" " ;
    const char le[2]="<";
    const char grap[3]=">>";
    const char gr[2]=">";
    char* cmds_argv[10005];
    char* redir_files[10005]; 
    int cmds_argc=0;
    int redir_no[10005];
    int rd=0,fd_in=-1,fd_out=-1;
    char* tok ;
    tok = strtok(buff2,de);
    while(tok!=NULL){
        if(strcmp(tok,le)==0){
            tok=strtok(NULL,de);
            if(tok!=NULL){
                redir_files[rd]=tok;
                redir_no[rd]=0;
                rd++;
            }
            else{
                printf("Error at input file\n");
                return 0;
            }
        }
        else if(strcmp(tok,grap)==0){
            tok=strtok(NULL,de);
            if(tok!=NULL){
                redir_files[rd]=tok;
                redir_no[rd]=2;
                rd++;
            }
            else{
                printf("Error at output file\n");
                return 0;
            }
        }
        else if(strcmp(tok,gr)==0){
            tok=strtok(NULL,de);
            if(tok!=NULL){
                redir_files[rd]=tok;
                redir_no[rd]=1;
                rd++;
            }
            else{
                printf("Error at output file\n");
                return 0;
            }
        }
        else{
            cmds_argv[cmds_argc]= tok;
            cmds_argc++;
        }
        tok=strtok(NULL,de);
    }
    for(int i=0;i<rd;i++){
        int temp;
        switch (redir_no[i]){
        case 0 :
            temp = in_redir(redir_files[i]);
            if(fd_in==-1)
                fd_in=temp;
            break;
        case 1:
            temp=out_redir(redir_files[i],0);
            if(fd_out==-1)
                fd_out=temp;
            break;
        default:
            temp=out_redir(redir_files[i],1);
            if(fd_out==-1)
                fd_out=temp;
            break;
        }
        
    }
    char cmd[10005];
    char sp[]=" ";
    char end[]="\0";
    for(int i=0;i<cmds_argc;i++){
        strcat(cmd,cmds_argv[i]);
        strcat(cmd,sp);
    }
    int fd3;
    int sta=imple(cmd,curadd,revcuradd);
    fflush(stdout);
    strcpy(cmd,end);
    if(fd3=dup2(fd_in,STDIN_FILENO)<0 && fd_in!=-1){
        perror("Error at dup");
        return 0;
    }
    if(fd3=dup2(fd_out,STDOUT_FILENO)<0 && fd_out!=-1){
        perror("Error at dup");
        return 0;
    }
    return sta;
}