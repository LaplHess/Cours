#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "pilote.h"

/*les do whiles permettent de verifier les conditions de l ennonces qui repetent de facon continu qui s arettent grace au break*/



void ajouterPilote(Pilote pilotes[], int *tailleLogique, int tailleMax, Ecurie ecuries[], int nbEcuries, Pays pays[], int *nbPays)
{
    if (*tailleLogique >= tailleMax) {
        printf("Impossible d'ajouter un pilote : championnat complet ->%d/%d. \n", tailleMax,tailleMax);
        return;
    }
    Pilote nouveauPilote;

    /* Nom */
    do {
        printf("Entrez le nom du pilote : ");
        if (fgets(nouveauPilote.nom, sizeof(nouveauPilote.nom), stdin) != NULL)  //si fgets ne renvoie pas NULL alors on continue
            nouveauPilote.nom[strcspn(nouveauPilote.nom, "\n")] = '\0';  //strcspn pour remplacer le \n par \0
        if (strlen(nouveauPilote.nom) == 0 || strlen(nouveauPilote.nom) > 49) {
            printf("Nom Vide ou Trop grand reesayer\n");
        } else {
            break;
        }
    } while (1);   //repete jusqu'a une saisie correcte (break)

    /* Prenom */
    do {
        printf("Entrez le prenom du pilote : ");
        if (fgets(nouveauPilote.prenom, sizeof(nouveauPilote.prenom), stdin) != NULL)
            nouveauPilote.prenom[strcspn(nouveauPilote.prenom, "\n")] = '\0';   //meme systeme que ci dessus
        if (strlen(nouveauPilote.prenom) == 0 || strlen(nouveauPilote.prenom) > 49) {  //strlen pour verifier la taille 
            printf("Prenom Vide ou Trop grand reesayer\n");
        } else {
            break;
        }
    } while (1);

    /* Nationalite */
    do{
        printf("Entrez le pays d origine du pilote : ");
        if (fgets(nouveauPilote.nationalite, sizeof(nouveauPilote.nationalite), stdin) != NULL)
            nouveauPilote.nationalite[strcspn(nouveauPilote.nationalite, "\n")] = '\0';     //meme systeme que ci dessus
        if (paysexiste(nouveauPilote.nationalite, pays, *nbPays) == 0) {
            printf("Pays inexistant, reesayer\n");
        } else {
            break;
        }
    } while (1);
    /* Ecurie */
    do {
        printf("Entrez l'ecurie du pilote : ");
        if (fgets(nouveauPilote.Ecurie, sizeof(nouveauPilote.Ecurie), stdin) != NULL)
            nouveauPilote.Ecurie[strcspn(nouveauPilote.Ecurie, "\n")] = '\0';    //meme systeme que ci dessus
        if (ecurieexiste(nouveauPilote.Ecurie, ecuries, nbEcuries) == 0) {  //utilisation de la fonction ecurieexiste defini dans initialisation.c pour verifier l'existence
            printf("Ecurie inexistante, reesayer\n");
        } else {
            break;
        }
    } while (1);

    /* Numero */
    do{
        printf("Entrez le numero du pilote : ");
        scanf("%d", &nouveauPilote.numero);
    } while (numeroutilise(pilotes, *tailleLogique, nouveauPilote.numero) == 1);

    

    //age
    do{
        printf("Entrez l age du pilote : ");
        scanf("%d", &nouveauPilote.age);
    } while (nouveauPilote.age < 18 || nouveauPilote.age > 50);
    nouveauPilote.points = 0;
    nouveauPilote.actif = 1;

    pilotes[*tailleLogique] = nouveauPilote;
    (*tailleLogique)++;
    printf("Le Pilote %s %s ajoute avec succes.\n", nouveauPilote.prenom, nouveauPilote.nom);
}



/*----------------------------------------------------------------------------------------------------*/



void modifierPilote(Pilote pilotes[], int nbPilotes, int numero, int nouveauxPoints)
{
    int index = -1;     //verifier si le pilote existe
    for (int i = 0; i < nbPilotes; i++) {
        if (pilotes[i].numero == numero) {  //parcour de la liste des pilotes pour trouver le pilote recherche
            index = i;
            break;
        }
    }
    if (index != -1) {
        pilotes[index].points = nouveauxPoints;
        printf("Les points du pilote %s %s ont ete mis a jour a %d.\n", pilotes[index].prenom, pilotes[index].nom, nouveauxPoints);
    } else {
        printf("Pilote avec le numero %d non trouve.\n", numero);
    }
}


void modifiertoutpilotes(Pilote pilotes[], int nbPilotes, int numero, char ecurie[])    //fonction rajoute afin de gagner du temps sur la presentation
{
    //meme principe que modifier pilote mais pour tous les pilotes//
    int listepoints[10];
    for (int i = 0; i < nbPilotes; i++) 
    {
        printf("points du pilotes %d ", i+1);
        scanf("%d", &listepoints[i]);
    }
    for (int i = 0; i < nbPilotes; i++) 
    {
        modifierPilote(pilotes, nbPilotes, pilotes[i].numero, listepoints[i]);
    }
}




/*----------------------------------------------------------------------------------------------------*/



void afficherPilotes(Pilote pilotes[], int nbPilotes)
{
    printf("Liste des pilotes :\n");
    for (int i = 0; i < nbPilotes; i++) {
        printf("Pilote %d : %s %s, Nationalite : %s, ecurie : %s, Numero : %d, Âge : %d, Points : %d, Actif : %s\n",
               i + 1,
               pilotes[i].prenom,
               pilotes[i].nom,
               pilotes[i].nationalite,
               pilotes[i].Ecurie,
               pilotes[i].numero,
               pilotes[i].age,
               pilotes[i].points,
               pilotes[i].actif ? "Oui" : "Non");
    }
}


/*----------------------------------------------------------------------------------------------------*/


void supprimerPilote(Pilote pilotes[], int *nbPilotes, int numero)
{
    // index du pilote a supprimer
    int index = -1; 

    // cherche le pilote par numero
    for (int i = 0; i < *nbPilotes; i++) {
        if (pilotes[i].numero == numero) {
            index = i;
            break;
        }
    }

    if (index != -1) {
        // decale les pilotes suivants pour combler l'espace
        for (int j = index; j < *nbPilotes - 1; j++) {
            pilotes[j] = pilotes[j + 1];
        }
        (*nbPilotes)--; // met a jour le nombre total de pilotes
        printf("Pilote avec le numero %d supprime avec succes.\n", numero);
    } else {
        printf("Pilote avec le numero %d non trouve.\n", numero);
    }
}
//echange l ecurie de 2 pilotes(fonction "creative")

void echangerEcuriePilotes(Pilote *pilote1, Pilote *pilote2)
{
    char tempEcurie[50];
    strcpy(tempEcurie, pilote1->Ecurie);
    strcpy(pilote1->Ecurie, pilote2->Ecurie);
    strcpy(pilote2->Ecurie, tempEcurie);
    printf("Ecuries echangees entre les numeros %d et %d.\n", pilote1->numero, pilote2->numero);
}