/*
 * Longest Nap
 * PC/UVa IDs: 110404/10191
 */

/*
 * appointments的时间，有可能重叠
 * 例如：
 * 10:36 16:02 Meeting with Morass
 * 10:22 11:30 Meeting with Morass
 * 13:37 16:27 Meeting with Vinit
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define N 100
#define BUFFER_LENGTH 300

int t0_hh = 10, t0_mm = 0, t0 = 0;
int t9_hh = 18, t9_mm = 0, t9 = 8 * 60;

typedef struct
{
    int t1, t2;
} appointment_t;

int cmp(const void *s, const void *t)
{
    return (((appointment_t *)s)->t1 - ((appointment_t *)t)->t1);
}

int get_ts(char h0, char h1, char m0, char m1)
{
    int h, m;

    h = (h0 - '0') * 10 + (h1 - '0');
    m = (m0 - '0') * 10 + (m1 - '0');

    return (h - t0_hh) * 60 + m;
}

int main(void)
{
    int day, s;
    char buff[BUFFER_LENGTH];
    appointment_t appointments[N];

    int i;

    int start, longest_nap, nap, k;

    day = 1;

    while (NULL != fgets(buff, BUFFER_LENGTH, stdin))
    {
        sscanf(buff, "%d", &s);
        for (i = 0; i < s; i++)
        {
            fgets(buff, BUFFER_LENGTH, stdin);
            appointments[i].t1 = get_ts(buff[0], buff[1], buff[3], buff[4]);
            appointments[i].t2 = get_ts(buff[6], buff[7], buff[9], buff[10]);
        }

        qsort(appointments, s, sizeof(appointment_t), cmp);

        start = t0, longest_nap = (appointments[0].t1 - t0);
        k = appointments[0].t2;

        for (i = 1; i < s; i++)
        {
            if (k < appointments[i].t1)
            {
                nap = appointments[i].t1 - k;
                if (nap > longest_nap)
                {
                    longest_nap = nap;
                    start = k;
                }
            }

            if (k < appointments[i].t2)
            {
                k = appointments[i].t2;
            }
        }

        nap = t9 - k;
        if (nap > longest_nap)
        {
            longest_nap = nap;
            start = k;
        }

        if (longest_nap < 60)
        {
            printf("Day #%d: the longest nap starts at %02d:%02d and will last for %d minutes.\n",
                   day, (start / 60) + t0_hh, start % 60, longest_nap);
        }
        else
        {
            printf("Day #%d: the longest nap starts at %02d:%02d and will last for %d hours and %d minutes.\n",
                   day, (start / 60) + t0_hh, start % 60, longest_nap / 60, longest_nap % 60);
        }

        day++;
    }

    return EXIT_SUCCESS;
}