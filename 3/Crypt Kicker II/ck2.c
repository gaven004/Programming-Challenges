/*
 * Crypt Kicker II
 * PC/UVa IDs: 110304/850
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_LENGTH 100
#define MAX_ROWS 100

char *readline(char *s)
{
    char c;
    char *ps = s;

    while ((c = getchar()) != EOF && c != '\n')
    {
        *ps = c;
        ps++;
    }

    *ps = '\0';

    if (c != EOF || ps > s)
    {
        return ps;
    }

    return NULL;
}

int initmappping(char m[])
{
    int i;
    for (i = 'a'; i <= 'z'; i++)
    {
        m[i] = 0;
    }

    m[' '] = ' ';

    return EXIT_SUCCESS;
}

int decrypt(char *key, char *data, char mapping[])
{
    while (*key && *data)
    {
        if (mapping[*data])
        {
            if (mapping[*data] != *key)
            {
                return 0;
            }
        }
        else
        {
            mapping[*data] = *key;
        }
        key++, data++;
    }

    if (*key == 0 && *data == 0)
    {
        return 1;
    }

    return 0;
}

int main(void)
{
    int cases;
    char buff[BUFFER_LENGTH];

    char key[] = "the quick brown fox jumps over the lazy dog";

    char data[MAX_ROWS][BUFFER_LENGTH];
    char mapping[128];

    int done, rows, i;
    char *ps;

    fgets(buff, BUFFER_LENGTH, stdin), sscanf(buff, "%d", &cases);
    fgets(buff, BUFFER_LENGTH, stdin); /* the blank line */
    while (cases--)
    {
        /* initialize */
        done = 0;

        /* read data */
        for (rows = 0; readline(data[rows]) != NULL && strcmp(data[rows], ""); rows++)
        {
        }

        /* processing */
        for (i = 0; i < rows; i++)
        {
            initmappping(mapping);

            done = decrypt(key, data[i], mapping);

            if (done)
            {
                break;
            }
        }

        /* output */
        if (done)
        {
            for (i = 0; i < rows; i++)
            {
                ps = data[i];
                while (*ps)
                {
                    putchar(mapping[*ps]);
                    ps++;
                }
                putchar('\n');
            }
        }
        else
        {
            puts("No solution.");
        }

        if (cases)
        {
            putchar('\n');
        }
    }

    return EXIT_SUCCESS;
}
