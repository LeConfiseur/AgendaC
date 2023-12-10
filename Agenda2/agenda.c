#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdbool.h>
#include <ctype.h>
#include "agenda.h"

#define MAX_NAME_LENGTH 100

Contact *createContact(const char *nom, const char *prenom) {
    Contact *newContact = (Contact *)malloc(sizeof(Contact));
    if (newContact == NULL) {
        return NULL; // Échec de l'allocation
    }

    newContact->nom = strdup(nom); // Allocation et copie du nom
    newContact->prenom = strdup(prenom); // Allocation et copie du prénom

    if (newContact->nom == NULL || newContact->prenom == NULL) {
        free(newContact->nom);    // Libération en cas d'échec
        free(newContact->prenom); // Libération en cas d'échec
        free(newContact);
        return NULL;
    }

    return newContact;
}

void freeContact(Contact *contact) {
    if (contact != NULL) {
        free(contact->nom);
        free(contact->prenom);
        free(contact);
    }
}

void toLowerStr(char *str) {
    for (int i = 0; str[i]; i++) {
        str[i] = tolower(str[i]);
    }
}

Contact *scanString(void) {
    char nom[100], prenom[100];
    printf("Entrez le prénom : ");
    scanf("%99s", prenom);
    printf("Entrez le nom : ");
    scanf("%99s", nom);

    // Conversion en minuscules
    toLowerStr(nom);
    toLowerStr(prenom);

    // Création de la chaîne "nom_prenom"
    char *nomPrenom = (char *)malloc(strlen(nom) + strlen(prenom) + 2); // +2 pour le '_' et le caractère nul
    if (nomPrenom == NULL) {
        return NULL; // Échec de l'allocation
    }
    sprintf(nomPrenom, "%s_%s", nom, prenom);

    // Création du contact
    Contact *contact = createContact(nomPrenom, "");
    free(nomPrenom); // Libération de la mémoire temporaire
    return contact;
}


// Fonction pour ajouter un contact à la liste à niveaux

/*
void add_contact_in_list(t_d_list *listeNiveaux) {
    if (listeNiveaux == NULL) {
        return;
    }

    Contact *C1 = scanString();

    // Créer la chaîne "nom_prenom" pour le contact
    char nomPrenom[MAX_NAME_LENGTH * 2];
    snprintf(nomPrenom, sizeof(nomPrenom), "%s_%s", C1->nom, C1->prenom);

    // Ajouter le contact à la liste à niveaux
    t_d_cell *new_cell = create_cell_char(nomPrenom, 4); // 4 niveaux comme exemple

    // Libérer la mémoire des noms saisis
    freeContact(C1); // Utiliser freeContact pour libérer proprement le contact
}
*/
void add_contact_and_tri(t_d_list *listeNiveaux, Contact *contact) {
    if (listeNiveaux == NULL || contact == NULL) {
        return;
    }

    // Créer la chaîne "nom_prenom" pour le contact
    char nomPrenom[MAX_NAME_LENGTH * 2];
    snprintf(nomPrenom, sizeof(nomPrenom), "%s_%s", contact->nom, contact->prenom);

    // Créer un nouveau nœud pour le contact
    t_char_cell *new_cell = create_cell_char(nomPrenom, 1); // 1 niveau pour le niveau 0

    // Si la liste est vide, ajoutez simplement le nouveau nœud
    if (listeNiveaux->head[0] == NULL) {
        listeNiveaux->head[0] = new_cell;
    } else {
        // Sinon, insérez le nœud trié
        t_char_cell *current = listeNiveaux->head[0];
        t_char_cell *previous = NULL;

        while (current != NULL && strcmp(current->name, nomPrenom) < 0) {
            previous = current;
            current = current->next[0];
        }

        new_cell->next[0] = current;

        if (previous == NULL) {
            listeNiveaux->head[0] = new_cell;
        } else {
            previous->next[0] = new_cell;
        }
    }
}

void attribuerAgenda(Contact *contact, int jour, int mois, int annee, int heure, int minute, int dureeHeure, int dureeMinute, const char *objet) {
    if (contact == NULL) {
        printf("Contact invalide.\n");
        return;
    }

    // Créer un rendez-vous
    RendezVous *nouveauRdv = (RendezVous *)malloc(sizeof(RendezVous));
    if (nouveauRdv == NULL) {
        printf("Échec de l'allocation pour le rendez-vous.\n");
        return;
    }

    // Attribuer les valeurs au rendez-vous
    nouveauRdv->jour = jour;
    nouveauRdv->mois = mois;
    nouveauRdv->annee = annee;
    nouveauRdv->heure = heure;
    nouveauRdv->minute = minute;
    nouveauRdv->dureeHeure = dureeHeure;
    nouveauRdv->dureeMinute = dureeMinute;
    nouveauRdv->objet = strdup(objet);

    // Ajouter le rendez-vous à la liste du contact
    AgendaEntry *nouvelleEntree = (AgendaEntry *)malloc(sizeof(AgendaEntry));
    if (nouvelleEntree == NULL) {
        printf("Échec de l'allocation pour l'entrée de l'agenda.\n");
        free(nouveauRdv->objet);
        free(nouveauRdv);
        return;
    }

    nouvelleEntree->contact = *contact;
    nouvelleEntree->rendezVousList = nouveauRdv;
    nouvelleEntree->totalRendezVous = 1;
    nouvelleEntree->next = NULL;

    // Ajouter l'entrée de l'agenda à la liste du contact
    // Ajoute ici le code nécessaire pour gérer la liste des entrées de l'agenda du contact

    printf("Agenda attribué avec succès au contact %s %s.\n", contact->prenom, contact->nom);
}

void afficherAgenda(Contact *contact) {
    if (contact == NULL) {
        printf("Contact invalide.\n");
        return;
    }

    printf("Agenda de %s_%s :\n", contact->prenom, contact->nom);

    if (contact->rendezVousList == NULL) {
        printf("Aucun rendez-vous.\n");
        return;
    }

    RendezVous *currentRdv = contact->rendezVousList;
    int count = 1;

    while (currentRdv != NULL) {
        printf("\nRendez-vous %d:\n", count++);
        printf("Date: %02d/%02d/%04d\n", currentRdv->jour, currentRdv->mois, currentRdv->annee);
        printf("Heure: %02d:%02d\n", currentRdv->heure, currentRdv->minute);
        printf("Durée: %02d:%02d\n", currentRdv->dureeHeure, currentRdv->dureeMinute);
        printf("Objet: %s\n", currentRdv->objet);

        currentRdv = currentRdv->next;
    }
}




