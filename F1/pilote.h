#ifndef PILOTES_H
#define PILOTES_H

#include <stdio.h>
#include <string.h>
#include "initialisation.h"


// Fonctions de gestion des pilotes 
void afficherPilotes(Pilote pilotes[], int nbPilotes);
void ajouterPilote(Pilote pilotes[], int *nbPilotes, int tailleMax, Ecurie ecuries[], int nbEcuries, Pays pays[], int *nbPays); // Ajout de tailleMax
void modifierPilote(Pilote pilotes[], int nbPilotes, int numero, int nouveauxPoints);
void supprimerPilote(Pilote pilotes[], int *nbPilotes, int numero);
void modifiertoutpilotes(Pilote pilotes[], int nbPilotes, int numero, char ecurie[]);
void echangerEcuriePilotes(Pilote *pilote1, Pilote *pilote2);
#endif