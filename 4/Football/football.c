/*
 * Football (aka Soccer)
 * PC/UVa IDs: 110408/10194
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_LENGTH 300

#define LENGTH_OF_TOURNAMENT_NAME 102
#define LENGTH_OF_TEAM_NAME 32

#define N_TEAMS 30

typedef struct {
    int index, points, games, wins, ties, losses, goal_difference, goals, goals_against;
} team_t;

char teams[N_TEAMS][LENGTH_OF_TEAM_NAME];
team_t tables[N_TEAMS];

int cmp(const void *s, const void *t) {
    int r;

    team_t *ptr_s = (team_t *) s;
    team_t *ptr_t = (team_t *) t;

    r = ptr_t->points - ptr_s->points;
    if (r) {
        return r;
    }

    r = ptr_t->wins - ptr_s->wins;
    if (r) {
        return r;
    }

    r = ptr_t->goal_difference - ptr_s->goal_difference;
    if (r) {
        return r;
    }

    r = ptr_t->goals - ptr_s->goals;
    if (r) {
        return r;
    }

    r = ptr_s->games - ptr_t->games;
    if (r) {
        return r;
    }

    return strcasecmp(teams[ptr_s->index], teams[ptr_t->index]);
}

int main(void) {
    int n, t, g;
    char buff[BUFFER_LENGTH];

    char team1[LENGTH_OF_TEAM_NAME], team2[LENGTH_OF_TEAM_NAME];
    int goal1, goal2;

    int i, k1, k2;
    char *ptrs, *ptrt;
    char **ptrk;

    fgets(buff, BUFFER_LENGTH, stdin);
    sscanf(buff, "%d", &n);

    while (n) {
        fgets(buff, LENGTH_OF_TOURNAMENT_NAME, stdin);
        printf("%s", buff);

        fgets(buff, BUFFER_LENGTH, stdin);
        sscanf(buff, "%d", &t);

        for (i = 0; i < t; i++) {
            fgets(teams[i], LENGTH_OF_TEAM_NAME, stdin);
            teams[i][strlen(teams[i]) - 1] = '\0';
        }

        qsort(teams, t, LENGTH_OF_TEAM_NAME, (int (*)(const void *, const void *)) strcmp);

        for (i = 0; i < t; i++) {
            tables[i].index = i;
            tables[i].points = 0;
            tables[i].games = 0;
            tables[i].wins = 0;
            tables[i].ties = 0;
            tables[i].losses = 0;
            tables[i].goal_difference = 0;
            tables[i].goals = 0;
            tables[i].goals_against = 0;
        }

        fgets(buff, BUFFER_LENGTH, stdin);
        sscanf(buff, "%d", &g);

        for (i = 0; i < g; i++) {
            fgets(buff, BUFFER_LENGTH, stdin);
            goal1 = 0, goal2 = 0;

            ptrs = buff, ptrt = team1;
            while (*ptrs != '#') {
                *ptrt = *ptrs;
                ptrs++, ptrt++;
            }
            *ptrt = '\0';
            ptrs++;

            while (*ptrs != '@') {
                goal1 = goal1 * 10 + (*ptrs - '0');
                ptrs++;
            }
            ptrs++;

            while (*ptrs != '#') {
                goal2 = goal2 * 10 + (*ptrs - '0');
                ptrs++;
            }
            ptrs++;

            ptrt = team2;
            while (*ptrs != '\n' && *ptrs != '\0') {
                *ptrt = *ptrs;
                ptrs++, ptrt++;
            }
            *ptrt = '\0';

            ptrk = bsearch(team1, teams, t, LENGTH_OF_TEAM_NAME, (int (*)(const void *, const void *)) strcmp);
            k1 = ((char (*)[32]) ptrk - teams);

            ptrk = bsearch(team2, teams, t, LENGTH_OF_TEAM_NAME, (int (*)(const void *, const void *)) strcmp);
            k2 = ((char (*)[32]) ptrk - teams);

            tables[k1].games++;
            tables[k2].games++;

            if (goal1 > goal2) {
                tables[k1].points += 3;
                tables[k1].wins++;
                tables[k2].losses++;
            } else if (goal1 == goal2) {
                tables[k1].points++;
                tables[k2].points++;
                tables[k1].ties++;
                tables[k2].ties++;
            } else {
                tables[k2].points += 3;
                tables[k2].wins++;
                tables[k1].losses++;
            }

            tables[k1].goals += goal1;
            tables[k1].goals_against += goal2;

            tables[k2].goals += goal2;
            tables[k2].goals_against += goal1;
        }

        for (i = 0; i < t; i++) {
            tables[i].goal_difference = tables[i].goals - tables[i].goals_against;
        }

        qsort(tables, t, sizeof(team_t), cmp);

        for (i = 0; i < t; i++) {
            printf("%d) %s %dp, %dg (%d-%d-%d), %dgd (%d-%d)\n",
                   i + 1, teams[tables[i].index], tables[i].points, tables[i].games,
                   tables[i].wins, tables[i].ties, tables[i].losses,
                   tables[i].goal_difference, tables[i].goals, tables[i].goals_against);
        }

        n--;
        if (n) {
            printf("\n");
        }
    }
    return EXIT_SUCCESS;
}