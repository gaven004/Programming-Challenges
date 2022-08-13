#include <stdio.h>
#include <stdlib.h>

int main(void)
{
    ungetc('A', stdin);
    ungetc('B', stdin);

    printf("%c", getchar());
    printf("%c", getchar());

    return EXIT_SUCCESS;
}