#include <string.h>
#include "initialisation.h" // contient les typedefs


//utilisation de cette fonction pour eviter la disparition des donnees a chaque execution du programme et pour qu il soit utilisable dans le main 
void initialiserDonnees(Pilote pilotes[], int *nbPilotes,Ecurie ecuries[], int *nbEcuries,GrandPrix grandsPrix[], int *nbGrandsPrix,Pays pays[], int *nbPays)
{
    // Initialisation des ecuries
    *nbEcuries = 5;
    Ecurie tempEcuries[5] = {
    {"Red Bull Racing", "Autriche", 0, 2005, "Christian Horner", 1},
    {"Scuderia Ferrari", "Italie", 0, 1950, "Frederic Vasseur", 1},
    {"Mercedes-AMG", "Allemagne", 0, 2010, "Toto Wolff", 1},
    {"McLaren Racing", "Royaume-Uni", 0, 1966, "Andrea Stella", 1},
    {"Aston Martin", "Royaume-Uni", 0, 2021, "Mike Krack", 1}
    };

    // Finish the incomplete for loops
    for (int i = 0; i < *nbEcuries; i++) {
        ecuries[i] = tempEcuries[i];
    }

    // Initialisation des pilotes
    *nbPilotes = 10;
    Pilote tempsPilotes[10] = {
     {"Verstappen", "Max", "Pays-Bas", "Red Bull Racing", 0, 1, 27, 1},
    {"Perez", "Sergio", "Mexique", "Red Bull Racing", 0, 11, 34, 1},
    {"Leclerc", "Charles", "Monaco", "Scuderia Ferrari", 0, 16, 27, 1},
    {"Sainz", "Carlos", "Espagne", "Scuderia Ferrari", 0, 55, 30, 1},
    {"Hamilton", "Lewis", "Royaume-Uni", "Mercedes-AMG", 0, 44, 39, 1},
    {"Russell", "George", "Royaume-Uni", "Mercedes-AMG", 0, 63, 26, 1},
    {"Norris", "Lando", "Royaume-Uni", "McLaren Racing", 0, 4, 25, 1},
    {"Piastri", "Oscar", "Australie", "McLaren Racing", 0, 81, 23, 1},
    {"Alonso", "Fernando", "Espagne", "Aston Martin", 0, 14, 43, 1},
    {"Stroll", "Lance", "Canada", "Aston Martin", 0, 18, 26, 1}
    };

    for (int i = 0; i < *nbPilotes; i++) {
        pilotes[i] = tempsPilotes[i];
    }


    // Initialisation du Grand Prix de Monaco

    
    *nbGrandsPrix = 3;
    /* Grand Prix 0 : Monaco */
    strcpy(grandsPrix[0].nomCircuit, "Circuit de Monaco");
    strcpy(grandsPrix[0].pays, "Monaco");
    grandsPrix[0].nombreTours = 78;
    grandsPrix[0].date = (Date){26, 5, 2024};
    grandsPrix[0].horaire = (Heure){15, 0};
    grandsPrix[0].nombreResultats = 10;
    grandsPrix[0].actif = 1;
    ResultatCourse resultats0[10] = {
        {"Verstappen", "Max", "Pays-Bas", 1, "1:44:12.456", 25},
        {"Leclerc", "Charles", "Monaco", 2, "1:44:18.234", 18},
        {"Hamilton", "Lewis", "Royaume-Uni", 3, "1:44:25.678", 15},
        {"Norris", "Lando", "Royaume-Uni", 4, "1:44:32.123", 12},
        {"Sainz", "Carlos", "Espagne", 5, "1:44:39.456", 10},
        {"Russell", "George", "Royaume-Uni", 6, "1:44:45.789", 8},
        {"Perez", "Sergio", "Mexique", 7, "1:44:52.234", 6},
        {"Alonso", "Fernando", "Espagne", 8, "1:44:58.567", 4},
        {"Piastri", "Oscar", "Australie", 9, "1:45:04.890", 2},
        {"Stroll", "Lance", "Canada", 10, "1:45:11.123", 1}
    };

    for (int i = 0; i < grandsPrix[0].nombreResultats; i++) {
        grandsPrix[0].resultats[i] = resultats0[i];
    }

    /* Grand Prix 1 : Monza */
    strcpy(grandsPrix[1].nomCircuit, "Autodromo Nazionale Monza");
    strcpy(grandsPrix[1].pays, "Italie");
    grandsPrix[1].nombreTours = 53;
    grandsPrix[1].date = (Date){7, 9, 2024};
    grandsPrix[1].horaire = (Heure){14, 0};
    grandsPrix[1].nombreResultats = 10;
    grandsPrix[1].actif = 1;

    ResultatCourse resultats1[10] = {
        {"Leclerc", "Charles", "Monaco", 1, "1:21:34.123", 25},
        {"Sainz", "Carlos", "Espagne", 2, "1:21:40.567", 18},
        {"Verstappen", "Max", "Pays-Bas", 3, "1:21:47.890", 15},
        {"Hamilton", "Lewis", "Royaume-Uni", 4, "1:21:55.234", 12},
        {"Perez", "Sergio", "Mexique", 5, "1:22:02.678", 10},
        {"Norris", "Lando", "Royaume-Uni", 6, "1:22:09.012", 8},
        {"Russell", "George", "Royaume-Uni", 7, "1:22:16.345", 6},
        {"Alonso", "Fernando", "Espagne", 8, "1:22:23.678", 4},
        {"Piastri", "Oscar", "Australie", 9, "1:22:30.901", 2},
        {"Stroll", "Lance", "Canada", 10, "1:22:38.234", 1}
    };

    for (int i = 0; i < grandsPrix[1].nombreResultats; i++)
        grandsPrix[1].resultats[i] = resultats1[i];

    /* Grand Prix 2 : Silverstone */
    strcpy(grandsPrix[2].nomCircuit, "Silverstone Circuit");
    strcpy(grandsPrix[2].pays, "Royaume-Uni");
    grandsPrix[2].nombreTours = 52;
    grandsPrix[2].date = (Date){6, 7, 2024};
    grandsPrix[2].horaire = (Heure){15, 0};
    grandsPrix[2].nombreResultats = 10;
    grandsPrix[2].actif = 1;

    ResultatCourse resultats2[10] = {
        {"Hamilton", "Lewis", "Royaume-Uni", 1, "1:28:12.456", 25},
        {"Verstappen", "Max", "Pays-Bas", 2, "1:28:18.234", 18},
        {"Norris", "Lando", "Royaume-Uni", 3, "1:28:25.678", 15},
        {"Leclerc", "Charles", "Monaco", 4, "1:28:32.123", 12},
        {"Sainz", "Carlos", "Espagne", 5, "1:28:39.456", 10},
        {"Russell", "George", "Royaume-Uni", 6, "1:28:45.789", 8},
        {"Perez", "Sergio", "Mexique", 7, "1:28:52.234", 6},
        {"Alonso", "Fernando", "Espagne", 8, "1:28:58.567", 4},
        {"Piastri", "Oscar", "Australie", 9, "1:29:04.890", 2},
        {"Stroll", "Lance", "Canada", 10, "1:29:11.123", 1}
    };

    for (int i = 0; i < grandsPrix[2].nombreResultats; i++)
        grandsPrix[2].resultats[i] = resultats2[i];



        //liste des pays 

    *nbPays = 25;
    Pays tempsPays[25] = {
        {"Monaco"},
        {"Italie"},
        {"Royaume-Uni"},
        {"Espagne"},
        {"Pays-Bas"},
        {"France"},
        {"Allemagne"},
        {"Belgique"},
        {"Hongrie"},
        {"Autriche"},
        {"Suisse"},
        {"Portugal"},
        {"Turquie"},
        {"Russie"},
        {"Chine"},
        {"Japon"},
        {"Australie"},
        {"Canada"},
        {"etats-Unis"},
        {"Mexique"},
        {"Bresil"},
        {"Argentine"},
        {"Afrique du Sud"},
        {"emirats arabes unis"},
        {"Singapour"}

    };

    for (int i = 0; i < *nbPays; ++i) pays[i] = tempsPays[i];
}

    //verfication existance


int circuitexiste(char nomCircuit[], GrandPrix grandsPrix[], int nbGrandsPrix)
{
    for (int i = 0; i < nbGrandsPrix; i++) {
        if (strcmp(grandsPrix[i].nomCircuit, nomCircuit) == 0) {
            return 1; // Le circuit existe
        }
    }
    return 0; // Le circuit n'existe pas
}

int ecurieexiste(char ecurie[], Ecurie ecuries[], int nbEcuries)
{
    for (int i = 0; i < nbEcuries; i++) {
        if (strcmp(ecuries[i].nom, ecurie) == 0) {
            return 1; // L'ecurie existe
        }
    }
    return 0; // L'ecurie n'existe pas
}

int numeroutilise(Pilote pilotes[], int nbPilotes, int numero)
{
    for (int i = 0; i < nbPilotes; i++) {
        if (pilotes[i].numero == numero) {
            return 1; // Le numero est deja utilise
        }
    }
    return 0; // Le numero n'est pas utilise
}

int paysexiste(char pays[], Pays paysList[], int nbPays)
{
    for (int i = 0; i < nbPays; i++) {
        if (strcmp(paysList[i].nom, pays) == 0) {
            return 1; // Le pays existe
        }
    }
    return 0; // Le pays n'existe pas
}
