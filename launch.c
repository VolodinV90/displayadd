#include <stdio.h>
#include <stdlib.h>
#include "define.h"
#include "init.h"
#include "dir.h"
#include "interface.h"

//Utility to launch a program in i3Blocks or similar manager
//calls a main program in xterm terminal
int main()
{
    printf("🖥️\n");
    char *user=UserName();
    char *path=ChangeStar(PATH_PART1,user);
    char *path2=StringConnect(path,PATH_PART2);
    free(path);
    char *path3=StringConnect(path2,PROGRAM_FILE_NAME);
    free(path2);
    char *launch_command=ChangeStar("i3-sensible-terminal -e '*'",path3);
    free(path3);
    system(launch_command);
    //system("i3-sensible-terminal -e '/home/vladimir/.config/i3blocks/displayadd/display'");
    return 0;
}