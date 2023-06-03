/*
 * CDVII
 * PC/UVa IDs: 110406/10138
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#define N 1000
#define N_HOURS 24
#define LENGTH_OF_LICENSE_NUMBER 30

typedef struct {
    char license_number[LENGTH_OF_LICENSE_NUMBER];
    int month, date, hour, minute;
    int time_stamp;
    int enter_or_exit;
    int location;
} photo_record_t;

int cmp(const void *s, const void *t) {
    int r;
    photo_record_t *ptr_s = (photo_record_t *) s;
    photo_record_t *ptr_t = (photo_record_t *) t;

    r = strcmp(ptr_s->license_number, ptr_t->license_number);
    if (r) {
        return r;
    }

    /* All dates will be within a single month */

    r = ptr_s->date - ptr_t->date;
    if (r) {
        return r;
    }

    r = ptr_s->hour - ptr_t->hour;
    if (r) {
        return r;
    }

    r = ptr_s->minute - ptr_t->minute;
    if (r) {
        return r;
    }

    return ptr_s->enter_or_exit - ptr_t->enter_or_exit;
}

int main(void) {
    int c;
    int n;
    int i;
    int km;

    char buff[LENGTH_OF_LICENSE_NUMBER];

    int tolls[N_HOURS];
    photo_record_t records[N];
    int total;

    scanf("%d", &c);
    while (c--) {
        for (i = 0; i < N_HOURS; ++i) {
            scanf("%d", &(tolls[i]));
        }
        /* 处理换行 */
        getchar();

        n = 0;
        while ((i = getchar()) != EOF && i != '\n') {
            ungetc(i, stdin);
            scanf("%s %d:%d:%d:%d %s %d", records[n].license_number,
                  &(records[n].month), &(records[n].date), &(records[n].hour), &(records[n].minute),
                  buff, &(records[n].location));
            records[n].enter_or_exit = (buff[1] == 'x');
            n++;
            getchar();
        }

        qsort(records, n, sizeof(photo_record_t), cmp);

        total = 0;

        strcpy(buff, records[0].license_number);
        for (i = 1; i < n; ++i) {
            if (strcmp(buff, records[i].license_number)) {
                if (total > 0) {
                    total += 200;
                    printf("%s $%d.%02d\n", buff, total / 100, total % 100);
                }

                total = 0;
                strcpy(buff, records[i].license_number);
            } else {
                /* Unpaired “enter” and “exit” records are ignored. */
                if (records[i - 1].enter_or_exit == 0 && records[i].enter_or_exit == 1) {
                    km = (records[i - 1].location > records[i].location) ?
                         (records[i - 1].location - records[i].location) :
                         (records[i].location - records[i - 1].location);
                    total += (100 + km * tolls[records[i - 1].hour]);
                }
            }
        }

        if (total > 0) {
            total += 200;
            printf("%s $%d.%02d\n", buff, total / 100, total % 100);
        }

        if (c) {
            printf("\n");
        }
    }

    return EXIT_SUCCESS;
}