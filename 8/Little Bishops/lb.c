//
// Created by gaven on 2024/11/19.
//

/*
 * Little Bishops
 * PC/UVa IDs: 110801/861
 */

#include <stdio.h>

#define MAXN 8

int main() {
    const int MAXK = MAXN * 2 - 2;

    /*
     * 将棋盘分为黑白两块区域，两块区域内的棋子互不攻击
     */

    // black_squares[i]，棋盘尺寸，从 i-1 扩大到 i，所增加的黑格数
    int black_squares[MAXN + 1] = {0, 1, 1, 3, 3, 5, 5, 7, 7};
    // write_squares[i]，棋盘尺寸，从 i-1 扩大到 i，所增加的白格数
    int write_squares[MAXN + 1] = {0, 0, 2, 2, 4, 4, 6, 6, 8};

    // black_total[i][k]，white_total[i][k]，棋盘尺寸 (i * i)，在黑、白区域，可放置k个棋子的方案数
    // 用Dynamic Programming，通过组合的方法得到这些数值
    long long black_total[MAXN + 1][MAXK + 1] = {}, white_total[MAXN + 1][MAXK + 1] = {};

    int n, k, i;

    // k = 0时，只有1种方案
    for (i = 0; i <= MAXN; ++i)
        black_total[i][0] = 1;
    for (i = 0; i <= MAXN; ++i)
        white_total[i][0] = 1;

    // black_squares[i] - (k - 1): 多的那條黑的有幾格 - 先前已阻擋的位置
    for (i = 1; i <= MAXN; ++i)
        for (k = 1; k <= MAXK; ++k)
            black_total[i][k] = black_total[i - 1][k] + black_total[i - 1][k - 1] * (black_squares[i] - (k - 1));

    for (i = 2; i <= MAXN; ++i)
        for (k = 1; k <= MAXK; ++k)
            white_total[i][k] = white_total[i - 1][k] + white_total[i - 1][k - 1] * (write_squares[i] - (k - 1));

    while (scanf("%d %d", &n, &k) && n) {
        // n * n 的棋盘，最多只能放置 (2 * n - 2) 个互不攻击的Bishops
        if (k > (2 * n - 2) && n > 1) {
            puts("0");
            continue;
        }

        long long sum = 0;
        for (i = 0; i <= k; ++i)
            sum += (black_total[n][i] * white_total[n][k - i]);

        printf("%lld\n", sum);
    }
}
