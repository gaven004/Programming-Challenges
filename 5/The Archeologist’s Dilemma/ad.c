/*
 * The Archeologist’s Dilemma
 * PC/UVa IDs: 110503/701
 */

/*
 * 题目用数学表述：给定N，求一个E，使得N * 10 ^ l ≤ 2 ^ E < (N + 1) * 10 ^ l，l > N的位数。
 * 转换成：log2(N) + l * log2(10) ≤ E < log2(N + 1) + l * log2(10)，对l做枚举，求E
 * 至于l的上边界，似乎题中没有给定
 */

/*
 * 在onlinejudge，程序以ANSI C提交，得到Time limit exceeded
 * 而使用C++11提交，则是Accepted，时间还是0.000
 * 估计是一些类型转换的问题，没有深研，确认算法没问题而已
 */

#include <stdio.h>
#include <math.h>

int count(unsigned int n) {
    int l = 0;
    while (n != 0) {
        n = n / 10;
        ++l;
    }
    return l;
}

int main() {
    unsigned int n;
    double p, q, t, base, c, f;
    int l;

    base = log2(10);

    while (scanf("%u", &n) != EOF) {
        p = log2(n);
        q = log2(n + 1);
        l = count(n) + 1;

        while (l < 2147483647) {
            t = l * base;
            c = ceil(p + t);
            f = (q + t);

            if (c < f) {
                break;
            }

            l++;
        }

        if (l == 2147483647) {
            printf("no power of 2\n");
        } else {
            printf("%d\n", (int) c);
        }
    }
}
