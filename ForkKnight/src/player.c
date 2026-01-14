#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../headers/player.h"
#define MAX_PLAYERS 100

// 1.1 Creation d un joueur
Player* createPlayer(const char* username) {
    if (username == NULL) return NULL;

    Player* p = (Player*) malloc(sizeof(Player));
    if (p == NULL) return NULL;

    strncpy(p->username, username, sizeof(p->username) - 1);
    p->username[sizeof(p->username) - 1] = '\0'; // securite

    p->level = 1;
    p->spicyIndex = 1000;
    p->numGames = 0;
    p->numWins = 0;
    p->numLosses = 0;
    p->inQueue = 0;

    return p;
}

// 1.2 Liberation d un joueur
void destroyPlayer(Player* player) {
    if (player != NULL) {
        free(player);
    }
}

void destroyPlayerArray(Player** players, int count) {
    if (players == NULL) return;
    for (int i = 0; i < count; i++) {
        destroyPlayer(players[i]);
    }
    free(players);
}

// 1.3 Affichage detaille
void displayPlayer(const Player* player) {
    if (player == NULL) return;

    printf("==========================================\n");
    printf("Player: %s\n", player->username);
    printf("Level: %d | Spicy Index: %d\n", player->level, player->spicyIndex);
    printf("Games: %d | Wins: %d | Losses: %d\n", player->numGames, player->numWins, player->numLosses);
    printf("In Queue: %s\n", player->inQueue ? "Yes" : "No");
    printf("==========================================\n");
}

// 1.4 Affichage condense
void displayPlayerMini(const Player* player) {
    if (player == NULL) return;

    printf("[%s | Lvl: %d | SI: %d]\n", player->username, player->level, player->spicyIndex);
}

// Creation d un tableau de joueurs
Player** createPlayersArray(int size) {
    return (Player**)malloc(size * sizeof(Player*));
}

void displayAllPlayers(Player* players[], int count) {
    if (players == NULL || count == 0) {
        printf("Aucun joueur à afficher.\n");
        return;
    }
    for (int i = 0; i < count; i++) {
        displayPlayerMini(players[i]);
    }
}
//


