#include "dir.h"
#include "init.h"
#include "define.h"
#include "list.h"
#include "interface.h"
#include <sys/stat.h>

//Create a directory /home/[USER_ID]/.config/i3blocks/displayadd 
char *CreateDir(char *user_ID)
{
    char *path=ChangeStar(PATH_PART1,user_ID);
    mkdir(path,0755);
    char *path2=StringConnect(path,PATH_PART2);
    free(path);
    mkdir(path2,0755);
    return path2;
}

//connects two strings
char *StringConnect(char *str, char *str2)
{
    int l=1+strlen(str)+strlen(str2);

    char *result=malloc(l*sizeof(char));
    int i=0;
    int j=0;
    while(i<strlen(str)){
        result[i]=str[i];
        i++;
    }
    while(i<l){
        result[i]=str2[j];
        i++;
        j++;
    }
    result[i]='\0';
    return result;
}

//save last display config as default
int save_as_default(char *path, char *d_name,char *d_mode, 
                    char *d_pos, char *d_base)
{   
    if(read_number(1)){
        FILE *f=fopen(path,"w");
        if(!f){
            UI_CONF_FILE_ERROR 
            return 1;
        }
    fprintf(f,"%s\n%s\n%s\n%s\n",d_name,d_mode,d_pos,d_base);
    fclose(f);
    UI_CONF_FILE_SAVED
    printf(">%s\n\n",path);
    }
    return 0;
}