/*
 * Fmt
 *
 * PC/UVa IDs: 110308/848
 */

#include <limits.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BUFFER_LENGTH 1000
#define MAX_CHARS_OF_LINE 72

char c, t;
char buff[BUFFER_LENGTH];
char *pb;
int ll; /* length of current line */
int lw; /* length of current word */
int lb; /* length of current space */

void init()
{
    ll = 0, lw = 0, lb = 0;
    pb = buff;
}

void put_n_space(int n)
{
    int i;

    for (i = 0; i < n; i++)
    {
        putchar(' ');
    }
}

void put_n_char(char *s, int n)
{
    int i;

    for (i = 0; i < n; i++)
    {
        putchar(*s);
        s++;
    }
}

void put_word()
{
    if (lw > MAX_CHARS_OF_LINE)
    {
        if (ll > 0)
        {
            /* put a line break */
            putchar('\n');
        }

        /* put the word containing more than 72 characters */
        put_n_char(buff, lw);
        putchar('\n');

        /* skip space */
        while ((t = getchar()) == ' ')
            ;

        if (t != '\n' && t != EOF)
        {
            ungetc(t, stdin);
        }

        /* reset */
        init();

        if (c == ' ')
        {
            lb = -1;
        }

        return;
    }

    if ((ll + lb + lw) > MAX_CHARS_OF_LINE)
    {
        /* put a line break, remove end spaces */
        putchar('\n');
        put_n_char(buff, lw);

        ll = lw, lw = 0, lb = 0;
        pb = buff;

        return;
    }

    put_n_space(lb);
    put_n_char(buff, lw);

    ll = ll + lb + lw;
    lw = 0, lb = 0;
    pb = buff;
}

int main(void)
{

    init();

    while ((c = getchar()) != EOF)
    {
        switch (c)
        {
        case ' ':
            if (lw > 0)
            {
                put_word();
            }

            lb++;
            break;
        case '\n':
            if (ll == 0 && lw == 0)
            {
                /* a blank or empty line */
                putchar('\n');
                lb = 0;
            }
            else
            {
                if (lw > 0)
                {
                    put_word();
                }

                c = getchar();
                switch (c)
                {
                case EOF:
                    putchar('\n');
                    return EXIT_SUCCESS;
                case ' ':
                    /* followed by a space */
                    putchar('\n');
                    ll = 0, lw = 0, lb = 1;
                    pb = buff;
                    break;
                case '\n':
                    /* followed by another line break */
                    putchar('\n');
                    init();
                    ungetc(c, stdin);
                    break;
                default:
                    lb = 1; /* When a line break is eliminated, it is replaced by a space. */
                    *pb = c;
                    pb++;
                    lw++;
                    break;
                }
            }

            break;
        default:
            *pb = c;
            pb++;
            lw++;
            break;
        }
    }

    /* put the remain chars */
    if (lw > 0)
    {
        put_word();
    }

    return EXIT_SUCCESS;
}
