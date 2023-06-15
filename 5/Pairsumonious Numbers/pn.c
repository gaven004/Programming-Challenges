/*
 * Pairsumonious Numbers
 * PC/UVa IDs: 110508/10202
 */

#include <stdio.h>
#include <stdlib.h>

#define MAXN 10
#define MAXL 46 /* MAXN * (MAXN - 1) / 2 + 1 */

int cmp(const void *s, const void *t) {
    return *(int *) s - *(int *) t;
}

void process_solution(int x[MAXN], int n) {
    int i;
    for (i = 1; i < n; i++) {
        printf("%d ", x[i]);
    }
    printf("%d\n", x[i]);
}

void process_no_solution() {
    printf("Impossible\n");
}

int is_a_solution(int sum[MAXL], int x[MAXN], int n, int l, int k) {
    int i, j, m, s;
    int flag[l];

    flag[1] = flag[2] = 1;
    for (i = 3; i <= l; i++) {
        flag[i] = 0;
    }

    x[1] = (sum[1] + sum[2] - sum[k]) / 2;
    if ((x[1] + x[1]) != (sum[1] + sum[2] - sum[k])) {
        /* 不能整除，非可行解 */
        return 0;
    }

    x[2] = sum[1] - x[1], x[3] = sum[2] - x[1], flag[k] = 1;

    for (i = 4; i <= n; ++i) {
        m = ((i - 1) + (n - 1)) * (n - i + 1) / 2;
        m = l - m + 1;
        for (j = 3; j <= m; ++j) {
            /* 寻找当前最小的未被占用的数 */
            if (!flag[j]) {
                break;
            }
        }

        x[i] = sum[j] - x[1], flag[j] = 1;

        for (j = 2; j < i; ++j) {
            /* 与之前求出的x，计算和，并标记占用 */
            s = x[i] + x[j];

            for (m = 3; m <= l; ++m) {
                if (!flag[m] && s == sum[m]) {
                    flag[m] = 1;
                    break;
                }
            }

            if (l < m) {
                /* 若sum数列中，未有对应的值，则表明不是可行解 */
                return 0;
            }
        }
    }

    return 1;
}

void solve(int sum[MAXL], int x[MAXN], int n, int l) {
    int i;

    /*
     * 由于确定有 x[1] + x[2] = sum[1], x[1] + x[3] = sum[2]
     * 只要寻找到 x[2] + x[3] 的值，则可以求出x[1], x[2], x[3]
     * sum[3]...sum[n] 是 x[2] + x[3] 的候选值，
     * 从sum[n+1]开始，则全部大于 x[2] + x[3]
     * 下面枚举这些候选值
     */
    for (i = 3; i <= n; ++i) {
        if (is_a_solution(sum, x, n, l, i)) {
            process_solution(x, n);
            return;
        }
    }

    process_no_solution();
}

int main() {
    int n, i, l;
    int sum[MAXL];
    int x[MAXN];

    while (scanf("%d", &n) != EOF) {
        l = n * (n - 1) / 2;
        for (i = l; i > 0; i--) {
            scanf("%d", &(sum[i]));
        }

        qsort(sum + 1, l, sizeof(int), cmp);

        solve(sum, x, n, l);
    }
}