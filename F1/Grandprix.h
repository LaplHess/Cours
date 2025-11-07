#ifndef GRANDPRIX_H
#define GRANDPRIX_H

#include <stdio.h>
#include <string.h>
#include "initialisation.h"
#include "pilote.h"  // Pour la mise à jour des points des pilotes


void ajouterGrandPrix(GrandPrix grandsPrix[], int *nbGrandsPrix, int tailleMax);
void afficherGrandsPrix(GrandPrix grandsPrix[], int nbGrandsPrix);
int rechercherGrandPrix(GrandPrix grandsPrix[], int nbGrandsPrix, const char* nomCircuit);
void supprimerGrandPrix(GrandPrix grandsPrix[], int* nbGrandsPrix, const char* nomCircuit, Pilote pilotes[], int nbPilotes);
int calculerPoints(int position);

#endif
