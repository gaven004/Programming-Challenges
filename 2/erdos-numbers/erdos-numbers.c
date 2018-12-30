/*
 * Erd¨os Numbers
 * PC/UVa IDs: 110206/10044
 */

#include <limits.h>
#include <stdio.h>
#include <string.h>
#include <time.h>

#define MAX_NUMBER_OF_AUTHORS 10000
#define MAX_LENGTH_OF_NAME 101
#define BUFFER_LENGTH 10001

int nAuthors;
char authors[MAX_NUMBER_OF_AUTHORS][MAX_LENGTH_OF_NAME];
int graph[MAX_NUMBER_OF_AUTHORS][MAX_NUMBER_OF_AUTHORS];
int distance[MAX_NUMBER_OF_AUTHORS], visited[MAX_NUMBER_OF_AUTHORS];

int index_of(const char *name) {
  int i;

  for (i = 0; i < nAuthors; i++) {
    if (!strcmp(authors[i], name)) {
      return i;
    }
  }

  return -1;
}

int put(const char *name) {
  int i;

  i = index_of(name);

  if (i >= 0) {
    return i;
  }

  strcpy(authors[nAuthors], name);

  return nAuthors++;
}

void add_authors(char *buff) {
  char name[MAX_LENGTH_OF_NAME], *ps, *pt;
  int f, i, j, k, n, a[MAX_NUMBER_OF_AUTHORS];

  ps = buff, pt = name, n = f = 0;
  while (*ps != ':') {
    if (*ps == ',') {
      if (f) {
        f = 0, *pt = '\0';
        k = put(name), a[n++] = k;
        pt = name, ps += 2;
      } else {
        f = 1, *pt++ = *ps++;
      }
    } else {
      *pt++ = *ps++;
    }
  }

  *pt = '\0', k = put(name), a[n++] = k;

  for (i = 0; i < n - 1; i++) {
    for (j = i + 1; j < n; j++) {
      graph[a[i]][a[j]] = graph[a[j]][a[i]] = 1;
    }
  }
}

void calculate() {
  int i, v, current, shortest;

  distance[0] = 0, visited[0] = 0;
  for (i = 1; i < nAuthors; i++) {
    distance[i] = INT_MAX, visited[i] = 0;
  }

  current = 0;
  while (!visited[current]) {
    for (i = 0; i < nAuthors; i++) {
      if (graph[current][i]) {
        if (distance[i] > distance[current] + 1) {
          distance[i] = distance[current] + 1;
        }
      }
    }

    visited[current] = 1;

    shortest = INT_MAX;
    for (i = 1; i < nAuthors; i++) {
      if (!visited[i] && distance[i] < shortest) {
        current = i, shortest = distance[i];
      }
    }

    if (shortest == INT_MAX) {
      break;
    }
  }
}

void trim(char *buff) {
  while (*buff) {
    if (*buff == '\n') {
      *buff = 0;
      return;
    }
    buff++;
  }
}

int main() {
  clock_t start, end;

  int scenarios, P, N, en;
  int s, i, j, k, v;
  char buff[BUFFER_LENGTH];

  start = clock();

  strcpy(authors[0], "Erdos, P.");

  for (scanf("%d", &scenarios), s = 1; s <= scenarios; s++) {
    nAuthors = 1;

    for (i = 0; i < MAX_NUMBER_OF_AUTHORS; i++) {
      for (j = 0; j < MAX_NUMBER_OF_AUTHORS; j++) {
        graph[i][j] = 0;
      }
    }

    scanf("%d %d", &P, &N), gets(buff);
    for (i = 0; i < P; i++) {
      gets(buff);
      add_authors(buff);
    }

    calculate();

    printf("Scenario %d\n", s);
    for (i = 0; i < N; i++) {
      gets(buff);

      if ((k = index_of(buff)) >= 0 && (v = distance[k]) < INT_MAX) {
        printf("%s %d\n", buff, v);
      } else {
        printf("%s infinity\n", buff);
      }
    }
  }

  end = clock();
	printf("\nElapsed: %ld\n", end - start);

  return 0;
}
