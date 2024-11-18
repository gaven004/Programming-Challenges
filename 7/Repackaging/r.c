//
// Created by gaven on 2024/11/18.
//

/*
 * Repackaging
 * PC/UVa IDs: 110708/10089
 */

#include <stdio.h>

#define MAXN 1000

int N;
int n[MAXN], s1[MAXN], s2[MAXN], s3[MAXN];

/*
 * sum(n[i] * s1[i]) = sum(n[i] * s2[i]) = sum(n[i] * s3[i]), 0 ≤ n[i], 1 ≤ i ≤ N
 */

int main() {
    int *ps1, *ps2, *ps3;

    scanf("%d", &N);
    while (N) {
        ps1 = s1, ps2 = s2, ps3 = s3;

        for (int i = 0; i < N; i++) {
            scanf("%d %d %d", ps1, ps2, ps3);
            ps1++, ps2++, ps3++;
        }


        scanf("%d", &N);
    }
}
