
#ifndef CFG_INTERFACE_H
#define CFG_INTERFACE_H

 int int_choose_display(struct item *first,struct item *last);
 int display_connect_check(char *display_id);
 int use_default_config(char *name,char *res, char *pos, char *base);  
char *int_choose_mode(struct resol *first,struct resol *last);
 int read_number(int num);
char *int_choose_pos();
char *ui_choose_base(struct item *first,struct item *last);
 int allreday_active(struct item *tmp,int num);

#endif