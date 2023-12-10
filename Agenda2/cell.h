//
// Created by Fabio  on 07/11/2023.
//

typedef struct s_d_cell
{
    int value;
    int niveaux;
    struct s_d_cell **next;
} t_d_cell;

typedef struct s_char_cell {
    char *name;
    int niveaux;
    struct s_char_cell **next;
} t_char_cell;

t_d_cell* create_cell(int valeur, int niveaux);

t_char_cell * create_cell_char(const char *valeur, int niveaux);

#ifndef AGENDA_CELL_H
#define AGENDA_CELL_H

#endif //AGENDA_CELL_H
