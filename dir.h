#ifndef CFG_DIR_H
#define CGF_DIR_H

char *CreateDir(char *user_ID);
char *StringConnect(char *str, char *str2);
int save_as_default(char *path, char *d_name,
                    char *d_mode, char *d_pos, char *d_base);

#endif