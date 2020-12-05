#include "header.h"

void pwd(){
    char  str[100005];
    char *s;
    s = getcwd(str,100000); 
    printf("%s\n",str); 
}