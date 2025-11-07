#ifndef INITIALISATION_H
#define INITIALISATION_H
#include <string.h>

typedef struct {
    int jour;
    int mois;
    int annee;
}Date;
typedef struct {
    int heure;
    int minute;
}Heure;

//structures Pilote
typedef struct {
    char nom[50];
    char prenom[50];
    char nationalite[50];
    char Ecurie[50];
    int points;
    int numero;
    int age;
    int actif;
}Pilote;

//structure Ecurie
typedef struct {
    char nom[50];
    char pays[50];
    int points;
    int anneeCreation;
    char directeur[50];
    int  actif;
}Ecurie;

//structure ResultatCourse
typedef struct {
    char nomPilote[50];
    char prenomPilote[50];
    char nationalite[50];
    int position;
    char tempsrealise[20];
    int pointsobtenus;
}ResultatCourse;

//structure GrandPrix
typedef struct {
    char nomCircuit[50];
    char pays[50];
    int nombreTours;
    Date date;
    Heure horaire;
    ResultatCourse resultats[20];
    int nombreResultats;
    int actif; 
}GrandPrix;

//structure Pays
typedef struct {
    char nom[50];
}Pays;

int ecurieexiste(char ecurie[], Ecurie ecuries[], int nbEcuries);
int numeroutilise(Pilote pilotes[], int nbPilotes, int numero);
int paysexiste(char pays[], Pays paysList[], int nbPays);
void initialiserDonnees(Pilote pilotes[], int *nbPilotes, Ecurie ecuries[], int *nbEcuries,GrandPrix grandsPrix[], int *nbGrandsPrix,Pays pays[], int *nbPays);
void saisirResultatsCourse(GrandPrix* grandPrix, Pilote pilotes[], int nbPilotes);
int circuitexiste(char nomCircuit[], GrandPrix grandsPrix[], int nbGrandsPrix);
#endif