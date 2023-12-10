#include "list.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "math.h"

t_d_list* creer_liste_niveaux(int niv_max_input)
{
    t_d_list * new_list = (t_d_list *)malloc(sizeof(t_d_list));
    if (new_list != NULL) {
        new_list->niv_max = niv_max_input;
        new_list->head = (t_d_cell **) malloc(new_list->niv_max * sizeof(t_d_cell *));
        for (int i = 0; i < new_list->niv_max; i++) {
            new_list->head[i] = NULL;
        }
        return new_list;
    }
    return NULL;
}

void addHeadSortList(t_d_list *my_list, t_d_cell *new_cell) {
    if (new_cell->niveaux < 0 || new_cell->niveaux >= my_list->niv_max + 1) {
        printf("Niveau invalide\n");
        return;
    }
    for (int i = 0; i < new_cell->niveaux; i++) {
        if (my_list->head[i] == NULL || new_cell->value < my_list->head[i]->value) {
            // Si la liste est vide ou la nouvelle valeur est inférieure à la tête
            new_cell->next[i] = my_list->head[i];
            my_list->head[i] = new_cell;
        } else {
            t_d_cell *temp, *previous;
            temp = my_list->head[i];
            previous = NULL;

            while (temp != NULL && new_cell->value > temp->value) {
                previous = temp;
                temp = temp->next[i];
            }

            if (previous == NULL) {
                new_cell->next[i] = my_list->head[i];
                my_list->head[i] = new_cell;
            } else {
                previous->next[i] = new_cell;
                new_cell->next[i] = temp;
            }
        }
    }
}

void displayList(t_d_list *list) {
    t_d_cell *temp, *temp2;
    for (int i = 0; i < list->niv_max; i++) {
        temp = list->head[i];
        temp2 = list->head[0];
        printf("[list head %d @-]", i);
        while (temp != NULL) {
            while (temp->value != temp2->value) {
                if (temp2->value < 10) {
                    printf("----------");
                } else {
                    printf("-----------");
                }
                temp2 = temp2->next[0];
            }
            printf("-->[ %d|@-]", temp->value);
            temp = temp->next[1];
            temp2 = temp2->next[0];
        }
        while (temp2!=NULL && temp!=NULL){
            if(temp2->value<10){
                printf("----------");
            }
            else{
                printf("-----------");
            }
            temp2 = temp2->next[0];
        }
        printf("-->NULL\n");
    }
    printf("\n");
}

void print_cell_for_1_level(t_d_list *my_list, int level)
{
    if (level < 0 || level >= my_list->niv_max)
    {
        printf("Niveau Invalide %d invalide \n");
        return;
    }

    t_d_cell *temp = my_list->head[level];

    if ( my_list->head[level] == NULL)
    {
        printf("--> NULL");
    }

    while (temp != NULL)
    {
        printf("--> [ %d|@- ] ", temp->value);
        temp = temp->next[level];
    }
    printf("\n");
    return;
}

void print_cell_for_all_level(t_d_list *my_list)
{
    for (int i = 0; i < my_list->niv_max; i++)
    {
        printf("list head_%d @-] ", i);
        print_cell_for_1_level(my_list, i);
    }
}

void print_contact_for_1_level(t_d_list *my_list, int level) {
    if (level < 0 || level >= my_list->niv_max) {
        printf("Niveau invalide %d\n", level);
        return;
    }

    t_char_cell *temp = (t_char_cell *)my_list->head[level]; // Cast nécessaire si my_list->head est de type t_d_cell**

    if (temp == NULL) {
        printf("--> NULL\n");
        return;
    }

    while (temp != NULL) {
        printf("--> [ %s ] ", temp->name);
        temp = (t_char_cell *)temp->next[level]; // Cast nécessaire ici aussi
    }
    printf("\n");
}

void print_contact_for_all_level(t_d_list *my_list)
{
    for (int i = 0; i < my_list->niv_max; i++)
    {
        printf("list head_%d @-] ", i);
        print_contact_for_1_level(my_list, i);
    }
}

t_d_list createListNiv(int n)
{
    int number_cell, niveau;
    t_d_list  * list_niv;
    t_d_cell *new_cell;
    list_niv = creer_liste_niveaux(n);
    number_cell = (int)pow(2, n) -1;
    for (int i = 0; i < number_cell; i++)
    {
        niveau = 0;
        for (int j = 0; j<n ; j++)
        {
            if ((i+1)%(int)pow(2, j)==0)
            {
                niveau++;
            }
        }
        new_cell = create_cell(i+1, niveau);
        addHeadSortList(list_niv,new_cell);
    }
    return *list_niv;
}

t_d_cell* searchInLevel0(t_d_list *my_list, int value)
{
    if (my_list == NULL || my_list->head == NULL)
    {
        printf("Liste vide.\n");
        return NULL;
    }

    t_d_cell *current = my_list->head[0];

    while (current != NULL)
    {
        if (current->value == value)
        {
            printf("La valeur %d a été trouvée dans le niveau 0.\n", value);
            return current;
        }
        current = current->next[0];
    }

    printf("La valeur %d n'a pas été trouvée dans le niveau 0.\n", value);
    return NULL;
}

t_d_cell* searchFromTopLevel(t_d_list *my_list, int value)
{
    if (my_list == NULL || my_list->head == NULL)
    {
        printf("Liste vide.\n");
        return NULL;
    }
    int top_level = my_list->niv_max - 1;
    t_d_cell *current = my_list->head[top_level];
    t_d_cell *prev = NULL;
    while (top_level >= 0)
    {
        while (current != NULL && current->value < value)
        {
            prev = current;
            current = current->next[top_level];
        }
        if (current != NULL && current->value == value)
        {
            printf("La valeur %d a été trouvée à partir du niveau %d.\n", value, top_level);
            return current;
        }
        top_level--;
        if (prev != NULL && top_level >= 0 && prev->next[top_level] != NULL)
        {
            current = prev->next[top_level];
        }
        else if (top_level >= 0)
        {
            current = my_list->head[top_level];
        }
        prev = NULL;
    }
    printf("La valeur %d n'a pas été trouvée dans la liste.\n", value);
    return NULL;
}

