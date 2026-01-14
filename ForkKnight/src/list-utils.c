#include <stdlib.h>
#include <stdio.h>
#include "../headers/list-utils.h"
#include "../headers/player.h"

t_cell* createCell(Player* player) {
    if (player == NULL) return NULL;
    t_cell *cell = malloc(sizeof *cell);
    if (cell == NULL) return NULL;
    cell->value = player;
    cell->next = NULL;
    return cell;
}

void destroyCell(t_cell* cell) {
    if (cell == NULL) return;
    free(cell);
}

t_queue * createQueue() {
    t_queue *q = malloc(sizeof *q);
    if (q == NULL) return NULL;
    q->head = NULL;
    q->tail = NULL;
    return q;
}

int isQueueEmpty(t_queue* queue) {
    if (queue == NULL) return 1;
    return (queue->head == NULL) ? 1 : 0;
}

void enqueue(t_queue * queue, Player * player) {
     if (queue == NULL || player == NULL) return;
     if (player->inQueue) return; // eviter double-ajout

     t_cell *cell = createCell(player);
     if (cell == NULL) return;

    if (isQueueEmpty(queue)) {
        queue->head = cell;
        queue->tail = cell;
    } else {
        queue->tail->next = cell;
        queue->tail = cell;
    }
    player->inQueue = 1;
}

Player * dequeue(t_queue* queue) {
    if (queue == NULL) return NULL;
    if (isQueueEmpty(queue)) return NULL;

    t_cell *old = queue->head;
    Player *p = old->value;

    queue->head = old->next;
    if (queue->head == NULL) { // file devenue vide
        queue->tail = NULL;
    }

    if (p) p->inQueue = 0;
    free(old); // libere la cellule mais pas le joueur
    return p;
}

t_cell * removeHead(t_queue * queue) {
    if (queue == NULL) return NULL;
    if (isQueueEmpty(queue)) return NULL;

    t_cell *old = queue->head;
    Player *p = old->value;

    queue->head = old->next;
    if (queue->head == NULL) queue->tail = NULL;

    old->next = NULL; // detacher proprement
    if (p) p->inQueue = 0;
    return old; // la memoire de la cellule n'est PAS liberee ici
}

void displayQueue(t_queue* queue) {
    if (queue == NULL) {
        printf("Aucune file (queue == NULL)\n");
        return;
    }

    printf("======= File d'attente =======\n");
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
    printf("Total: %d joueur%s en attente\n", idx, (idx > 1) ? "s" : "");
    printf("==============================\n");
}

void destroyQueue(t_queue * queue) {
    if (queue == NULL) return;
    t_cell *cell;
    while ((cell = removeHead(queue)) != NULL) {
        destroyCell(cell);
    }
    free(queue);
}