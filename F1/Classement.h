#ifndef CLASSEMENT_H
#define CLASSEMENT_H

#include <stdio.h>
#include <string.h>
#include "initialisation.h"  

void classementCourse(GrandPrix grandsPrix[], int nbGrandsPrix, const char* nomCircuit);  // Capital C
void classementGeneralPilotes(Pilote pilotes[], int nbPilotes);
void classementGeneralConstructeurs(Ecurie ecuries[], int nbEcuries, Pilote pilotes[], int nbPilotes);
#endif