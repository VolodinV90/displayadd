#include <stdio.h>
#include <stdlib.h>

#define BUF 50 //text buffer size

//default display parameters if not defined
#define DEF_DISPLAY_NAME    "DisplayPort-1" //name of a monitor
#define DEF_DISPLAY_MODE    "1920x1080"     //display mode
//#define DEF_DISPLAY_RATE  "60"            //display rate
#define DEF_DISPLAY_POS     "above"         //above,below,left-of,right-of,same-as
#define DEF_DISPLAY_BASIC   "eDP"           //from which display the position must be taken
//end default dispalay parameters

//screen config file,
//full path is "/home/[user_ID]/.config/i3blocks/displayadd/display.cfg"
#define PATH_PART1  "/home/*/.config"//i3blocks"
//#define PATH_PART1  "/home/*/.config"
#define PATH_PART2  "/displayadd"
#define CFG_FILE_NAME "/display.cfg"
#define PROGRAM_FILE_NAME "/display"
#define MAX_LINES 4 //lines count in setup fie

//xrandr commands
#define CONNECT_CHECK "xrandr | grep '* connected'"
#define CONNECT_ERR "external display is not connected, try another name or check hardware"
#define CONNECT_OK "external display is OK"

#define DISPLAY_DISCONNECT1 "xrandr --output * --off"
#define DISPLAY_CONNECT1 "xrandr --output * --mode * --* *"
//#define DISPLAY_CONNECT1 "xrandr --output * --mode * --rate * --* eDP"

//ui messages in main program
#define UI_STARTOVER_LINE \
    printf("__________________________________________________________\n");

#define UI_CHOOSE_DISPLAY1 \
    printf("\n>Choose a display to setup:\n");
#define UI_CHOOSE_DISPLAY2 \
    printf("\n  0.  or use a default display setup:\n");

#define UI_DISPLAY_CHOSEN1 \
    printf("\n>Display nr [%i], [%s] has been chosen:\n",d_num,d_name);
#define UI_DISPLAY_CHOSEN2 \
    printf(">Default setup has been chosen,\n");

#define UI_CHOOSE_ACTION \
    printf(">choose your action:\n"); \
    printf("  0 -deactivate display(don't use to display a picture)\n"); \
    printf("  1 -  activate display(......use to display a picture)\n");

#define UI_PRIMARY_DISPLAY \
    printf(">unable to deactivate primary display\n\n");\

#define UI_DISPLAY_NOT_CONNECTED \
    printf(">the display is not physically connected, can not activate\n");\
    printf(">please connect a display first, and start over.\n\n");

#define UI_SELECT_MODE \
    printf("\n>select display mode:\n");

#define UI_SELECT_POSITION \
    printf("\n>select display position:\n"); \
    printf(">1-left, 2-right, 3-above, 4-below, 5-duplicate display\n");

#define UI_OF_WHICH_DISPLAY \
    printf("\n>of which from active displays:\n");

#define UI_SAVE_DEFAULT_CONFIG \
    printf("\n>save config as default?\n"); \
    printf(">1-yes, 0-no\n");

#define UI_STARTOVER \
    printf(">start over?(1-yes,0-no)\n");


//ui messages in main dir.c
#define UI_CONF_FILE_ERROR \
    printf(">error opening config file\n");

#define UI_CONF_FILE_SAVED \
    printf(">config has been saved to:\n");


//This is a welcome screen for the main program:
#define UI_WELCOMESCREEN \
    printf("Displayadd v1.0\n"); \
    printf("Author: Vladimir Volodin, 2025\n"); \
    printf("https://github.com/VolodinV90") \
    printf("This software is licensed under the MIT License.\n\n"); \
    printf("Description:\n\
A utility for managing additional displays in X11 environments. \
Enables connecting and disconnecting monitors, adjusting their placement relative \
to each other and the primary display (e.g., left-of, right-of, above, below), \
and configuring resolution.\n\n"); \
    printf("Controls:\n"); \
    printf("Just fllow the instructions on the screen,\npress CTRL+d to exit\n");
    //printf("\n");

