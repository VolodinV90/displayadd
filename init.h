#include <stdio.h>
#include <string.h>
#include <stdlib.h>

#ifndef CFG_FILL_H
#define CFG_FILL_H

int cfg_init(FILE *f,const char *cmd);
char *ChangeStar(char *base, char *insert); 
char *MakeCommand(char *base, char *dn,char *dm,char *dp,char *db);

int display_deactivate(char *comm,char *name);
int display_activate(char *comm,char *name, char *mode,char *pos,char *base);
char *UserName();
int DisplaySetup(char *cmd,char *name,char *mode, char *pos, char *base);

#endif

