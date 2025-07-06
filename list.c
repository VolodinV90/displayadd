/*this modul works with datalists for a project*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "list.h"
#include "interface.h"
#include "init.h"
#include "define.h"

//struct item{}; look in list.h

//struct resol{}; look in list.h

//add an element to the list of avaliable resolution for a current display
struct resol *mode_list_push(struct resol **f, struct resol **l,int n,char *str)
{
    struct resol *first=*f;
    struct resol *last=*l;
    struct resol *tmp;

    tmp=malloc(sizeof(struct resol));
    tmp->data=malloc(BUF);
    int i=0;
    while(str[i]!='\0'){
        tmp->data[i]=str[i];
        i++;
    }
    tmp->mode_num = n;
    
    tmp->next=NULL;
    tmp->prev=NULL;
    strcpy(tmp->data,str);

    if (!first){
        first=tmp;
        last=first;
    }else{
        tmp->prev=last;
        last->next=tmp;
        last=tmp;
    }
    *f=first;
    *l=last;

    struct resol *cur;
    cur=*l;
    return cur;
}

//add an element to the list of avalable displays
struct item *list_push(struct item **f, struct item **l,int n,char *str,
                        int conn_status,int active_status)
{
    struct item *first=*f;
    struct item *last=*l;
    struct item *tmp;

    tmp=malloc(sizeof(struct item));
    tmp->data=malloc(BUF);
    int i=0;
    while(str[i]!='\0'){
        tmp->data[i]=str[i];
        i++;
    }
    tmp->display_num = n;
    tmp->conn_stat = conn_status;
    tmp->active_stat = active_status;

    tmp->next=NULL;
    tmp->prev=NULL;
    strcpy(tmp->data,str);

    if (!first){
        first=tmp;
        last=first;
    }else{
        tmp->prev=last;
        last->next=tmp;
        last=tmp;
    }
    *f=first;
    *l=last;

    struct item *cur;
    cur=*l;
    return cur;
}

//free display list. used in the end of a program
int list_free(struct item **f)
{
    struct item *first=*f;
    struct item *tmp;
    
    if(!first){
        return 0;
    }

    tmp=first;
    while(tmp){
        first=first->next;
        free(tmp);
        if (!first){
            tmp=NULL;
        }
        tmp=first;
    }
    return 0;
}


//free display resolution list. used in the end of a program
int res_list_free(struct resol **f)
{
    struct resol *first=*f;
    struct resol *tmp;
    
    if(!first){
        return 0;
    }

    tmp=first;
    while(tmp){
        first=first->next;
        free(tmp);
        if (!first){
            tmp=NULL;
        }
        tmp=first;
    }
    return 0;
}

//this prints a whole list of avaliable displays
char *list_print(struct item *first) 
{
    struct item *tmp;
    tmp=first;
    int l=0;
    while(tmp){ //defines a longest name length
        int lt=strlen(tmp->data);
        if(lt>l)
            l=lt;
        tmp=tmp->next;
    }

    tmp=first;
    printf(" ID.  NAME"); //head
            for(int i=0;(i<l);i++){
            printf(" ");
        }
    printf("STATUS\n");

    while(tmp){    //list
        int lt=strlen(tmp->data);
        printf("%3i.  ",tmp->display_num);
        printf("%s ",tmp->data);
        for(int i=0;(i<3+l-lt);i++){
            printf(".");
        }
        if (tmp->conn_stat){
            printf("...connected,");
        }else{
            printf("disconnected,");
        }

        switch(tmp->active_stat){
            case 0:{
                printf("unacive\n");
                break;}
            case 1:{
                printf("acive\n");
                break;}
            case 2:{
                printf("primary\n");
                break;}
        
        }
        //printf("\n");
        tmp=tmp->next;
    }
    return 0;
}

//this prints a whole list of aaliable resolutions for a current display
char *mode_list_print(struct resol *first) 
{
    struct resol *tmp;
    tmp=first;

    while(tmp){    //list
        printf("%3i.%s\n",tmp->mode_num,tmp->data);
        tmp=tmp->next;
    }
    return 0;
}

//add a new char to the string
char *get_string(char **s,char c,int i){
    char *str=*s;
    str[i]= c;
    *s=str;
    return str;
}

//check and remember if display active in system or not
//0-not active, 1- ative, 2- primary;
int check_active_status(char *d_name) 
{   
    char *str="xrandr --verbose | grep *";
    char *comm=ChangeStar(str, d_name);
    FILE *f=popen(comm,"r");
    int spc=0; //count spaces in the string
    char c;
    int res =0;
    while ((c=fgetc(f))!=EOF){
        if (c==' '){
            spc++;
        }
        if (spc==2){
            if (c=='p'){
                pclose(f);
                return 2;
            }
            if ((c>='0')&&(c<='9')){
                res = 1;
            }else{
                res = 0;
            }
        }
    }
    pclose(f);
    return res;
}

//this fills a list with displayname values
int list_fill(struct item **first, struct item **last)
{
    char c,c_last;
    int name_read=0;            //check if programm should red a name of a display
    char *str=malloc(BUF);      //display name
    int i=0;                    //symbol counter in a name
    int display_num=0;          //display number
    int conn_status=0;          //display connect status
    int active_status=0;        //display active in system status

    FILE *f=popen("xrandr","r");        //grabbing a command from terminal
    if (!f){
        printf("error getting ""xrandr""");
        return 0;
    }
    while((c=fgetc(f))!=EOF){       //filters displays name out of xrandr command
        if(c_last == '\n' && c != ' ' && c != '\n'){//only if not space after \n
            name_read = 1;
            display_num++;                          //defines display number
        } else if (name_read && c == ' ') {         // defines the end of a name
            get_string(&str,'\0',i);                //finishes a string with '\0'
            i=0;
            conn_status=display_connect_check(str);
            active_status=check_active_status(str);
            //push a name to the list:
            list_push(&(*first),&(*last),display_num,str,conn_status,active_status);
            name_read = 0;
        } 
        if(name_read){                       //push a new symbol to display name
            get_string(&str,c,i);
            i++;
        }
        c_last = c;
    }
    pclose(f);
    return 0;
}

//fill a list of avaliable display resolution modes
int display_modes_list_fill(char *d_name,struct resol **first, struct resol **last)
{
    char *str="xrandr | grep -A30 *";
    char *comm=ChangeStar(str,d_name);
    char c,c_last;
    int i=0,first_string=1,j=0,read=0,z=0;
    char buf[BUF];
    FILE *f=popen(comm,"r");
    while((c=fgetc(f))!=EOF){
        if((c_last=='\n')&&(!first_string)&&(c!=' ')){
            break;
        }
        if(c_last=='\n'){
            first_string=0;
            z=0;
        }
        if((c==' ')&&(c_last<='9')&&(c_last>='0')){
            read=0;
        }

        if((c!=' ')&&(!first_string)&&(j<BUF)&&(read)){
            buf[j]=c;
            j++;
        }
          if (c_last=='\n'){
            read=1;
        }

        if((c_last>='0')&&(c_last<='9')&&(c==' ')&&(z==0)&&(!first_string)){
            //goto the next element
            z=1;
            buf[j]='\0';
            mode_list_push(&(*first),&(*last),i,buf);
            j=0;
        }
        if(c=='\n'){
            i++;
        }
        c_last=c;
    }
    free(comm);
    pclose(f);
    return 0;
}

//gets a display name from list based on its number
char *get_display_name(int c, struct item *item)
{
    struct item *temp = item;
    while(temp){
        if (temp->display_num==c){
            return temp->data;
        }
        temp=temp->next;
    }
    return NULL;
}

//check if selected monitor primary or not
int primary_check(struct item *first,int c){
    struct item *tmp=first;    
    while(tmp){
        if (tmp->display_num==c){
            if (tmp->active_stat==2){
                return 1;
            }
        }
        tmp=tmp->next;
    }
    return 0;
}