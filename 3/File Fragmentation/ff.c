/*
 * File Fragmentation
 * PC/UVa IDs: 110306/10132
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

#define BUFFER_LENGTH 300
#define MAX_NUMBER_OF_FILES 150

int finished = 0;

int cmp(const char *s, const char *t)
{
    int ls = strlen(s), lt = strlen(t);
    return ls == lt ? strcmp(s, t) : ls - lt;
}

int concat(char *dest, char fragments[MAX_NUMBER_OF_FILES * 2][BUFFER_LENGTH], int i, int j)
{
    if (j > 0)
    {
        strcpy(dest, fragments[i]);
        strcat(dest, fragments[j]);
    }
    else
    {
        strcpy(dest, fragments[-j]);
        strcat(dest, fragments[i]);
    }

    return EXIT_SUCCESS;
}

int is_a_solution(char fragments[MAX_NUMBER_OF_FILES * 2][BUFFER_LENGTH],
                  int length_of_fragments[MAX_NUMBER_OF_FILES * 2],
                  int solution[MAX_NUMBER_OF_FILES * 2],
                  int fragments_count,
                  int file_size,
                  int k,
                  int d)
{
    int i;

    printf("is_a_solution: fragments_count: %d, file_size: %d, k: %d, d: %d\n", fragments_count, file_size, k, d);

    for (i = 0; i < fragments_count; i++)
    {
        if (solution[i] == fragments_count)
        {
            return 0;
        }
    }

    finished = 1;
    return 1;
}

int process(char fragments[MAX_NUMBER_OF_FILES * 2][BUFFER_LENGTH], /* 碎片数据 */
            int length_of_fragments[MAX_NUMBER_OF_FILES * 2],       /* 碎片长度 */
            int solution[MAX_NUMBER_OF_FILES * 2],                  /* 解，若solution[k] = v，则 fragments[k] 和 fragments[v] 拼接在一起为一组候选解 */
            int fragments_count,                                    /* 碎片数 */
            int file_size,                                          /* 文件长度 */
            int k,                                                  /* 第K块碎片 */
            int d /* 碎片拼接方向，为1时表示第K块碎片放在前面，为-1时表示第K块碎片放在后面 */)
{
    int i, l;

    char expected[BUFFER_LENGTH];
    char actual[BUFFER_LENGTH];

    printf("process: fragments_count: %d, file_size: %d, k: %d, d: %d\n", fragments_count, file_size, k, d);

    puts("是否完整解");
    /* 是否完整解 */
    if (is_a_solution(fragments, length_of_fragments, solution, fragments_count, file_size, k, d))
    {
        return 1;
    }

    l = length_of_fragments[k];

    if (k > 0)
    {
        concat(expected, fragments, 0, solution[0]);
    }

    puts("构建当前K下的可行解");

    /* 构建当前K下的可行解 */
    for (i = fragments_count - 1; i > k; i--)
    {
        puts("碎片合并后长度是否符合");
        /* 碎片合并后长度是否符合 */
        if (l + length_of_fragments[i] < file_size)
        {
            break;
        }

        puts("碎片是否已使用");
        /* 碎片是否已使用 */
        if (solution[i] < fragments_count)
        {
            continue;
        }

        if (k > 0)
        {
            /* 比较当前的候选解是否与上一步解得到的文件一致 */

            concat(actual, fragments, k, d * i);

            if (strcmp(expected, actual))
            {
                continue;
            }
        }

        puts("测试条件通过，得到一个可行候选解");
        /* 测试条件通过，得到一个可行候选解 */
        if (d > 0)
        {
            solution[k] = i;
            solution[i] = -k;
        }
        else
        {
            solution[k] = -i;
            solution[i] = k;
        }

        puts("递归寻找下一层的解");
        /* 递归寻找下一层的解 */
        process(fragments, length_of_fragments, solution, fragments_count, file_size, k + 1, 1);

        if (finished)
        {
            puts("若得到完整解，则可退出");
            /* 若得到完整解，则可退出 */
            return 1;
        }

        /* 当前解下，不能得到完整的解，则恢复状态，尝试下一个可行候选解 */
        solution[i] = fragments_count;
        solution[k] = fragments_count;
    }

    if (d > 0)
    {
        puts("在当前情况下，碎片K放在组合中的前面无法得到完整解，尝试放在后面");
        /* 在当前情况下，碎片K放在组合中的前面无法得到完整解，尝试放在后面 */
        process(fragments, length_of_fragments, solution, fragments_count, file_size, k, -1);
    }

    puts("在当前情况下，碎片K，放在组合的前面和后面，都无法得到完整解，回退一步，在上一层的下一个可行候选解再开始");
    /* 在当前情况下，碎片K，放在组合的前面和后面，都无法得到完整解，回退一步，在上一层的下一个可行候选解再开始 */
    return 0;
}

int main(void)
{
    int cases;
    char buff[BUFFER_LENGTH];

    char fragments[MAX_NUMBER_OF_FILES * 2][BUFFER_LENGTH];
    int length_of_fragments[MAX_NUMBER_OF_FILES * 2];
    int solution[MAX_NUMBER_OF_FILES * 2];

    int i, fragments_count, file_size;

    fgets(buff, BUFFER_LENGTH, stdin), sscanf(buff, "%d", &cases);
    fgets(buff, BUFFER_LENGTH, stdin); /* the blank line */
    while (cases--)
    {
        /* initialize */

        /* read data */
        for (fragments_count = 0; fgets(buff, BUFFER_LENGTH, stdin) != NULL && strcmp(buff, "\n"); fragments_count++)
        {
            sscanf(buff, "%s", fragments[fragments_count]);
        }

        /* processing */
        qsort(fragments, fragments_count, BUFFER_LENGTH, (int (*)(const void *, const void *))cmp);

        puts("----");
        for (i = 0; i < fragments_count; i++)
        {
            puts(fragments[i]);
            length_of_fragments[i] = strlen(fragments[i]);
            solution[i] = fragments_count;
        }
        puts("----");
        finished = 0;
        file_size = length_of_fragments[0] + length_of_fragments[fragments_count - 1];

        process(fragments, length_of_fragments, solution, fragments_count, file_size, 0, 1);

        /* output */
        // concat(buff, fragments, 0, solution[0]);
        // puts(buff);

        puts("****");
        for (i = 0; i < fragments_count; i++)
        {
            printf("%d\t%d\n", i, solution[i]);

            // if (solution[i] < fragments_count)
            // {
            //     concat(buff, fragments, i, solution[i]);
            //     puts(buff);
            //     solution[solution[i]] = fragments_count;
            //     solution[i] = fragments_count;
            // }
        }
        puts("****");

        if (cases)
        {
            putchar('\n');
        }
    }

    return EXIT_SUCCESS;
}
