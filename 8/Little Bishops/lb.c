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

#define MAXN 9
#define MAXK 15

int main() {
    /*
     * 将棋盘分为黑白两块区域，两块区域内的棋子互不攻击
     */

    // black_rows[i]，
    int black_rows[MAXN] = {0, 1, 1, 3, 3, 5, 5, 7, 7};
    int write_rows[MAXN] = {0, 0, 2, 2, 4, 4, 6, 6, 8};

    long long black[MAXN][MAXK] = {}, white[MAXN][MAXK] = {};

    //棋盤分成黑白間隔後，轉 45 度(菱形)
    //row_b[i]: i * i 時，增加的一條黑色的格子數，遞增

    // k = 0时，只有1种方案
    for (int i = 0; i < MAXN; ++i)
        black[i][0] = 1;
    for (int i = 0; i < MAXN; ++i)
        white[i][0] = 1;

    //(row_b[i] - (k - 1): 多的那條黑的有幾格 - 先前已阻擋的位置
    for (int i = 1; i < MAXN; ++i)
        for (int k = 1; k < MAXK; ++k)
            black[i][k] = black[i - 1][k] + black[i - 1][k - 1] * (black_rows[i] - (k - 1));

    for (int i = 2; i < MAXN; ++i)
        for (int k = 1; k < MAXK; ++k)
            white[i][k] = white[i - 1][k] + white[i - 1][k - 1] * (write_rows[i] - (k - 1));


    int n, k;

    while (scanf("%d %d", &n, &k) && n) {
        if (k >= MAXK) {
            puts("0");
            continue;
        }

        long long sum = 0;
        for (int i = 0; i <= k; ++i)
            sum += (black[n][i] * white[n][k - i]);

        printf("%lld\n", sum);
    }
}
