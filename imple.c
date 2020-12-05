#include "header.h"
#include "cd.h"
#include "pwd.h"
#include "echo.h"
#include "ls.h"
#include "pinfo.h"
#include "syscmd.h"
#include "history.h"
#include "envar.h"
#include "jobs.h"

const char c[]="cd";
const char p[]="pwd";
const char ech[]="echo";
const char l[]="ls";
const char pi[]="pinfo";
const char ex[]="quit";
const char his[]="history";
const char se[]="setenv";
const char unse[]="unsetenv";
const char jo[]="jobs";
const char kjo[]="kjob";
const char f[]="fg";
const char b[]="bg";
const char okil[]="overkill";

int imple(char* tok2 , char* curadd,char* revcuradd){
    char buff2[100005];
    const char s[2] = " ";
    char* tok= NULL;
    strcpy(buff2,tok2);
    tok = strtok(buff2,s);
    if(tok!=NULL){
        if(strcmp(tok,ex)==0){
            return 1;
        }
        else if(strcmp(tok,c)==0){
            cd(tok2,curadd,revcuradd);
        }
        else if(strcmp(tok,p)==0){
            pwd();
        }
        else if(strcmp(tok,ech)==0){
            echo(tok2);
        }
        else if(strcmp(tok,l)==0){
            ls(tok2);
        }
        else if(strcmp(tok,pi)==0){
            pinfo(tok2,revcuradd);
        }
        else if(strcmp(tok,his)==0){
            tok = strtok(NULL,s);
            if(tok==NULL || strlen(tok)==2){
                history(10);
            }
            else{
                int n = (tok[0]-'0');
                history(n);
            }
        }
        else if (strcmp(tok,se)==0){
            int re = senv(tok2);
        }
        else if(strcmp(tok,unse)==0){
            int re = unsev(tok2);
        }
        else if(strcmp(tok,jo)==0){
            jobs();
        }
        else if(strcmp(tok,kjo)==0){
            kjobs(tok2);
        }
        else if(strcmp(tok,f)==0){
            fg(tok2,1);
        }
        else if(strcmp(tok,b)==0){
            fg(tok2,0);
        }
        else if(strcmp(tok,okil)==0){
            overkill();
        }
        else{
            syscmd(tok2);
        }
    }
    return 0;
}