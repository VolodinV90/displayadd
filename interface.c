#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "define.h"
#include "init.h"

//read integer in given diapasone
int read_number(int num)
{
    int c,ch;
    while (1) {
        printf(" Your choice: ");
        int res = scanf("%d", &c);

        if (res == EOF) {  // ctrl+D or input closed
            printf("\n");
            exit(3);
            //return -1;
        }
        if (res == 0) {  // Invalid input, e.g. letters
            // Clear the line buffer
            while ((ch = getchar()) != '\n' && ch != EOF);
            printf(">Invalid input, enter a number (0 to %d):\n", num);
            continue;
        }

        // Valid int read
        while ((ch = getchar()) != '\n' && ch != EOF); // flush extra input

        if (c >= 0 && c <= num) {
            break; // correct value, exit loop
        } else {
            printf(">Wrong number, try again (1-%d, or 0):\n", num);
        }
    }
    return c;
}

//select display dialog, returns display number
int int_choose_display(struct item *first,struct item *last)
{
    int num = last->display_num;
    printf(">Type [1-%i] to select a display to setup,\n",num);
    printf(">or [0] for default setup:\n");
    int c=read_number(num);
    return c;
}

//Select display mode dialog. to choose display resolution
char *int_choose_mode(struct resol *first,struct resol *last)
{
    int num = last->mode_num;
    printf(">Type [1-%i] to select mode,\n",num);
    printf(">or [0] for default setup:\n");
    int c=read_number(num);
    if (c==0){
        return NULL;
    }
    struct resol *tmp;
    tmp=first;
    char *str=malloc(BUF*sizeof(char));
    while(tmp){
        if (tmp->mode_num==c){
            strcpy(str,tmp->data);
            return (str);
        }
        tmp=tmp->next;
    }
    return (str);
}

//select display position dialog(right,left,top,bot,same as)
char *int_choose_pos()
{
    char *str=malloc(10*sizeof(char));
    int c=read_number(5);
    switch(c){
        case 1:{ //left
            strcpy(str,"left-of");
            break;
        }
        case 2:{ //right
            strcpy(str,"right-of");
            break;
        }
        case 3:{ //top
            strcpy(str,"above");
            break;
        }
        case 4:{ //bot
            strcpy(str,"below");
            break;
        }
        case 5:{ //same as
            strcpy(str,"same-as");
            break;
        }
        default:
            break;
    }
    return(str);
}

//a dialog to select basic display
char *ui_choose_base(struct item *first,struct item *last)
{
    int c,check=0;
    int num;
    struct item *tmp=first;
    while(tmp){
        if ((tmp->conn_stat)&&(tmp->active_stat)){
            printf("%3i. %s\n",tmp->display_num,tmp->data);
            num=tmp->display_num;
        }
        tmp=tmp->next;
    }
    printf(">Type [1-%i] to select main display\n", num);
    char *str=malloc(BUF*sizeof(char));
    checkagain:
    c=read_number(num);
    if (c==-1){
        goto checkagain;
    }
    if (c==0){
        goto skip;
    }
    tmp=first;
    while(tmp){
        if ((tmp->display_num==c)&&(tmp->active_stat)){
            //printf("<%i>\n",tmp->display_num);
            strcpy(str,tmp->data);
            check = 1;
            return (str);
        }
        tmp=tmp->next; 
    }
    if(!check){
        skip:
        printf("\n>invalid display number, or display is not active\n");
        printf(">please repeat your input with a number from a given list\n");
        
        goto checkagain;
    }
    return NULL;
}

//check if display is physically connected
int display_connect_check(char *display_id)
{
    char *connect_check_cmd=ChangeStar(CONNECT_CHECK,display_id);
    FILE *f=NULL;
    char buf[BUF];

    //var for skipping the name of a display in buffer(display name length)
    int skip = strlen(display_id)+1;
    
    f=popen(connect_check_cmd,"r"); //parsing a command from terminal
    if (!f){
        pclose(f);
        return 0;
    }
    buf[0]='\0';
    for (int i=0;i<BUF;i++){     //filling buffer for command check true/false
        buf[i]=fgetc(f);         //now the buffer consists a grabbed command
    }
    if(buf[skip]!='c'){          //check if the DisplayPort-1 connected
        pclose(f); //if the first character after displayname not 'C', then error
        return 0;  
    }
    pclose(f);
    return 1;
}

//defines if you should use default display config from file 
//or choose custom settings
int use_default_config(char *name,char *mode, char *pos, char *base)
{
    printf("              name:[%s]\n",   name);
    printf("        resolution:[%s]\n",   mode);
    printf("          position:[%s"   ,   pos);
    printf(" of %s]\n\n", base);
    return 0;
}

//warning if the display allready active
//then will no changes taken
int allreday_active(struct item *tmp,int num)
{
    while(tmp){
        if(tmp->display_num==num){
            if(tmp->active_stat){
                printf("\n>warning: the display is allready active and setup\n");
                printf(">will not take effect. would you like to continue?\n");
                printf(">1-yes, 0-no\n");
                return read_number(1);
            }
        }
        tmp=tmp->next;
    }
    return 0;
}

