//
// Created by Fabio on 24/11/2023.
//
#include "list.h"

#include <stdlib.h>
#include <stdbool.h>

typedef struct {
    char *nom;    // Nom dynamique
    char *prenom; // Prénom dynamique
    struct s_agenda_entry *rendezVousList;
} Contact;

typedef struct {
    int jour, mois, annee; // Date
    int heure, minute;     // Heure de début
    int dureeHeure, dureeMinute; // Durée
    char *objet;           // Objet du rendez-vous dynamique
    struct s_rendezvous *next;
} RendezVous;

typedef struct s_agenda_entry {
    Contact contact;
    struct s_agenda_entry *next; // Pour la liste chaînée
    RendezVous *rendezVousList;  // Liste de rendez-vous
    int totalRendezVous;         // Nombre total de rendez-vous
} AgendaEntry;

Contact *createContact(const char *nom, const char *prenom);
void freeContact(Contact *contact);

void toLowerStr(char *str);
Contact *scanString(void);

void add_contact_in_list(t_d_list *listeNiveaux);
void add_contact_and_tri(t_d_list *listeNiveaux, Contact *contact);
void add_contact_to_levels(t_d_list *listeNiveaux, Contact *contact);

void attribuerAgenda(Contact *contact, int jour, int mois, int annee, int heure, int minute, int dureeHeure, int dureeMinute, const char *objet);
void afficherAgenda(Contact *contact);

#ifndef AGENDA_AGENDA_H
#define AGENDA_AGENDA_H

#endif //AGENDA_AGENDA_H
