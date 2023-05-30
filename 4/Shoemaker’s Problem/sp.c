/*
 * Shoemaker’s Problem
 * PC/UVa IDs: 110405/10026
 */

#include <stdio.h>
#include <stdlib.h>

#define N 1000

typedef struct {
    int i, t, s;
} job_t;

/*
 * 比较两个工作哪一个优先
 *
 * 先做s工作，罚金为jobs->t * jobt->s
 * 先做t工作，罚金为jobt->t * jobs->s
 * 计算出罚金大的先做
 */
int cmp(const void *s, const void *t) {
    job_t *jobs = (job_t *) s;
    job_t *jobt = (job_t *) t;
    int p1 = jobs->t * jobt->s;
    int p2 = jobt->t * jobs->s;
    return p1 == p2 ? (jobs->i - jobt->i) : p1 - p2;
}

int main(void) {
    int c;
    int n;
    int i;

    job_t jobs[N];

    scanf("%d", &c);
    while (c--) {

        scanf("%d", &n);
        for (i = 0; i < n; ++i) {
            jobs[i].i = i + 1;
            scanf("%d", &(jobs[i].t));
            scanf("%d", &(jobs[i].s));
        }

        qsort(jobs, n, sizeof(job_t), cmp);

        printf("%d", jobs[0].i);
        for (i = 1; i < n; ++i) {
            printf(" %d", jobs[i].i);
        }
        printf("\n");

        if (c) {
            /* The output of two consecutive cases must be separated by a blank line. */
            printf("\n");
        }
    }

    return EXIT_SUCCESS;
}