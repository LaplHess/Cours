#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Grandprix.h"
/*les do whiles permettent de verifier les conditions de l ennonces qui repetent de facon continu qui s arettent grace au break*/
// Bareme de points 
int calculerPoints(int position) {
    switch(position) {
        case 1: return 25;
        case 2: return 18;
        case 3: return 15;
        case 4: return 12;
        case 5: return 10;
        case 6: return 8;
        case 7: return 6;
        case 8: return 4;
        case 9: return 2;
        case 10: return 1;
        default: return 0;
    }
}



void ajouterGrandPrix(GrandPrix grandsPrix[], int *nbGrandsPrix, int tailleMax)
{
    if (*nbGrandsPrix >= tailleMax) {
        printf("Impossible d'ajouter un Grand Prix : calendrier complet.\n");
        return;
    }

    GrandPrix nouveauGP;
    char stock[128];

    // Nom du circuit
    printf("Entrez le nom du circuit : ");
    if (fgets(nouveauGP.nomCircuit, sizeof(nouveauGP.nomCircuit), stdin) != NULL)   //si fgets ne renvoie pas NULL alors on continue
        nouveauGP.nomCircuit[strcspn(nouveauGP.nomCircuit, "\n")] = 0;      //strcspn pour remplacer le \n par \0

    // Pays
    printf("Entrez le pays : ");
    if (fgets(nouveauGP.pays, sizeof(nouveauGP.pays), stdin) != NULL)   //meme systeme que ci dessus
        nouveauGP.pays[strcspn(nouveauGP.pays, "\n")] = 0;

    // Nombre de tours
    do{
        printf("Entrez le nombre de tours : ");
        if (fgets(stock, sizeof(stock), stdin)) {
            if (sscanf(stock, "%d", &nouveauGP.nombreTours) == 1 && nouveauGP.nombreTours >= 10 && nouveauGP.nombreTours <= 100) {  //cette methode car sinon on a des problemes avec le reesayer
                break;
            }
        }
        printf("Nombre de tours invalide, reesayer.\n");
    } while (1);


    // Date
    printf("Entrez la date (jour mois annee) : ");
    if (fgets(stock, sizeof(stock), stdin)) {
        if (sscanf(stock, "%d %d %d", 
            &nouveauGP.date.jour, 
            &nouveauGP.date.mois, 
            &nouveauGP.date.annee) != 3) {
            printf("Format de date invalide.\n");
            return;
        }
    }

    // horaire
    do{
    printf("Entrez l'heure de depart (heure minute) : ");
    if (fgets(stock, sizeof(stock), stdin)) {
        if (sscanf(stock, "%d %d", 
            &nouveauGP.horaire.heure, 
            &nouveauGP.horaire.minute) != 2) {
            printf("Format d'heure invalide.\n");
            return;
        }
    }
    } while (nouveauGP.horaire.heure <0 || nouveauGP.horaire.heure >23 || nouveauGP.horaire.minute <0 || nouveauGP.horaire.minute >59);


    
    // Initialisation des resultats
    nouveauGP.nombreResultats = 0;
    // Actif
    nouveauGP.actif = 1;
    
    grandsPrix[*nbGrandsPrix] = nouveauGP;
    (*nbGrandsPrix)++;
    printf("Grand Prix de %s ajoute avec succes.\n", nouveauGP.nomCircuit);
}

/*----------------------------------------------------------------------------------------------------*/

void afficherGrandsPrix(GrandPrix grandsPrix[], int nbGrandsPrix)
{
    printf("\nCalendrier des Grands Prix :\n");
    for (int i = 0; i < nbGrandsPrix; i++) {
        printf("\nGrand Prix #%d:\n", i + 1);
        printf("Circuit: %s\n", grandsPrix[i].nomCircuit);
        printf("Pays: %s\n", grandsPrix[i].pays);
        printf("Date: %02d/%02d/%d\n", grandsPrix[i].date.jour, grandsPrix[i].date.mois, grandsPrix[i].date.annee);
        printf("Heure de depart: %02d:%02d\n", grandsPrix[i].horaire.heure, grandsPrix[i].horaire.minute);
        printf("Nombre de tours: %d\n", grandsPrix[i].nombreTours);
        printf("etat: %s\n", grandsPrix[i].actif ? "Actif" : "Annule");
        
    }
}
//fonction a part pour permettre uen meilleur lisibilite
int rechercherGrandPrix(GrandPrix grandsPrix[], int nbGrandsPrix, const char *nomCircuit)
{
    for (int i = 0; i < nbGrandsPrix; i++) {
        if (strcmp(grandsPrix[i].nomCircuit, nomCircuit) == 0) {
            return i;
        }
    }
    return -1;
}

/*----------------------------------------------------------------------------------------------------*/

void supprimerGrandPrix(GrandPrix grandsPrix[], int *nbGrandsPrix, const char *nomCircuit, 
                       Pilote pilotes[], int nbPilotes)
{   //cherche l index du grand prix a supprimer
    int index = rechercherGrandPrix(grandsPrix, *nbGrandsPrix, nomCircuit);
    if (index == -1) {
        printf("Grand Prix de %s non trouve.\n", nomCircuit);
        return;
    }

    // Retirer les points attribues lors de cette course
    for (int i = 0; i < grandsPrix[index].nombreResultats; i++) {
        for (int j = 0; j < nbPilotes; j++) {
            if (strcmp(pilotes[j].nom, grandsPrix[index].resultats[i].nomPilote) == 0 &&strcmp(pilotes[j].prenom, grandsPrix[index].resultats[i].prenomPilote) == 0)  //compare les noms et prenoms pour trouver le pilote correspondant
            {   pilotes[j].points -= grandsPrix[index].resultats[i].pointsobtenus; 
                break;
            }
        }
    }

    // Decaler les grands prix suivants
    for (int i = index; i < *nbGrandsPrix - 1; i++) {
        grandsPrix[i] = grandsPrix[i + 1];
    }
    (*nbGrandsPrix)--;

    printf("Grand Prix de %s supprime avec succes et points recalcules.\n", nomCircuit);
}




/*----------------------------------------------------------------------------------------------------*/



//saisie du classment final avec le temps
void majgp(GrandPrix *gp, Pilote pilotes[], int nbPilotes)
{
    if (!gp) return;  // sort si gp est null
    int numeroPilote;
    printf("Mise a jour des resultats pour le Grand Prix de %s\n", gp->nomCircuit);
    printf("Entrez le nombre de pilotes ayant termine la course (max 20) : ");
    int nbResultats;
    scanf("%d", &nbResultats);


    if (nbResultats < 1 || nbResultats > 20) {
        printf("Nombre de resultats invalide.\n");
        return;
    }

    gp->nombreResultats = nbResultats;

    for (int i = 0; i < nbResultats; i++) {
        ResultatCourse *resultat = &gp->resultats[i];
        do{
        printf("Entrez le numero du pilote pour la position %d : ", i + 1);
        scanf("%d", &numeroPilote);
        }while(numeroutilise(pilotes, nbPilotes, numeroPilote) == 0);
        // Trouve le pilote correspondant
        for (int j = 0; j < nbPilotes; j++) {
            if (pilotes[j].numero == numeroPilote) { 
                // copie le nom du pilote   
                strcpy(resultat->nomPilote, pilotes[j].nom);                   
                strcpy(resultat->prenomPilote, pilotes[j].prenom);
                strcpy(resultat->nationalite, pilotes[j].nationalite);
                break;
            }
        }
        resultat->position = i + 1;

        printf("Entrez le temps realise par le pilote (format HH:MM:SS.mmm) pour la position %d : ", i + 1);
        if (fgets(resultat->tempsrealise, sizeof(resultat->tempsrealise), stdin) != NULL)   //si fgets ne renvoie pas NULL alors on continue
            resultat->tempsrealise[strcspn(resultat->tempsrealise, "\n")] = 0;      //strcspn pour remplacer le \n par \0

        resultat->pointsobtenus = calculerPoints(resultat->position);

        // Met a jour les points du pilote dans la liste des pilotes
        for (int j = 0; j < nbPilotes; j++) {
            if (strcmp(pilotes[j].nom, resultat->nomPilote) == 0 && strcmp(pilotes[j].prenom, resultat->prenomPilote) == 0) {
                pilotes[j].points += resultat->pointsobtenus;
                break;
            }
        }
    }
}
