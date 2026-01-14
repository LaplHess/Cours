#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/array-utils.h"
#include "../headers/player.h"
#define MAX_PLAYERS 100
#include "../headers/list-utils.h"
#include "../headers/priority-queue.h"
#include "../headers/match.h"


int addPlayer(Player* players[], int* count, Player* player);
int searchPlayerByUsername(Player* players[], int count, const char* username);
int removePlayer(Player* players[], int* count, const char* username);
void sortPlayersBySpicyIndex(Player* players[], int count);
void displayAllPlayers(Player* players[], int count);
void displayMenu();

int main() {
    Player** allPlayers = NULL;
    int nbPlayers = 0;
    const char* datafilename = "input/players_50.txt";


    t_priority_queue* matchmakingQueue = createPriorityQueue();
    t_queue* fifoQueue = createQueue();
    if (matchmakingQueue == NULL || fifoQueue == NULL){
        fprintf(stderr, "Erreur: impossible de creer les files d'attente\n");
        if (matchmakingQueue) destroyPriorityQueue(matchmakingQueue);
        if (fifoQueue) destroyQueue(fifoQueue);
        return EXIT_FAILURE;
    }
    printf("Chargement des joueur...\n");
    allPlayers = loadPlayers(datafilename, &nbPlayers);

    if (allPlayers == NULL) {
        // fichier introuvable ou erreur d'allocation -> creer un tableau vide
        printf("Aucun fichier de donnees trouve (%s). Creation d'un tableau vide.\n", datafilename);
        nbPlayers = 0;
        allPlayers = createPlayerArray(MAX_PLAYERS);
        if (allPlayers == NULL) {
            fprintf(stderr, "Erreur: impossible de creer le tableau de joueurs\n");
			destroyPriorityQueue(matchmakingQueue);//permet de libere la memoire pour la structure file d'attente
            return EXIT_FAILURE;
        }
    } else {
        // chargement reussi (meme si nbPlayers == 0)
        printf("Chargement reussi. %d joueur(s) trouves.\n", nbPlayers);
    }

    int choix;
    char username[30];
    Player* newPlayer = NULL;
	Player* dequeuedPlayer = NULL;//permet de retire le joueur de la file



    do {
        displayMenu();
        printf("Saisissez votre choix: ");
        scanf("%d", &choix);
        if (choix < 0 || choix > 19) {
            printf("Votre choix n'est pas valide. Veuillez entrer un nombre entre 0 et 19\n");
        }
        printf("----------------------------------------\n");
        switch (choix) {
            case 1:
                displayAllPlayers(allPlayers, nbPlayers);
                break;

            case 2:
                printf("Entrez le pseudo du nouveau joueur: ");
                scanf("%29s", username);

                // creer le joueur avant l'ajout
                newPlayer = createPlayer(username);
                if (newPlayer == NULL) {
                    printf("Erreur: impossible de creer le joueur\n");
                    break;
                }

                if (addPlayer(allPlayers, &nbPlayers, newPlayer)) {
                    printf("Joueur '%s' ajoute. Nombre de joueurs total : %d\n", username, nbPlayers);
                    // le joueur est maintenant dans allPlayers ; eviter de le detruire ici
                    newPlayer = NULL;
                }
                else {
                    printf("Erreur: impossible d'ajouter le joueur\n");
                    destroyPlayer(newPlayer); // nettoyer si ajout echoue
                    newPlayer = NULL;
                }
                break;

            case 3:
                printf("Saisir le pseudo du joueur: ");
                scanf("%29s", username);
                if (removePlayer(allPlayers, &nbPlayers, username)) {
                    printf("Joueur supprime. Nombre de joueurs total : %d\n", nbPlayers);
                }
                else {
                    printf("Erreur: joueur '%s' n'a pas ete trouver.\n", username);
                }
                break;

            case 4: {
                printf("Entrez le pseudo du joueur: ");
                scanf("%29s", username);
                int index = searchPlayerByUsername(allPlayers, nbPlayers, username);
                if (index != -1) {
                    printf("Joueur trouve:\n");
                    displayPlayer(allPlayers[index]);
                }
                else {
                    printf("Joueur non trouve:\n");
                }
                break;
            }
            case 5: {
                sortPlayersBySpicyIndex(allPlayers, nbPlayers);
                printf("Les joueurs on ete tries par Spicy Index:\n");
                break;
            }
            case 6: {
                savePlayers(datafilename, allPlayers, nbPlayers);
                printf("Sauvegarde terminee.\n");
                break;
            }

            case 7: {
                printf("Utilisez les options 12-15 pour gerer la file de priorite.\n");
                break;
            }

            case 8: {
                printf("Utilisez les options 12-15 pour gerer la file de priorite.\n");
                break;
            }

            case 9: {
                printf("Utilisez les options 12-15 pour gerer la file de priorite.\n");
                break;
            }

            case 10: {
                printf("Entrez le pseudo du joueur a mettre en file (FIFO): ");
                scanf("%29s", username);
                int index = searchPlayerByUsername(allPlayers, nbPlayers, username);
                if (index != -1) {
                    Player* p = allPlayers[index];
                    if (p->inQueue) {
                        printf("Erreur: le joueur '%s' est deja dans une file.\n", username);
                    } else {
                        enqueue(fifoQueue, p);
                        printf("Joueur '%s' ajoute a la file FIFO.\n", username);
                    }
                } else {
                    printf("Erreur: le joueur '%s' n'a pas ete trouve.\n", username);
                }
                break;
            }

            case 11: {
                dequeuedPlayer = dequeue(fifoQueue);
                if (dequeuedPlayer != NULL) {
                    printf("Joueur sorti de la file FIFO:\n");
                    displayPlayerMini(dequeuedPlayer);
                } else {
                    printf("La file FIFO est vide.\n");
                }
                break;
            }

            case 12: { // Ajouter joueur à la file de priorité (nouvelle position)
                printf("Entrez le pseudo du joueur a mettre en file (priorite): ");
                scanf("%29s", username);
                int index = searchPlayerByUsername(allPlayers, nbPlayers, username);
                if (index != -1) {
                    Player* p = allPlayers[index];
                    if (p->inQueue) {
                        printf("Erreur: le joueur '%s' est deja dans une file.\n", username);
                    } else {
                        insertWithPriority(matchmakingQueue, p);
                        printf("Joueur '%s' ajoute a la file de priorite. Spicy Index: %d\n", username, p->spicyIndex);
                    }
                } else {
                    printf("Erreur: le joueur '%s' n'a pas ete trouve.\n", username);
                }
                break;
            }

            case 13: { // Retirer le meilleur joueur (priorite)
                dequeuedPlayer = removeHighestPriority(matchmakingQueue);
                if (dequeuedPlayer != NULL) {
                    printf("Joueur sorti de la file de priorite:\n");
                    displayPlayerMini(dequeuedPlayer);
                } else {
                    printf("La file de priorite est vide.\n");
                }
                break;
            }

            case 14: { // Afficher la file de priorite
                displayPriorityQueue(matchmakingQueue);
                break;
            }

            case 15: { // Former un match équilibré depuis la file de priorite
                printf("Tentative de formation d'un match equilibre (depuis file de priorite)...\n");
                launchBalancedMatch(matchmakingQueue);
                break;
            }

            case 16: { // Afficher la file FIFO (nouvelle position)
                displayQueue(fifoQueue);
                break;
            }

            case 17: { // Former un match depuis la file FIFO (nouvelle position)
                printf("Formation d'un match depuis la file FIFO...\n");
                launchMatch(fifoQueue);
                break;
            }


            case 0: {
                printf("Sauvegarde des donnees avant de quitter...\n");
                savePlayers(datafilename, allPlayers, nbPlayers);
                printf("Au revoir\n");
                break;
            }
            default: {
                printf("choix non valide\n");
                break;
            }
        }
        printf("----------------------------------------\n");
    } while (choix != 0);

    destroyPlayerArray(allPlayers, nbPlayers);//netoyage de la memoir des joueur avant de quitter
	destroyPriorityQueue(matchmakingQueue);//netoyage de la file de priorite avant de quitter
	destroyQueue(fifoQueue); // nettoyer la file FIFO
    return 0;
}

void displayMenu() {
    printf("\n================ MENU MATCHMAKING ================\n");
    printf("1. Afficher tous les joueurs\n");
    printf("2. Ajouter un nouveau joueur\n");
    printf("3. supprimer un joueur par pseudo\n");
    printf("4. Rechercher un joueur par pseudo\n");
    printf("5. Trier les joueurs par niveau\n");
    printf("6. Sauvegarder les joueurs \n");
    printf("7. Ajouter un joueur au matchmaking (File de priorite)\n");
    printf("8. Retirer le meilleur joueur (File de priorite)\n");
    printf("9. Afficher la file de priorite\n");
    printf("10. Ajouter un joueur au matchmaking (FIFO)\n");
    printf("11. Retirer un joueur du matchmaking (FIFO)\n");
    printf("12. Ajouter un joueur a la file de priorite\n");
    printf("13. Retirer le meilleur joueur (priorite)\n");
    printf("14. Afficher la file de priorite\n");
    printf("15. Former un match equilibre (12 meilleurs)\n");
    printf("16. Afficher la file FIFO\n");
    printf("17. Former un match depuis la file FIFO\n");
    printf("0. Quitter\n");
    printf("==================================================\n");
}
//
