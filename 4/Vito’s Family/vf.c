/*
 * Vito’s Family
 * PC/UVa IDs: 110401/10041
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define NRELATIVES 500

int numcmp(const void *s, const void *t)
{
    return (*(int *)s - *(int *)t);
}

int main(void)
{
    int cases;
    int r, i, k, m;
    int s[NRELATIVES];
    int d;

    scanf("%d", &cases);
    while (cases--)
    {
        /* initialize */

        /* read data */
        scanf("%d", &r);
        for (i = 0; i < r; i++)
        {
            scanf("%d", &(s[i]));
        }

        /* processing */

        /* find the median */
        qsort(s, r, sizeof(int), numcmp);

        k = r / 2;
        m = s[k];

        /* sum */
        d = 0;
        for (i = 0; i < k; i++)
        {
            d += (m - s[i]);
        }
        for (i = k + 1; i < r; i++)
        {
            d += (s[i] - m);
        }

        /* output */
        printf("%d\n", d);
    }

    return EXIT_SUCCESS;
}
