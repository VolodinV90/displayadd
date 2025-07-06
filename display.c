#include "init.h"
#include "dir.h"
#include "define.h"
#include "list.h"
#include "interface.h"

///////here starts the main function//////
int main()
{   
    //this keeps display config parameter
    int  d_num; 
    char d_name[BUF];
    char d_mode[BUF];
    char d_pos[BUF];
    char d_base[BUF];
    //end

    char *user=UserName();//defines user name

    //creates dir+defines cfg file path and name
    char *path=StringConnect(CreateDir(user),CFG_FILE_NAME);
    free(user);

    UI_WELCOMESCREEN
    //sets up display's default start parameters.name,path,resolution,rate
    DisplaySetup(path,d_name,d_mode, d_pos,d_base); 
    startover:
    UI_STARTOVER_LINE //see in define.h

    //list of structs, that keeps all displays names and numbers,
    // which have been found in system
    struct item *display_first=NULL;
    struct item *display_last=NULL;
    list_fill(&display_first,&display_last);
    //end of a list

    UI_CHOOSE_DISPLAY1          //display choose, see in define.h
    list_print(display_first);  //Print a list of avaliable display
    UI_CHOOSE_DISPLAY2          //display choose, see in define.h
    use_default_config(d_name,d_mode,d_pos,d_base);

    //choose a display to setup
    d_num = int_choose_display(display_first,display_last);
    if(d_num==-1){
        return 1;
    }

    //warning if display is allready active
/*  if((d_num)&&(!allreday_active(display_first,d_num))){
    goto if_active;
    }
*/
    if (d_num){ //assign a displayname from the list to work with
        strcpy(d_name,get_display_name(d_num,display_first));  
        UI_DISPLAY_CHOSEN1
    }else{
        UI_DISPLAY_CHOSEN2
    }

    //defines a command to disconnect a display
    char *display_disconnect_cmd=ChangeStar(DISPLAY_DISCONNECT1,d_name);
    
    //a menu to activate-deactivate display. look in define.h
    UI_CHOOSE_ACTION 
    int act=read_number(1);

    //struct taht keeps avaliable resolution list for a chosen display
    struct resol *resol_first=NULL;
    struct resol *resol_last=NULL;

    //deactivate or activate display menu 
    switch(act){

        case 0:{ //if it is a need to DEACTIVATE a display
            if (primary_check(display_first,d_num)){
                UI_PRIMARY_DISPLAY //look in define.h
                break;
            }
            display_deactivate(display_disconnect_cmd,d_name);
            break;}

        case 1:{  //if it is a need to ACTIVATE a display
            if(!display_connect_check(d_name)){
                UI_DISPLAY_NOT_CONNECTED //look in define.h
                }else{
                    UI_SELECT_MODE //select display resolution, look in define.h
                    display_modes_list_fill(d_name,&resol_first,&resol_last);
                    mode_list_print(resol_first);
                    char *tmpmode=int_choose_mode(resol_first,resol_last);
                    if (tmpmode){
                      strcpy(d_mode,tmpmode);
                        free(tmpmode);
                    }

                    UI_SELECT_POSITION //select display position, look in define.h
                    char *tmppos=int_choose_pos();
                    if (tmppos){
                        strcpy(d_pos,tmppos);free(tmppos);
                    }

                    UI_OF_WHICH_DISPLAY //select of which display, look in define.h
                    char *tmpbase=ui_choose_base(display_first,display_last);
                    if (tmppos){
                        strcpy(d_base,tmpbase);free(tmpbase);
                    }
                    char *display_connect_cmd=
                            MakeCommand(DISPLAY_CONNECT1,d_name,d_mode,d_pos,d_base);
                    display_activate(display_connect_cmd,d_name,d_mode,d_pos,d_base);
                } 
            break;}
        default:{
            break;
        }
    }

    //saving last setup in a *.cfg file
    if (act){
        UI_SAVE_DEFAULT_CONFIG //see in define.h
        save_as_default(path,d_name,d_mode,d_pos,d_base);
        free(path);
    }

    //if_active:
    UI_STARTOVER //start the program again?
    act=read_number(1);
    if (act == 1){
        list_free(&display_first);
        res_list_free(&resol_first);
        goto startover;
    }else
        return 0;
    getchar();
    return 0;
} 