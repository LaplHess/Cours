#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Classement.h"





//classement d'une course
void classementCourse(GrandPrix grandsPrix[], int nbGrandsPrix, const char* nomCircuit)  
{
    int found = 0;
    for (int i = 0; i < nbGrandsPrix; i++) {
        if (strcmp(grandsPrix[i].nomCircuit, nomCircuit) == 0) {            //compare le nom du circuit 
            found = 1;
            printf("Classement pour le Grand Prix de %s :\n", nomCircuit);
            for (int j = 0; j < grandsPrix[i].nombreResultats; j++) {
                printf("Position %d: %s avec un temps de %s et avec %d points \n",
                    grandsPrix[i].resultats[j].position,
                    grandsPrix[i].resultats[j].nomPilote,
                    grandsPrix[i].resultats[j].tempsrealise,
                    grandsPrix[i].resultats[j].pointsobtenus);
            }
            break;//sort de la boucle une fois le grand prix trouve
        }
    }
    if (!found) {
        printf("Grand Prix avec le nom de circuit '%s' non trouve.\n", nomCircuit);
    }
}





/*----------------------------------------------------------------------------------------------------*/
void classementGeneralPilotes(Pilote pilotes[], int nbPilotes)
{
    // Tri par selection des pilotes par points 
    for (int i = 0; i < nbPilotes - 1; i++) {
        for (int j = i + 1; j < nbPilotes; j++) {
            if (pilotes[j].points > pilotes[i].points) {
                Pilote temp = pilotes[i];
                pilotes[i] = pilotes[j];
                pilotes[j] = temp;
            }
        }
    }

    printf("Classement general des pilotes :\n");
    for (int i = 0; i < nbPilotes; i++) {
        printf("Position %d: %s %s - %d points\n", i + 1, pilotes[i].prenom, pilotes[i].nom, pilotes[i].points);
    }
}


/*----------------------------------------------------------------------------------------------------*/

void classementGeneralConstructeurs(Ecurie ecuries[], int nbEcuries, Pilote pilotes[], int nbPilotes)
{
    // Calcul des points par ecurie
    for (int i = 0; i < nbEcuries; i++) {
        ecuries[i].points = 0; // Reinitialiser les points
        for (int j = 0; j < nbPilotes; j++) {
            if (strcmp(pilotes[j].Ecurie, ecuries[i].nom) == 0) {
                ecuries[i].points += pilotes[j].points;
            }
        }
    }

    // Tri par selection des ecuries par points 
    for (int i = 0; i < nbEcuries - 1; i++) {
        for (int j = i + 1; j < nbEcuries; j++) {
            if (ecuries[j].points > ecuries[i].points) {
                Ecurie temp = ecuries[i];
                ecuries[i] = ecuries[j];
                ecuries[j] = temp;
            }
        }
    }

    printf("Classement general des constructeurs :\n");
    for (int i = 0; i < nbEcuries; i++) {
        printf("Position %d: %s - %d points\n", i + 1, ecuries[i].nom, ecuries[i].points);
    }
}

/*----------------------------------------------------------------------------------------------------*/


