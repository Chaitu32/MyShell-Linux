#include "header.h"


void ls(char* buff){
    char buffer[100005],b2[100005];
    strcpy(buffer,buff);
    strcpy(b2,buffer);
    int arg=1;
    const char d[2]=" ";
    char *tok;
    tok = strtok(buffer,d);
    while((tok=strtok(NULL,d))!=NULL){
        arg++; 
    }
    int i=0;
    tok = strtok(b2,d);
    char *args[arg+1];
    while(i<arg && tok){
        args[i]=tok;
        tok = strtok(NULL,d);
        i++;
    }
    args[arg]=NULL;
    int c;
    int aflag=0,lflag=0,fflag=0;
    char filename[10000];
    for(int i=1;i<arg;i++){
        if(args[i][0]=='-'){
            int le=strlen(args[i]);
            for(int j=1;j<le;j++){
                if(args[i][j]=='a')
                    aflag=1;
                else if(args[i][j]=='l')
                    lflag=1;
                else{
                    printf("invaild flag\n");
                    return;
                }
            }
        }
        else if(fflag==0){
            strcpy(filename,args[i]);
            fflag=1;
        }
        else{
            printf("INVAILD ARGS");
            return;
        }
        
    } 
    if(fflag==0){
        char fil[]=".";
        strcpy(filename,fil);
    }
    DIR *dir;
    dir=opendir(filename);
    if(dir==NULL){
        printf("Error at opening dir");
        return;
    }
    struct dirent *dr;
    dr = readdir(dir);
    if(lflag==1){
        struct stat bu;
        int sz1= stat(filename,&bu);
        if(sz1<0){
            perror("Error at stat");
            return ;
        }
        printf("total %ld\n",bu.st_blksize);
    }
    while(dr!=NULL){
        char name[256];
        strcpy(name,dr->d_name);
        dr=readdir(dir);
        if(aflag==0 && name[0]=='.')
            continue;
        if(lflag==0){
            printf("%s  ",name);
            if(dr==NULL)
                printf("\n");
        }
        else{
            char addfil[100005];
            char perm[11]="-rwxrwxrwx\0";
            strcpy(addfil,filename);
            int lenad=strlen(addfil);
            addfil[lenad]='/';
            addfil[lenad+1]='\0';
            strcat(addfil,name);
            struct stat buff3;
            int sd = stat(addfil,&buff3);
            if(sd<0){
                perror("Error at stat");
                return;
            }
            if(S_ISREG(buff3.st_mode))
                perm[0]='-';
            else if(S_ISDIR(buff3.st_mode))
                perm[0]='d';
            else if(S_ISLNK(buff3.st_mode))
                perm[0]='l';
            else if(S_ISSOCK(buff3.st_mode))
                perm[0]='s';
            else if(S_ISBLK(buff3.st_mode))
                perm[0]='b';
            else if(S_ISFIFO(buff3.st_mode))
                perm[0]='p';
            else if(S_ISCHR(buff3.st_mode))
                perm[0]='c';
            long long int num= buff3.st_mode;
            for(int i=0;i<9;i++){
                if(num%2==0)
                    perm[9-i]='-';
                num=(num/2);
            }
            long int lin=buff3.st_nlink;
            struct passwd *ppointeru;
            ppointeru = getpwuid(buff3.st_uid);
            struct group *grp;
            grp = getgrgid(buff3.st_gid);
            char ti[10003];
            const time_t *t;
            t = &(buff3.st_atim.tv_sec);
            strcpy(ti,ctime(t));
            int le3 = strlen(ti);
            ti[le3-1]='\0';
            printf("%s  %ld  %s  %s  %s  %s\n",perm,lin,ppointeru->pw_name,grp->gr_name,ti,name);
        }
    }
}