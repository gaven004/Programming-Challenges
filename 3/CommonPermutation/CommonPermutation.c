/*
 * Common Permutation
 * PC/UVa IDs: 110303/10252
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define BUFFER_LENGTH 1001

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

int cmpfunc(const void *a, const void *b)
{
    return (*(char *)a - *(char *)b);
}

int main(void)
{
    char a[BUFFER_LENGTH];
    char b[BUFFER_LENGTH];
    char x[BUFFER_LENGTH];

    while (readline(a) != NULL &&
           readline(b) != NULL)
    {
        if (*a == '\0' || *b == '\0')
        {
            putchar('\n');
            continue;
        }

        qsort(a, strlen(a), sizeof(char), cmpfunc);
        qsort(b, strlen(b), sizeof(char), cmpfunc);

        char *pa = a;
        char *pb = b;
        char *px = x;

        while (*pa && *pb)
        {
            if (*pa > *pb)
            {
                pb++;
            }
            else if (*pb > *pa)
            {
                pa++;
            }
            else
            {
                *px = *pa;
                pa++;
                pb++;
                px++;
            }
        }

        *px = '\0';

        puts(x);
    }

    return EXIT_SUCCESS;
}