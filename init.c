#include <unistd.h>
#include <pwd.h>
#include "init.h"
#include "define.h"

char *UserName() 
{                                            // get currens system username
    uid_t uid = getuid();                    // get UID
    struct passwd *pw = getpwuid(uid);       // struct with user data

    if (pw) {
        char *buf=malloc(sizeof(pw->pw_name));
        int i=0;
        while(pw->pw_name[i]!='\0'){
            buf[i]=pw->pw_name[i];
            i++;
        }
        buf[i]='\0';
        return buf;
    } else {
        return NULL;;
    }
}

//initial display setup
int DisplaySetup(char *cmd,char *name,char *mode, char *pos, char *base)
{       
    char *str[MAX_LINES];
    create:
    FILE *f=fopen(cmd,"r");
    if(!f){
        recreate:
        cfg_init(f,cmd); //a function which creates and fills a new config fille. see init.h
        goto create;
    }

    char c;   //check if the file ok,if it exist, and go to recreate file if not
    int Sc=0;
    while((c=fgetc(f))!=EOF){
        if(c=='\n')
            Sc++;
    }
    if(Sc<4){ //there must be more then 4 strings in a config file!
        fclose(f);
        goto recreate;
    }
    rewind(f);

    char buf[BUF];
    int i = 0;
    
    while (fgets(buf, sizeof(buf),f) && i<MAX_LINES){  //filling the strings
        buf[strcspn(buf, "\n")] = '\0';
        str[i] = strdup(buf);
        i++;
    }
    fclose(f);

    strcpy(name, str[0]);
    strcpy(mode, str[1]);
    strcpy(pos, str[2]);
    strcpy(base, str[3]);
    return 0;
}

//configures config file if it does not exist
int cfg_init(FILE *f,const char *cmd)
{
    f=fopen(cmd,"w");
    if(!f){
        printf("some problem with a config file\n");
    }
    //fprintf(f,""DEF_DISPLAY_NAME"\n"DEF_DISPLAY_MODE"\n"DEF_DISPLAY_RATE"\n"DEF_DISPLAY_POS  "\n");
    fprintf(f,""DEF_DISPLAY_NAME"\n"
                DEF_DISPLAY_MODE"\n"
                DEF_DISPLAY_POS "\n"
                DEF_DISPLAY_BASIC"\n");
    fclose(f);
    return 0;
}

//this reads a '*' count in a string
int CountStars(char *str)
{
    int count=0;
    while (*str){
            if(*str=='*') count++;
        str++;
    }
    return count;
}

//this unction is used in a function MakeCommand.
//it changes a '*' in a string into another string
//Base is a base string, insert is a string which is inseted in a base string
char *ChangeStar(char *base, char *insert)
{  
    int l = strlen(base) + strlen(insert) + 1;
    char *result=malloc(l);
    int f=0;
    
    int i = 0, k = 0;

    while (base[i] != '\0') {
        if ((base[i] == '*')&&(!f)) {
            int m = 0;
            f=1;
            while (insert[m] != '\0') {
                result[k++] = insert[m++];
            }
            i++;  
        } else {
            result[k++] = base[i++];
        }
    }
    
    result[k] = '\0';  
    return result;
}

//makes a command if a string has up to 4 '*' symbols
char *MakeCommand(char *base, char *dn,char *dm,/* char *dr,*/char *dp,char *db)
{
    char *d1=ChangeStar(base, dn);
    char *d2=ChangeStar(d1, dm);free(d1);
    char *d3=ChangeStar(d2, dp);free(d2);
    /**/char *d4=ChangeStar(d3, db);free(d3);
    return d4;
}


int display_deactivate(char *comm,char *name)
{
    system(comm);
    printf(" 🔴 Deactivated:🖥️ [%s]\n\n",name);
    return 0;
}

int display_activate(char *comm,char *name, char *mode,char *pos,char *base)
{
    system(comm);
    printf(" 🟢 Activated:🖥️ [%s,%s,%s %s]\n\n",name,mode,pos,base);
    return 0;
}