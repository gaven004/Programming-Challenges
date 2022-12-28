/*
 * Bridge
 * PC/UVa IDs: 110403/10037
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define N 1000

int numcmp(const void *s, const void *t)
{
    return (*(int *)s - *(int *)t);
}

int main(void)
{
    int c;
    int n, m;
    int i;
    int times[N];
    int total;

    scanf("%d", &c);
    while (c--)
    {
        scanf("%d", &n);
        for (i = 0; i < n; i++)
        {
            scanf("%d", &(times[i]));
        }

        qsort(times, n, sizeof(int), numcmp);

        m = n;
        total = 0;
        while (n)
        {
            if (n > 3)
            {
                if ((times[0] + times[n - 2]) > (times[1] + times[1]))
                {
                    total += times[1];
                    total += times[0];
                    total += times[n - 1];
                    total += times[1];
                }
                else
                {
                    total += times[n - 1];
                    total += times[0];
                    total += times[n - 2];
                    total += times[0];
                }

                n = n - 2;
            }
            else if (n == 3)
            {
                total += times[1];
                total += times[0];
                total += times[2];
                n = 0;
            }
            else
            {
                if (n > 1)
                {
                    total += times[1];
                }
                else
                {
                    total += times[0];
                }
                n = 0;
            }
        }

        printf("%d\n", total);

        n = m;
        while (n)
        {
            if (n > 3)
            {
                if ((times[0] + times[n - 2]) > (times[1] + times[1]))
                {
                    printf("%d %d\n", times[0], times[1]);
                    printf("%d\n", times[0]);
                    printf("%d %d\n", times[n - 2], times[n - 1]);
                    printf("%d\n", times[1]);
                }
                else
                {
                    printf("%d %d\n", times[0], times[n - 2]);
                    printf("%d\n", times[0]);
                    printf("%d %d\n", times[0], times[n - 1]);
                    printf("%d\n", times[0]);
                }

                n = n - 2;
            }
            else if (n == 3)
            {
                printf("%d %d\n", times[0], times[1]);
                printf("%d\n", times[0]);
                printf("%d %d\n", times[0], times[2]);
                n = 0;
            }
            else
            {
                if (n > 1)
                {
                    printf("%d %d\n", times[0], times[1]);
                }
                else
                {
                    printf("%d\n", times[0]);
                }
                n = 0;
            }
        }

        if (c)
        {
            putchar('\n');
        }
    }

    return EXIT_SUCCESS;
}