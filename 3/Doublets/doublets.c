/*
 * Doublets
 * PC/UVa IDs: 110307/10150
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BUFFER_LENGTH 100
#define MAX_LENGTH_OF_WORD 16
#define MAX_NUMBER_OF_WORDS 25143

int readline(char *s)
{
    char c;
    int l = 0;

    while ((c = getchar()) != '\n')
    {
        *s = c;
        s++;
        l++;
    }

    *s = '\0';

    return l;
}

int is_doublet(const char *s, const char *t)
{
    int d = 0;

    while (*s && *t && d < 2)
    {
        if (*s != *t)
        {
            d++;
        }

        s++;
        t++;
    }

    return d == 1;
}

char dict[MAX_LENGTH_OF_WORD][MAX_NUMBER_OF_WORDS][MAX_LENGTH_OF_WORD + 1];
int word_cnt_by_len[MAX_LENGTH_OF_WORD];
char adjacency[MAX_LENGTH_OF_WORD][MAX_LENGTH_OF_WORD][MAX_NUMBER_OF_WORDS];

int main(void)
{
    char buff[BUFFER_LENGTH];
    char word1[BUFFER_LENGTH];
    char word2[BUFFER_LENGTH];

    int cases;
    int i, j, l;

    for (i = 0; i < MAX_LENGTH_OF_WORD; i++)
    {
        word_cnt_by_len[i] = 0;
    }

    while ((l = readline(buff)))
    {
        l--;
        i = word_cnt_by_len[l];
        strcpy(dict[l][i], buff);
        word_cnt_by_len[l] = i + 1;
    }

    for (l = 0; l < MAX_LENGTH_OF_WORD; l++)
    {
        if (word_cnt_by_len[l] > 1)
        {
            qsort(dict[l], word_cnt_by_len[l], MAX_LENGTH_OF_WORD + 1, (int (*)(const void *, const void *))strcmp);

            // for (i = 0; i < word_cnt_by_len[l]; i++)
            // {
            //     puts(dict[l][i]);
            // }

            for (i = 0; i < word_cnt_by_len[l] - 1; i++)
            {
                for (j = i + 1; j < word_cnt_by_len[l]; j++)
                {
                    adjacency[l][i][j] = is_doublet(dict[l][i], dict[l][j]);
                    adjacency[l][j][i] = adjacency[l][i][j];
                }
            }

            // for (i = 0; i < word_cnt_by_len[l]; i++)
            // {
            //     for (j = 0; j < word_cnt_by_len[l]; j++)
            //     {
            //         printf("%d ", adjacency[l][i][j]);
            //     }
            //     putchar('\n');
            // }
        }
    }

    cases = 0;
    while (scanf("%s", word1) != EOF && scanf("%s", word2) != EOF)
    {
        if (cases)
        {
            putchar('\n');
        }
        
        printf("%s %s\n", word1, word2);

        l = strlen(word1);
        if (l != strlen(word2))
        {
            puts("No solution.");
        }

        cases++;
    }

    return EXIT_SUCCESS;
}
