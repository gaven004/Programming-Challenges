/*
 * Automated Judge Script
 * PC/UVa IDs: 110305/10188
 */

/*
 * 题目中多少有些歧义，按普通的理解，是每一行的答案去比较，但这里PRESENTATION_ERROR是忽略不同行的
 *
 * 如下面的用命：
 * 3
 * Input Set #1: YES
 * Input Set #2: NO
 * Input Set #3: NO
 * 4
 * 123
 * ABCDE FG
 * hij k
 * lmn
 *
 * 系统的答案是 Presentation·Error
 */

/* 
 * 有处理的方式是合并答案的多行为一行后，再去比较，这样避免换行的麻烦
 */

#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define BUFFER_LENGTH 101
#define MAX_LINES 100

#define ACCEPTED 2
#define PRESENTATION_ERROR 1
#define WRONG_ANSWER 0

int judge(char expected[MAX_LINES][BUFFER_LENGTH], char actual[MAX_LINES][BUFFER_LENGTH], int n, int m)
{
    int i, j;
    int result = ACCEPTED;
    char *pExpected, *pActual;

    i = 0, j = 0;
    pExpected = expected[i], pActual = actual[j];

    while (*pExpected && *pActual)
    {
        if (*pExpected == *pActual)
        {
            pExpected++;
            if (*pExpected == 0)
            {
                i++;
                if (i < n)
                {
                    pExpected = expected[i];
                }
            }

            pActual++;
            if (*pActual == 0)
            {
                j++;
                if (j < m)
                {
                    pActual = actual[j];
                }
            }
        }
        else
        {
            result = PRESENTATION_ERROR;

            if (isnumber(*pExpected) && isnumber(*pActual))
            {
                return WRONG_ANSWER;
            }

            if (!isnumber(*pExpected))
            {
                pExpected++;

                if (*pExpected == 0)
                {
                    i++;

                    if (i < n)
                    {
                        pExpected = expected[i];
                    }
                }
            }

            if (!isnumber(*pActual))
            {
                pActual++;

                if (*pActual == 0)
                {
                    j++;

                    if (j < m)
                    {
                        pActual = actual[j];
                    }
                }
            }
        }
    }

    /*
     * Has more lines in correct answer
     */
    if (*pExpected)
    {
        result = PRESENTATION_ERROR;

        while (*pExpected)
        {
            if (isnumber(*pExpected))
            {
                return WRONG_ANSWER;
            }

            pExpected++;
            if (*pExpected == 0)
            {
                i++;
                if (i < n)
                {
                    pExpected = expected[i];
                }
            }
        }
    }

    /*
     * Has more lines in actual
     */
    if (*pActual)
    {
        result = PRESENTATION_ERROR;

        while (*pActual)
        {
            if (isnumber(*pActual))
            {
                return WRONG_ANSWER;
            }

            pActual++;
            if (*pActual == 0)
            {
                j++;
                if (j < m)
                {
                    pActual = actual[j];
                }
            }
        }
    }

    return result;
}

int main(void)
{
    int x = 1;
    int n, m;
    int i;
    char buff[BUFFER_LENGTH];
    char expected[MAX_LINES][BUFFER_LENGTH];
    char actual[MAX_LINES][BUFFER_LENGTH];

    for (fgets(buff, BUFFER_LENGTH, stdin), sscanf(buff, "%d", &n);
         n;
         fgets(buff, BUFFER_LENGTH, stdin), sscanf(buff, "%d", &n))
    {
        /* read data */
        for (i = 0; i < n; i++)
        {
            fgets(expected[i], BUFFER_LENGTH, stdin);
        }

        fgets(buff, BUFFER_LENGTH, stdin), sscanf(buff, "%d", &m);
        for (i = 0; i < m; i++)
        {
            fgets(actual[i], BUFFER_LENGTH, stdin);
        }

        /* processing */
        i = judge(expected, actual, n, m);

        /* output */
        switch (i)
        {
        case ACCEPTED:
            printf("Run #%d: Accepted\n", x);
            break;
        case PRESENTATION_ERROR:
            printf("Run #%d: Presentation Error\n", x);
            break;
        case WRONG_ANSWER:
            printf("Run #%d: Wrong Answer\n", x);
            break;
        default:
            break;
        }

        x++;
    }

    return EXIT_SUCCESS;
}
