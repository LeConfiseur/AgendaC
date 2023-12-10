#include "cell.h"
#include <stdlib.h>
#include <stdlib.h>
#include <stdio.h>
#include <string.h>

t_d_cell * create_cell(int valeur, int niveaux) {
    t_d_cell * new_cell = (t_d_cell *)malloc(sizeof(t_d_cell));
    if (new_cell != NULL) {
        new_cell->value = valeur;
        new_cell->niveaux = niveaux;
        new_cell->next = (t_d_cell**) malloc(niveaux * sizeof(t_d_cell*));

        // Initialize next pointers to NULL
        for (int i = 0; i < niveaux; i++) {
            new_cell->next[i] = NULL;
        }
    }
    return new_cell;
}

t_char_cell * create_cell_char(const char *valeur, int niveaux) {
    t_char_cell * new_cell = (t_d_cell *)malloc(sizeof(t_d_cell));
    if (new_cell != NULL) {
        new_cell->name = strdup(valeur); // Copier la chaîne de caractères
        new_cell->niveaux = niveaux;
        new_cell->next = (t_d_cell**) malloc(niveaux * sizeof(t_d_cell*));

        for (int i = 0; i < niveaux; i++) {
            new_cell->next[i] = NULL;
        }
    }
    return new_cell;
}





