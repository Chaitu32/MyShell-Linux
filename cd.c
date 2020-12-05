#include "header.h"

void  cd(char* buff,char* curadd,char* homadd){
    const char dl[2]=" ";
    char* token;
    token = strtok(buff,dl);
    token = strtok( 0 ,dl);
    if(token==NULL || strcmp(token,"~")==0)
        token=homadd;
    int n = chdir(token);
    if(n<0){
        perror("Error opening dir");
        return;
    }
    char str[100005];
    getcwd(str,100000);
    int lenofh = strlen(homadd);
    int lenofc = strlen(str);
    if(lenofc>=lenofh){
        char s[100005];
        for(int i=0;i<lenofh;i++){
            s[i]=str[i];
        }
        s[lenofh]='\0';
        int c= strcmp(s,homadd);
        if(c==0 && (str[lenofh]=='/' || str[lenofh]=='\0')){
            curadd[0]='~';
            for(int i=1;i<lenofc-lenofh+1;i++){
                curadd[i]=str[i+lenofh-1];
            }
            curadd[lenofc-lenofh+1]='\0';
        }
        else{
            strcpy(curadd,str);
        }
        
    }
    else{
        strcpy(curadd,str);
    }
    
}