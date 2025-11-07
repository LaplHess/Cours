#ifndef ECURIE_H
#define ECURIE_H

#include <stdio.h>
#include <string.h>
#include "initialisation.h"

// Fonctions de gestion des ecuries
void afficherEcuries(Ecurie ecuries[], int nbEcuries);
void ajouterEcurie(Ecurie ecuries[], int *nbEcuries, int tailleMax, Pays pays[], int *nbPays);
int rechercherEcurie(Ecurie ecuries[], int nbEcuries, const char *nom);
// supprime une ecurie et détache les pilotes associes (met leur champ Ecurie à vide)
void supprimerEcurie(Ecurie ecuries[], int* nbEcuries, const char* nomEcurie, Pilote pilotes[], int nbPilotes);
// met à jour les points des écuries en sommant les points des pilotes affilies
void mettreAJourPointsEcuries(Ecurie ecuries[], int nbEcuries, Pilote pilotes[], int nbPilotes);

#endif // ECURIE_H
