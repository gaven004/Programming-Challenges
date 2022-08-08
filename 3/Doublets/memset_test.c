#include <stdio.h>
#include <stdlib.h>
#include <string.h>

int main(void)
{
    int i;
    int a[10];
    
    memset(a, 255, sizeof(a));
    for ( i = 0; i < 10; i++)
    {
        printf("%d ", a[i]);
    }
    putchar('\n');

    memset(a, 0, sizeof(a));
    for ( i = 0; i < 10; i++)
    {
        printf("%d ", a[i]);
    }
    putchar('\n');
    
    return EXIT_SUCCESS;
}