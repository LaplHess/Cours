#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/player.h"
#include "../headers/array-utils.h"

#define MAX_PLAYERS 100

// 1.5 Ajouter un joueur
int addPlayer(Player* players[], int* count, Player* player) {
    if (players == NULL || count == NULL || player == NULL) return 0;
    if (*count >= MAX_PLAYERS) return 0;
    players[*count] = player;
    (*count)++;
    return 1;
}

// 1.6 Recherche par pseudo
int searchPlayerByUsername(Player* players[], int count, const char* username) {
    if (players == NULL || username == NULL) return -1;
    for (int i = 0; i < count; i++) {
        if (players[i] != NULL && strcmp(players[i]->username, username) == 0) {
            return i;
        }
    }
    return -1;
}

// 1.7 Suppression
int removePlayer(Player* players[], int* count, const char* username) {
    if (players == NULL || count == NULL || username == NULL) return 0;
    int index = searchPlayerByUsername(players, *count, username);
    if (index == -1) return 0;

    destroyPlayer(players[index]);

    for (int i = index; i < *count - 1; i++) {
        players[i] = players[i + 1];
    }
    (*count)--;
    players[*count] = NULL; 

    return 1;
}

// 1,8 Tri par Spicy Index (bulle)
void sortPlayersBySpicyIndex(Player* players[], int count) {
    if (players == NULL) return;
    for (int i = 0; i < count - 1; i++) {
        for (int j = 0; j < count - i - 1; j++) {
            if (players[j]->spicyIndex < players[j + 1]->spicyIndex) {
                Player* tmp = players[j];
                players[j] = players[j + 1];
                players[j + 1] = tmp;
            }
        }
    }
}

// 2.1 Creation du tableau dynamique
Player** createPlayerArray(int size) {
    if (size <= 0) size = MAX_PLAYERS;
    Player** players = (Player**) malloc(size * sizeof(Player*));
    if (players == NULL) {
        fprintf(stderr, "Erreur : allocation du tableau de joueurs echouee.\n");
        return NULL;
    }
    for (int i = 0; i < size; i++) {
        players[i] = NULL;
    }
    return players;
}

// 2.3 Chargement des joueurs depuis un fichier
Player** loadPlayers(const char* filename, int* count) {
    if (count == NULL) return NULL;
    *count = 0;
    FILE* file = fopen(filename, "r");
    if (file == NULL) {
        return NULL;
    }

    int numPlayersExpected = 0;
    if (fscanf(file, "%d", &numPlayersExpected) != 1) {
        fclose(file);
        return NULL;
    }

    int capacity = (numPlayersExpected > 0) ? numPlayersExpected + 5 : 16;
    Player** players = (Player**)malloc(capacity * sizeof(Player*));
    if (players == NULL) {
        fclose(file);
        fprintf(stderr, "Erreur : allocation initiale impossible.\n");
        return NULL;
    }
    for (int i = 0; i < capacity; i++) players[i] = NULL;

    char username[50];
    int level, spicyIndex, numGames, numWins, numLosses, inQueue;
    while (fscanf(file, "%49s %d %d %d %d %d %d",
                  username, &level, &spicyIndex, &numGames, &numWins, &numLosses, &inQueue) == 7) {
        if (*count >= capacity) {
            int newcap = capacity * 2;
            Player** tmp = (Player**)realloc(players, newcap * sizeof(Player*));
            if (tmp == NULL) {
                // allocation echouee : nettoyage et sortie
                for (int i = 0; i < *count; i++) destroyPlayer(players[i]);
                free(players);
                fclose(file);
                fprintf(stderr, "Erreur : realloc echouee lors du chargement.\n");
                *count = 0;
                return NULL;
            }
            players = tmp;
            for (int i = capacity; i < newcap; i++) players[i] = NULL;
            capacity = newcap;
        }

        Player* p = createPlayer(username);
        if (p == NULL) {
            // nettoyage partiel
            for (int i = 0; i < *count; i++) destroyPlayer(players[i]);
            free(players);
            fclose(file);
            *count = 0;
            return NULL;
        }
        p->level = level;
        p->spicyIndex = spicyIndex;
        p->numGames = numGames;
        p->numWins = numWins;
        p->numLosses = numLosses;
        p->inQueue = inQueue;

        players[*count] = p;
        (*count)++;
    }

    fclose(file);

    if (*count > 0) {
        Player** shrink = (Player**)realloc(players, (*count) * sizeof(Player*));
        if (shrink != NULL) players = shrink;
    } else {
    }

    return players;
}

// 2.4 sauvegarde des joueurs dans un fichier
void savePlayers(const char* filename, Player* players[], int count) {
    if (filename == NULL || players == NULL) return;
    FILE* file = fopen(filename, "w");
    if (file == NULL) return;

    fprintf(file, "%d\n", count);

    for (int i = 0; i < count; i++) {
        if (players[i] == NULL) continue;
        fprintf(file, "%s %d %d %d %d %d %d\n",
                players[i]->username,
                players[i]->level,
                players[i]->spicyIndex,
                players[i]->numGames,
                players[i]->numWins,
                players[i]->numLosses,
                players[i]->inQueue);
    }
    fclose(file);
}
//

