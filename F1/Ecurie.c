#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include "Ecurie.h"
/*les do whiles permettent de verifier les conditions de l ennonces qui repetent de facon continu qui s arettent grace au break*/
// Gestion des ecuries / ajouter afficher supprimer (gerer pilotes associes) mise a jour des points
int nomecurieexiste(Ecurie ecuries[], int nbEcuries, const char *nom)
{
	for (int i = 0; i < nbEcuries; i++) {
		if (strcmp(ecuries[i].nom, nom) == 0) {
			return 1; // L'ecurie existe
		}
	}
	return 0; // L'ecurie n'existe pas
}
void ajouterEcurie(Ecurie ecuries[], int *tailleLogique, int tailleMax, Pays pays[], int *nbPays)
{
	if (*tailleLogique >= tailleMax) {
		printf("Impossible d'ajouter une ecurie : liste complete ->%d/%d.\n", tailleMax, tailleMax);
		return;
	}

	Ecurie nouv;
	//nom
	do{
	printf(" Entrez le nom de l'ecurie :");
	if (fgets(nouv.nom, sizeof(nouv.nom), stdin) != NULL)	//permet de verifier que fgets ne renvoie pas NULL
		nouv.nom[strcspn(nouv.nom, "\n")] = 0;		//strcspn pour remplacer le \n par \0
	if (strlen(nouv.nom) ==0 || nomecurieexiste(ecuries,*tailleLogique,nouv.nom)==1){
		printf("Nom vide ou ecurie existante, reesayer\n");
	} else {
		break;
	}
	} while (1);

	//pays
	do
	{
	printf("Entrez le pays de l'ecurie (Debute avec une majuscule ): ");
	if (fgets(nouv.pays, sizeof(nouv.pays), stdin) != NULL)
		nouv.pays[strcspn(nouv.pays, "\n")] = 0;}		//meme systeme que ci dessus
	while (strlen(nouv.pays)==0 && paysexiste(nouv.pays, pays, *nbPays) == 0); 
	
	
	//directeur
	do
	{
	printf("Entrez le directeur de l'ecurie : ");
	if (fgets(nouv.directeur, sizeof(nouv.directeur), stdin) != NULL)
		nouv.directeur[strcspn(nouv.directeur, "\n")] = 0;		//meme systeme que ci dessus
	} while (strlen(nouv.directeur) ==0 );



	//anneeCreation
	do
	{
	printf("Entrez l'annee de creation  : ");
	(scanf("%d", &nouv.anneeCreation) != 1);
	}while (nouv.anneeCreation < 1900 || nouv.anneeCreation > 2025);

	nouv.points = 0;
	nouv.actif = 1;


	

	ecuries[*tailleLogique] = nouv; //ajout de la nouvelle ecurie dans le tableau
	(*tailleLogique)++; //incrementation de la taille logique
	printf("Ecurie '%s' ajoutee avec succes.\n", nouv.nom);
}


void afficherEcuries(Ecurie ecuries[], int nbEcuries)
{
	printf("Liste des ecuries :\n");
	for (int i = 0; i < nbEcuries; i++) {
		printf("Ecurie %d : %s, Pays : %s, Directeur : %s, Annee : %d, Points : %d, Actif : %s\n",
			   i + 1,
			   ecuries[i].nom,
			   ecuries[i].pays,
			   ecuries[i].directeur,
			   ecuries[i].anneeCreation,
			   ecuries[i].points,
			   ecuries[i].actif ? "Oui" : "Non");
	}
}


int rechercherEcurie(Ecurie ecuries[], int nbEcuries, const char *nom)
{
	for (int i = 0; i < nbEcuries; i++) {
		if (strcmp(ecuries[i].nom, nom) == 0) return i;
	}
	return -1;
}

/*----------------------------------------------------------------------------------------------------*/



void supprimerEcurie(Ecurie ecuries[], int *nbEcuries, const char *nom, Pilote pilotes[], int nbPilotes)
{
	int index = rechercherEcurie(ecuries, *nbEcuries, nom);
	if (index == -1) {
		printf("Ecurie '%s' non trouvee.\n", nom);
		return;
	}

	// gerer pilotes associes  
	for (int i = 0; i < nbPilotes; i++) {
		if (strcmp(pilotes[i].Ecurie, nom) == 0) {
			strcpy(pilotes[i].Ecurie, "Sans Ecurie");	//detache les pilotes associes en mettant leur champ Ecurie a vide
		}
	}

	//decale les ecuries suivantes pour combler l'espace
	for (int j = index; j < *nbEcuries - 1; j++) {
		ecuries[j] = ecuries[j + 1];	
	}
	(*nbEcuries)--;
	printf("Ecurie '%s' supprimee avec succes.\n", nom);
}


// Met a jour automatiquement les points de chaque ecurie en sommant les points des pilotes affilies
void mettreAJourPointsEcuries(Ecurie ecuries[], int nbEcuries, Pilote pilotes[], int nbPilotes)
{
	for (int i = 0; i < nbEcuries; i++) {
		ecuries[i].points = 0;	
		for (int j = 0; j < nbPilotes; j++) {
			if (strcmp(pilotes[j].Ecurie, ecuries[i].nom) == 0) {	//verifie si le pilote appartient a l'ecurie
				ecuries[i].points += pilotes[j].points;	
			}
		}
	}
	printf("Points des ecuries mis a jour a partir des pilotes.\n");
}

