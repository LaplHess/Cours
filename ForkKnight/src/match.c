#include "../headers/match.h"

// 3.1 Création d’un match

Match * createMatch() {
    Match * match = malloc(sizeof(Match));
    if (!match)
        return NULL;

    match->players = malloc(sizeof(Player *) * MATCH_MAX_PLAYERS);
    if (!match->players) {
        free(match);
        return NULL;
    }

    match->results = NULL;
    match->numPlayers = 0;

    return match;
}

// 3.2 Destruction d’un match

void destroyMatch(Match * match) {
    if (!match)
        return;

    if (match->players)
        free(match->players);

    if (match->results)
        free(match->results);

    free(match);
}


// Fisher-Yates Shuffle

static void fisherYatesShuffle(int * array, int n) {
    for (int i = n - 1; i > 0; i--) {
        int j = rand() % (i + 1);
        int tmp = array[i];
        array[i] = array[j];
        array[j] = tmp;
    }
}


// 3.4 Simulation du match

void simulateMatch(Match * match) {
    if (!match || match->numPlayers < 2)
        return;

    if (match->results)
        free(match->results);

    match->results = malloc(sizeof(int) * match->numPlayers);
    if (!match->results)
        return;

    for (int i = 0; i < match->numPlayers; i++)
        match->results[i] = i;

    fisherYatesShuffle(match->results, match->numPlayers);
}


// 3.3 Ajout des joueurs

void addMatchPlayers(t_queue * queue, Match * match) {
    if (!queue || !match)
        return;

    while (match->numPlayers < MATCH_MAX_PLAYERS && !isQueueEmpty(queue)) {
        Player * p = dequeue(queue);
        if (!p)
            break;

        p->inQueue = 0;
        match->players[match->numPlayers++] = p;
    }
}


// 3.6 Affichage info match

void displayMatchInfo(const Match * match) {
    if (!match) {
        printf("Erreur: match NULL\n");
        return;
    }

    printf("========================================\n");
    printf("           MATCH INFORMATION\n");
    printf("========================================\n");
    printf("Participants: %d\n", match->numPlayers);
    printf("----------------------------------------\n");

    for (int i = 0; i < match->numPlayers; i++) {
        printf("%d. ", i + 1);
        displayPlayerMini(match->players[i]);
        printf("\n");
    }

    printf("========================================\n");
}


// 3.5 Mise à jour des stats

void updatePlayerStats(Match * match) {
    if (!match || !match->results)
        return;

    int n = match->numPlayers;
    if (n < 2)
        return;

    int baseGain = 100 / (n - 1);

    for (int r = 0; r < n; r++) {
        Player * p = match->players[match->results[r]];

        p->numGames++;

        if (r == 0)
            p->numWins++;
        else
            p->numLosses++;

        int gain = (n - r - 1) * baseGain;
        p->spicyIndex += gain;
    }
}


// 3.7 Affichage résultats

void displayMatchResult(const Match * match) {
    if (!match || !match->results) {
        printf("Erreur: résultats de match indisponibles\n");
        return;
    }

    int n = match->numPlayers;
    int baseGain = (n > 1) ? 100 / (n - 1) : 0;

    printf("========================================\n");
    printf("           MATCH RESULTS\n");
    printf("========================================\n");

    for (int r = 0; r < n; r++) {
        Player * p = match->players[match->results[r]];
        int gain = (n - r - 1) * baseGain;

        printf("%d. ", r + 1);
        displayPlayerMini(p);
        printf("  (+%d)\n", gain);
    }

    printf("========================================\n");
}


// 3.8 Match depuis une file

void launchMatch(t_queue * queue) {
    if (!queue) {
        printf("Erreur: queue NULL\n");
        return;
    }

    Match * match = createMatch();
    if (!match) {
        printf("Erreur allocation match\n");
        return;
    }

    addMatchPlayers(queue, match);

    if (match->numPlayers < 2) {
        printf("Pas assez de joueurs pour lancer un match\n");
        destroyMatch(match);
        return;
    }

    displayMatchInfo(match);
    simulateMatch(match);
    updatePlayerStats(match);
    displayMatchResult(match);
    destroyMatch(match);
}


// 3.9 Match équilibré

void launchBalancedMatch(t_priority_queue * p_queue) {
    if (!p_queue) {
        printf("Erreur: priority queue NULL\n");
        return;
    }

    Match * match = createMatch();
    if (!match) {
        printf("Erreur allocation match\n");
        return;
    }

    while (match->numPlayers < MATCH_MAX_PLAYERS && !isQueueEmpty(p_queue)) {
        Player * p = removeHighestPriority(p_queue);
        if (!p)
            break;

        p->inQueue = 0;
        match->players[match->numPlayers++] = p;
    }

    if (match->numPlayers < 2) {
        printf("Pas assez de joueurs pour lancer un match équilibré\n");
        destroyMatch(match);
        return;
    }

    displayMatchInfo(match);
    simulateMatch(match);
    updatePlayerStats(match);
    displayMatchResult(match);
    destroyMatch(match);
}
