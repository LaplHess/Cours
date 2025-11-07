#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "pilote.h"
#include "Ecurie.h"
#include "Grandprix.h"
#include "Classement.h"
#include "initialisation.h" 

#define MAX_PILOTES 10
#define MAX_ECURIES 20
#define MAX_GP 30
#define MAX_PAYS 25 

Pilote pilotes[MAX_PILOTES];
Ecurie ecuries[MAX_ECURIES];
GrandPrix grandsPrix[MAX_GP];
Pays pays[MAX_PAYS]; 
int nbPilotes = 0, nbEcuries = 0, nbGrandsPrix = 0, nbPays = 0;  


// Fonction pour lire un entier de maniere sure pour qu il y ait une condition de sortie dans les menus
int lireEntier(const char *invite)
{
    char buf[128];
    int val;
    while (1) {
        printf("%s", invite);
        if (!fgets(buf, sizeof(buf), stdin)) return 0;
        if (sscanf(buf, "%d", &val) == 1) return val;
        printf("Saisie invalide, reessayer.\n");
    }
}
// Menu pour la gestion des Pilotes
void menuPilotes(void)
{
    int choix;
    do {
        printf("\n--- Gestion Pilotes ---\n");
        printf("1. Ajouter pilote\n2. Modifier pilote\n3. Supprimer pilote\n4. Afficher pilotes\n0. Retour\n");
        choix = lireEntier("Choix: ");
        switch (choix) {
            case 1:
                ajouterPilote(pilotes, &nbPilotes, MAX_PILOTES, ecuries, nbEcuries, pays, &nbPays);
                break;
            case 2: {
                int numero = lireEntier("Entrez le numero du pilote a modifier: ");
                int nouveauxPoints = lireEntier("Entrez les nouveaux points: ");
                modifierPilote(pilotes, nbPilotes, numero, nouveauxPoints);
                break;
            }
            case 3: {
                int numero = lireEntier("Entrez le numero du pilote a supprimer: ");
                supprimerPilote(pilotes, &nbPilotes, numero);
                break;
            }
            case 4:
                afficherPilotes(pilotes, nbPilotes);
                break;
            case 0: break;
            default: printf("Option invalide.\n"); break;
        }
    } while (choix != 0);
}
// Menu pour la gestion des Ecuries
void menuEcuries(void)
{
    int choix;
    do {
        printf("\n--- Gestion Ecuries ---\n");
        printf("1. Ajouter ecurie\n2. Supprimer ecurie\n3. Afficher ecuries\n0. Retour\n");
        choix = lireEntier("Choix: ");
        switch (choix) {
            case 1:
                ajouterEcurie(ecuries, &nbEcuries, MAX_ECURIES, pays, &nbPays);
                break;
            case 2: {
                char nom[100];
                printf("Entrez le nom de l'ecurie a supprimer: ");
                if (fgets(nom, sizeof(nom), stdin)) {
                    nom[strcspn(nom, "\n")] = 0;
                    supprimerEcurie(ecuries, &nbEcuries, nom, pilotes, nbPilotes);
                }
                break;
            }
            case 3:
                afficherEcuries(ecuries, nbEcuries);
                break;
            case 0: break;
            default: printf("Option invalide.\n"); break;
        }
    } while (choix != 0);
}
// Menu pour la gestion des Grands Prix
void menuGrandsPrix(void)
{
    int choix;
    do {
        printf("\n--- Gestion Grands Prix ---\n");
        printf("1. Ajouter Grand Prix\n2. Mettre a jour Grand Prix\n3. Supprimer Grand Prix\n4. Afficher Grands Prix\n0. Retour\n");
        choix = lireEntier("Choix: ");
        switch (choix) {
            case 1:
                ajouterGrandPrix(grandsPrix, &nbGrandsPrix, MAX_GP);
                break;
            case 2: {
                int gpIndex = lireEntier("Choisissez le numero du GP a mettre a jour (1..): ");
                if (gpIndex >= 1 && gpIndex <= nbGrandsPrix) {
                    majgp(&grandsPrix[gpIndex-1], pilotes, nbPilotes);
                } else {
                    printf("Index invalide.\n");
                }
                break;
            }
            case 3: {
                char nom[128];
                printf("Entrez le nom du circuit a supprimer: ");
                if (fgets(nom, sizeof(nom), stdin)) {
                    nom[strcspn(nom, "\n")] = 0;
                    supprimerGrandPrix(grandsPrix, &nbGrandsPrix, nom, pilotes, nbPilotes);
                }
                break;
            }
            case 4:
                afficherGrandsPrix(grandsPrix, nbGrandsPrix);
                break;
            case 0: break;
            default: printf("Option invalide.\n"); break;
        }
    } while (choix != 0);
}
// Menu pour les classements
void menuClassements(void)
{
    int choix;
    do {
        printf("\n--- Classements ---\n");
        printf("1. Classement d'une course\n2. Classement pilotes\n3. Classement constructeurs\n0. Retour\n");
        choix = lireEntier("Choix: ");
        switch (choix) {
            case 1: {
                char nomCircuit[128];
                printf("Entrez le nom du circuit: ");
                if (fgets(nomCircuit, sizeof(nomCircuit), stdin)) {
                    nomCircuit[strcspn(nomCircuit, "\n")] = 0;
                    classementCourse(grandsPrix, nbGrandsPrix, nomCircuit);
                }
                break;
            }
            case 2:
                classementGeneralPilotes(pilotes, nbPilotes);
                break;
            case 3:
                classementGeneralConstructeurs(ecuries, nbEcuries, pilotes, nbPilotes);
                break;
            case 0: break;
            default: printf("Option invalide.\n"); break;
        }
    } while (choix != 0);
}

// Main pour initialiser les donnees et lancer le menu principal
int main()
{
    initialiserDonnees(pilotes, &nbPilotes, ecuries, &nbEcuries, grandsPrix, &nbGrandsPrix, pays, &nbPays);

    int choix;
    do {
        printf("\n=== Menu principal ===\n");
        printf("1. Gestion Pilotes\n");
        printf("2. Gestion Ecuries\n");
        printf("3. Gestion Grands Prix\n");
        printf("4. Classements\n");
        printf("0. Quitter\n");
        choix = lireEntier("Choix: ");

        switch (choix) {
            case 1: menuPilotes(); break;
            case 2: menuEcuries(); break;
            case 3: menuGrandsPrix(); break;
            case 4: menuClassements(); break;
            case 0: printf("Au revoir.\n"); break;
            default: printf("Option invalide.\n"); break;
        }
    } while (choix != 0);

    return 0;
}