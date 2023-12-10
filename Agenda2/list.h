#include "cell.h"

typedef struct s_d_list
{
    int niv_max;
    t_d_cell **head;
} t_d_list;

struct s_d_list* creer_liste_niveaux(int niv_max_input);
void addHeadSortList(t_d_list * my_list ,t_d_cell * new_cell);
void print_cell_for_1_level(t_d_list *my_list, int level);
void print_cell_for_all_level(t_d_list *my_list);
void displayList(t_d_list *list);

t_d_list createListNiv(int n);

t_d_cell* searchInLevel0(t_d_list *my_list, int value);
t_d_cell* searchFromTopLevel(t_d_list *my_list, int value);

void print_contact_for_1_level(t_d_list *my_list, int level);

void print_contact_for_all_level(t_d_list *my_list);

#ifndef AGENDA_LIST_H
#define AGENDA_LIST_H

#endif //AGENDA_LIST_H
