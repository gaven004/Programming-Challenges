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

void readdata(char *buff, int lines)
{
    char c;

    while (lines && (c = getchar()) != EOF)
    {
        *buff = c;
        buff++;

        if (c == '\n')
        {
            lines--;
        }
    }

    *buff = '\0';
}

int judge(char *expected, char *actual)
{
    int result = ACCEPTED;

    while (*expected && *actual)
    {
        if (*expected == *actual)
        {
            expected++;
            actual++;
        }
        else
        {
            result = PRESENTATION_ERROR;

            if (isdigit(*expected) && isdigit(*actual))
            {
                return WRONG_ANSWER;
            }

            if (!isdigit(*expected))
            {
                expected++;
            }

            if (!isdigit(*actual))
            {
                actual++;
            }
        }
    }

    if (*expected)
    {
        result = PRESENTATION_ERROR;

        while (*expected)
        {
            if (isdigit(*expected))
            {
                return WRONG_ANSWER;
            }
            expected++;
        }
    }

    if (*actual)
    {
        result = PRESENTATION_ERROR;

        while (*actual)
        {
            if (isdigit(*actual))
            {
                return WRONG_ANSWER;
            }
            actual++;
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
    char expected[MAX_LINES * BUFFER_LENGTH];
    char actual[MAX_LINES * BUFFER_LENGTH];

    for (scanf("%d", &n), getchar();
         n;
         scanf("%d", &n), getchar())
    {
        /* read data */
        readdata(expected, n);

        scanf("%d", &m), getchar();
        readdata(actual, m);

        /* processing */
        i = judge(expected, actual);

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
