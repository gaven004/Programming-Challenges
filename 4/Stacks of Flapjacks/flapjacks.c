/*
 * Stacks of Flapjacks
 * PC/UVa IDs: 110402/120
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define N 31

int flip(int d[N], int k)
{
    int t;
    int i = 1;
    while (i < k)
    {
        t = d[k];
        d[k] = d[i];
        d[i] = t;

        i++, k--;
    }

    return EXIT_SUCCESS;
}

int echo(int flapjacks[N], int n)
{
    int i;

    for (i = 1; i < n; i++)
    {
        printf("%d ", flapjacks[i]);
    }
    printf("%d\n", flapjacks[i]);

    return EXIT_SUCCESS;
}

int main(void)
{
    int c;
    int n;
    int i, j, k, m;
    int d[N];

    while (1)
    {
        n = 1;
        while (1)
        {
            scanf("%d", &(d[n]));
            c = getchar();
            if (c == '\n' || c == EOF)
            {
                break;
            }
            n++;
        }

        /* echo the original stack */
        echo(d, n);

        for (i = n; i > 0; i--)
        {
            m = d[i];
            k = i;
            for (j = i - 1; j > 0; j--)
            {
                if (m < d[j])
                {
                    m = d[j];
                    k = j;
                }
            }

            if (k < i)
            {
                if (1 < k)
                {
                    flip(d, k);
                    printf("%d ", n - k + 1);
                }

                flip(d, i);
                printf("%d ", n - i + 1);
            }
        }

        printf("0\n");

        c = getchar();
        if (c == EOF)
        {
            break;
        }
        else
        {
            ungetc(c, stdin);
        }
    }

    return EXIT_SUCCESS;
}