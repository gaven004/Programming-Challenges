/*
 * Where's Waldorf?
 * PC/UVa IDs: 110302/10010
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <ctype.h>

#define BUFFER_LENGTH 200
#define CAPABILITY 51

int getlowerstr(char *s)
{
    char c;
    while ((c = getchar()) != '\n' && c != EOF)
    {
        if (isupper(c))
        {
            c = tolower(c);
        }

        *s = c;
        s++;
    }

    *s = 0;

    return EXIT_SUCCESS;
}

int ismatch(char letters[CAPABILITY][CAPABILITY], int m, int n, char *t, int l, int x, int y, int dx, int dy)
{
    int lx = x + l * dx - dx;
    int ly = y + l * dy - dy;

    if (lx < 0 || lx >= n || ly < 0 || ly >= m)
    {
        return 0;
    }

    t++;

    while (*t)
    {
        x += dx;
        y += dy;

        if (letters[y][x] != *t)
        {
            return 0;
        }

        t++;
    }

    return 1;
}

int findmatch(char letters[CAPABILITY][CAPABILITY], int m, int n, char *t)
{
    int l = strlen(t);
    int x, y, dx, dy;

    for (y = 0; y < m; y++)
    {
        for (x = 0; x < n; x++)
        {
            if (letters[y][x] == *t)
            {
                for (dy = -1; dy < 2; dy++)
                {
                    for (dx = -1; dx < 2; dx++)
                    {
                        if (dx | dy)
                        {
                            if (ismatch(letters, m, n, t, l, x, y, dx, dy))
                            {
                                printf("%d %d\n", y + 1, x + 1);
                                return EXIT_SUCCESS;
                            }
                        }
                    }
                }
            }
        }
    }

    return EXIT_SUCCESS;
}

int main(void)
{
    int cases;
    int m, n;
    int k;
    int i;
    char buff[BUFFER_LENGTH];
    char letters[CAPABILITY][CAPABILITY];

    scanf("%d", &cases);
    getchar(); /* the blank line */
    while (cases--)
    {
        /* initialize */

        /* read data */
        scanf("%d %d", &m, &n);
        getchar(); /* the blank line */
        for (i = 0; i < m; i++)
        {
            getlowerstr(letters[i]);
        }

        scanf("%d", &k);
        getchar(); /* the blank line */

        for (i = 0; i < k; i++)
        {
            getlowerstr(buff);

            /* processing */
            findmatch(letters, m, n, buff);
        }

        if (cases)
        {
            getchar(); /* the blank line */
            putchar('\n');
        }
    }

    return EXIT_SUCCESS;
}
