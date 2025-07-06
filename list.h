#ifndef CFG_LIST_H
#define CFG_LIST_H

struct item{    //keeps list of avaliable displays
    struct item *next, *prev;
    char *data;
    int display_num;  //display number
    int conn_stat;      //0 - disconnect, 1 - connect
    int active_stat;
};

struct resol{  //keeps resolution for current display
  struct resol *next,*prev;
  char *data;
  int mode_num;
};

int list_free(struct item **f);
char *list_print(struct item *first);
int list_fill(struct item **first, struct item **last);
char *get_display_name(int c, struct item *item);
int primary_check(struct item *first,int d_num);
int display_modes_list_fill(char *d_name,struct resol **first, struct resol **last);
char *mode_list_print(struct resol *first);
int res_list_free(struct resol **f);

#endif