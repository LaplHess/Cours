#include "../headers/priority-queue.h"
#include "../headers/list-utils.h"
#include "../headers/player.h"
#include <stdio.h>
#include <stdlib.h>

#define MATCH_SIZE 12  //oblige de l initialise ici car ca ne marchais pas dans la fonctions

t_priority_queue * createPriorityQueue() {
    return createQueue();
}

void insertWithPriority(t_priority_queue * queue, Player * player) {
    if (queue == NULL || player == NULL) return;
    if (player->inQueue) return; // evite le double-ajout

    t_cell *cell = createCell(player);
    if (cell == NULL) return;

    // file vide
    if (isQueueEmpty(queue)) {
        queue->head = cell;
        queue->tail = cell;
        player->inQueue = 1;
        return;
    }

    // insertion en tête si spicyIndex plus grand que la tête
    if (player->spicyIndex > queue->head->value->spicyIndex) {
        cell->next = queue->head;
        queue->head = cell;
        player->inQueue = 1;
        return;
    }

    // insertion au milieu ou en fin
    t_cell *prev = queue->head;
    t_cell *cur = prev->next;

    // parcourir tant que cur.spicyIndex >= player->spicyIndex
    // pour placer le nouveau joueur apres les joueurs avec le meme spicyIndex
    while (cur != NULL && cur->value->spicyIndex >= player->spicyIndex) {
        prev = cur;
        cur = cur->next;
    }

    prev->next = cell;
    cell->next = cur;
    if (cur == NULL) {
        queue->tail = cell;
    }
    player->inQueue = 1;
}

Player * removeHighestPriority(t_priority_queue * queue) {
    if (queue == NULL) return NULL;
    return dequeue(queue);
}

void displayPriorityQueue(t_priority_queue * queue) {
    if (queue == NULL) {
        printf("Aucune file de priorite (queue == NULL)\n");
        return;
    }

    printf("====== File de Priorite ======\n");
    t_cell *cur = queue->head;
    int idx = 0;
    while (cur != NULL) {
        idx++;
        printf("%d. ", idx);
        if (cur->value != NULL) {
            displayPlayerMini(cur->value);
        } else {
            printf("[NULL]\n");
        }
        cur = cur->next;
    }
    printf("Total: %d joueur%s (ordre decroissant)\n", idx, (idx > 1) ? "s" : "");
    printf("==============================\n");
}

void destroyPriorityQueue(t_priority_queue * queue) {
    if (queue == NULL) return;
    destroyQueue(queue);
}
void formBalancedMatch(t_priority_queue* queue) {
    if (queue == NULL) return;

    Player* participants[MATCH_SIZE];
    int count = 0;

    // retirer jusqu a match_size meilleur
    for (int i = 0; i < MATCH_SIZE; ++i) {
        Player* p = removeHighestPriority(queue);
        if (p == NULL) break;
        participants[count++] = p;
    }

    if (count == 0) {
        printf("Pas assez de joueurs pour former un match.\n");
        return;
    }

    printf("=== Match forme avec %d joueur(s) ===\n", count);
    int maxSI = participants[0]->spicyIndex;
    int minSI = participants[0]->spicyIndex;
    for (int i = 0; i < count; ++i) {
        printf("%d. ", i + 1);
        displayPlayerMini(participants[i]);
        if (participants[i]->spicyIndex > maxSI) maxSI = participants[i]->spicyIndex;
        if (participants[i]->spicyIndex < minSI) minSI = participants[i]->spicyIndex;
    }
    printf("Ecart (max - min) : %d\n", maxSI - minSI);
    printf("Simulation du match...\n");
    printf("Match termine. Les joueurs ont ete retires de la file de priorite.\n");
}
