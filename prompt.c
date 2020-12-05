#include "header.h"

void prompt(char* curadd){
    struct passwd *ppointer;
    ppointer = getpwuid(getuid());
    char name[256];
    int nam = gethostname(name,255);
    if(nam<0){
        perror("Error at hostname");
        return;
    }
    printf("<%s@%s:%s>",ppointer->pw_name,name,curadd);
}