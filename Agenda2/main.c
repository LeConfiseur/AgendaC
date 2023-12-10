#include <stdio.h>
#include <stdlib.h>
#include "agenda.h"
#include "timer.h"
#include "math.h"


int main() {
    int choixPartie;

    do {
        printf("\nChoisissez la partie du projet à explorer:\n");
        printf("1. Partie 1 et 2 (Valeurs entières)\n");
        printf("2. Partie 3 (Caractères et Contacts)\n");
        printf("3. Note au correcteur\n ");
        printf("0. Quitter\n");

        printf("Entrez votre choix : ");
        scanf("%d", &choixPartie);

        int nombreNiveaux;
        printf("Entrez le nombre de niveaux : ");
        scanf("%d", &nombreNiveaux);

        switch (choixPartie) {
            case 1: {
                t_d_list *integerList = creer_liste_niveaux(nombreNiveaux);
                int choix;
                do {
                    printf("\nMenu pour les valeurs entières (Parties 1 et 2):\n");
                    printf("1. Ajouter une valeur\n");
                    printf("2. Afficher la liste des valeurs pour un niveau\n");
                    printf("3. Afficher la liste des valeurs pour tous les niveaux\n");
                    printf("4. Rechercher dans le niveau 0\n");
                    printf("5. Rechercher à partir du niveau le plus élevé\n");
                    printf("0. Quitter\n");

                    printf("Entrez votre choix : ");
                    scanf("%d", &choix);

                    switch (choix) {
                        case 1: {
                            int valeur, niveau;
                            printf("Entrez la valeur : ");
                            scanf("%d", &valeur);
                            printf("Entrez le niveau : ");
                            scanf("%d", &niveau);

                            if (niveau < 0 || niveau > nombreNiveaux) {
                                printf("Niveau invalide.\n");
                            } else {
                                t_d_cell *new_cell = create_cell(valeur, niveau);
                                addHeadSortList(integerList, new_cell);
                                printf("Valeur ajoutée avec succès au niveau %d.\n", niveau);
                            }
                            break;
                        }
                        case 2: {
                            int niveau;
                            printf("Entrez le niveau : ");
                            scanf("%d", &niveau);

                            if (niveau < 0 || niveau > nombreNiveaux) {
                                printf("Niveau invalide.\n");
                            } else {
                                printf("\nListe des valeurs pour le niveau %d :\n", niveau);
                                print_cell_for_1_level(integerList, niveau);
                            }
                            break;
                        }

                        case 3:
                            printf("\nListe des valeurs pour tous les niveaux:\n");
                            displayList(integerList);
                            break;
                        case 4: {
                            int valeur;
                            printf("Entrez la valeur à rechercher dans le niveau 0 : ");
                            scanf("%d", &valeur);
                            searchInLevel0(integerList, valeur);
                            break;
                        }
                        case 5: {
                            int valeur;
                            printf("Entrez la valeur à rechercher à partir du niveau le plus élevé : ");
                            scanf("%d", &valeur);
                            searchFromTopLevel(integerList, valeur);
                            break;
                        }
                        case 0:
                            printf("Au revoir!\n");
                            break;
                        default:
                            printf("Choix invalide. Veuillez réessayer.\n");
                    }
                } while (choix != 0);

                break;
            }
            case 2: {
                t_d_list *charList = creer_liste_niveaux(nombreNiveaux);
                int choix;
                do {
                    printf("\nMenu pour les caractères (Partie 3):\n");
                    printf("1. Ajouter un contact\n");
                    printf("2. Afficher la liste des contacts pour un niveau\n");
                    printf("3. Afficher la liste des contacts pour tous les niveaux\n");
                    printf("4. Attribuer un agenda à un contact\n");
                    printf("5. Afficher l'agenda d'un contact\n");
                    printf("0. Quitter\n");

                    printf("Entrez votre choix : ");
                    scanf("%d", &choix);

                    switch (choix) {
                        case 1: {
                            Contact *nouveauContact = scanString();
                            add_contact_and_tri(charList, nouveauContact);
                            printf("Contact ajouté avec succès.\n");
                            break;
                        }
                        case 2:
                            printf("\nListe des contacts par niveau:\n");
                            printf("Entrez le niveau : ");
                            int level;
                            scanf("%d", &level);
                            print_contact_for_1_level(charList, level);
                            break;
                        case 3:
                            printf("\nListe des contacts pour tous les niveaux:\n");
                            print_contact_for_all_level(charList);
                            break;
                        case 4: {
                            Contact *selectedContact = scanString();
                            int jour, mois, annee, heure, minute, dureeHeure, dureeMinute;
                            char objet[100];

                            printf("Entrez la date du rendez-vous (jour mois annee) : ");
                            scanf("%d %d %d", &jour, &mois, &annee);
                            printf("Entrez l'heure du rendez-vous (heure minute) : ");
                            scanf("%d %d", &heure, &minute);
                            printf("Entrez la durée du rendez-vous (heures minutes) : ");
                            scanf("%d %d", &dureeHeure, &dureeMinute);
                            printf("Entrez l'objet du rendez-vous : ");
                            scanf("%99s", objet);

                            attribuerAgenda(selectedContact, jour, mois, annee, heure, minute, dureeHeure, dureeMinute, objet);
                            break;
                        }
                        case 5: {
                            Contact *selectedContact = scanString();
                            afficherAgenda(selectedContact);
                            break;
                        }
                        case 0:
                            printf("Au revoir!\n");
                            break;
                        default:
                            printf("Choix invalide. Veuillez réessayer.\n");
                    }
                } while (choix != 0);

                break;

            }
            case 3:
                printf("3. Note au correcteur\n");
                printf("Nous n'avons pas pu aller au bout de ce projet. Le tri des contacts pour la partie 3 ne fonctionne qu'au niveau 0.\n");
                break;
            case 0:
                printf("Au revoir!\n");
                break;
            default:
                printf("Choix invalide. Veuillez réessayer.\n");
        }
    } while (choixPartie != 0);

    return 0;
}

//CODE A TESTER POUR CONNAITRE LA DIFFERENCE D'EFFICACITE ENTRE RESEARCH FROM LEVEL 0 ET RESEARCH FROM TOP LEVEL
/*
int num_searches[] = {1000,10000,100000};  // Changer les valeurs selon tes besoins

for (int i = 0; i < sizeof(num_searches) / sizeof(num_searches[0]); i++) {
t_d_list *my_list = creer_liste_niveaux(5);  // Changer le niveau maximal si nécessaire

for (int j = 0; j < num_searches[i]; j++) {
int value = j;
int niveaux = rand() % (my_list->niv_max + 1);
t_d_cell *new_cell = create_cell(value, niveaux);
addHeadSortList(my_list, new_cell);
}
// Mesure le temps pour la fonction searchInLevel0
startTimer();
for (int j = 0; j < num_searches[i]; j++) {
int search_value = rand() % num_searches[i];  // Valeur aléatoire à rechercher
searchInLevel0(my_list, search_value);
}
stopTimer();
printf("Temps pour searchInLevel0 avec %d recherches : %s\n", num_searches[i], getTimeAsString());

// Mesure le temps pour la fonction searchFromTopLevel
startTimer();
for (int j = 0; j < num_searches[i]; j++) {
int search_value = rand() % num_searches[i];  // Valeur aléatoire à rechercher
searchFromTopLevel(my_list, search_value);
}
stopTimer();
printf("Temps pour searchFromTopLevel avec %d recherches : %s\n", num_searches[i], getTimeAsString());

printf("\n");
}
return 0;
}
*/
