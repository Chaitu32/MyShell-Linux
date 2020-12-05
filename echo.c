#include "header.h"

void echo(char* buff){
    long long int len = strlen(buff);
    int check =0;
    for(long long int i=0;i<len;i++){
        if(check){
            if(buff[i]!=' '){
                int j=0;
                if(buff[i]=='"' || buff[i]=='\''){
                    char c=buff[i];
                    i++;
                    char s[100005];
                    j=0;
                    while(buff[i]!=c && i<len){
                        s[j]=buff[i];
                        j++;
                        i++;
                    }
                    s[j]='\0';
                    printf("%s ",s);
                }
                else {
                    char s[100005];
                    j=0;
                    while(buff[i]!=' ' && i<len){
                        s[j]=buff[i];
                        j++;
                        i++;
                    }
                    s[j]='\0';
                    printf("%s ",s);
                }
            }
        }
        else if(buff[i]=='e'){
            check=1;
            i=i+3;
        }
    }
    printf("\n");
}