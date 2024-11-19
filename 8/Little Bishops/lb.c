//
// Created by gaven on 2024/11/19.
//

/*
 * Little Bishops
 * PC/UVa IDs: 110801/861
 */

/*
 * 如何处理对称图形？？
 */

#include <stdio.h>

#define MAXN 8

void print(int src[][MAXN], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            printf("%d ", src[i][j]);
        }
        printf("\n");
    }
    printf("\n");
}

void cp(int src[][MAXN], int dest[][MAXN], int n) {
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            dest[i][j] = src[i][j];
        }
    }
}

void put(int src[][MAXN], int n, int i0, int j0) {
    int i, j, di, dj;

    src[i0][j0] = 1;

    di = -1, dj = -1;
    i = i0 + di, j = j0 + dj;
    while (i >= 0 && j >= 0) {
        src[i][j] = 1;
        i += di, j += dj;
    }

    di = -1, dj = +1;
    i = i0 + di, j = j0 + dj;
    while (i >= 0 && j < n) {
        src[i][j] = 1;
        i += di, j += dj;
    }

    di = +1, dj = +1;
    i = i0 + di, j = j0 + dj;
    while (i < n && j < n) {
        src[i][j] = 1;
        i += di, j += dj;
    }

    di = +1, dj = -1;
    i = i0 + di, j = j0 + dj;
    while (i < n && j >= 0) {
        src[i][j] = 1;
        i += di, j += dj;
    }
}

long long solve(int n, int k, int src[][MAXN]) {
    long long sum = 0;

    if (k == 0) {
        return 1;
    }

    for (int i = 0; i < n; i++) {
        for (int j = 0; j < n; j++) {
            if (src[i][j] == 0) {
                int tmp[MAXN][MAXN];
                cp(src, tmp, n);
                put(tmp, n, i, j);
                print(tmp, n);
                sum += solve(n, k - 1, tmp);
            }
        }
    }

    return sum;
}

int main() {
    int n, k;
    int board[MAXN][MAXN];

    scanf("%d %d", &n, &k);
    while (n) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < n; j++) {
                board[i][j] = 0;
            }
        }
        printf("%lld\n", solve(n, k, board));
        scanf("%d %d", &n, &k);
    }
}
