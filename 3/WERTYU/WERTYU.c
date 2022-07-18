/*
 * WERTYU
 * PC/UVa IDs: 110301/10082
 */

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

int main(void)
{
    char MAPPING[128];
    MAPPING['1'] = '`';
    MAPPING['2'] = '1';
    MAPPING['3'] = '2';
    MAPPING['4'] = '3';
    MAPPING['5'] = '4';
    MAPPING['6'] = '5';
    MAPPING['7'] = '6';
    MAPPING['8'] = '7';
    MAPPING['9'] = '8';
    MAPPING['0'] = '9';
    MAPPING['-'] = '0';
    MAPPING['='] = '-';
    MAPPING['W'] = 'Q';
    MAPPING['E'] = 'W';
    MAPPING['R'] = 'E';
    MAPPING['T'] = 'R';
    MAPPING['Y'] = 'T';
    MAPPING['U'] = 'Y';
    MAPPING['I'] = 'U';
    MAPPING['O'] = 'I';
    MAPPING['P'] = 'O';
    MAPPING['['] = 'P';
    MAPPING[']'] = '[';
    MAPPING['\\'] = ']';
    MAPPING['S'] = 'A';
    MAPPING['D'] = 'S';
    MAPPING['F'] = 'D';
    MAPPING['G'] = 'F';
    MAPPING['H'] = 'G';
    MAPPING['J'] = 'H';
    MAPPING['K'] = 'J';
    MAPPING['L'] = 'K';
    MAPPING[';'] = 'L';
    MAPPING['\''] = ';';
    MAPPING['X'] = 'Z';
    MAPPING['C'] = 'X';
    MAPPING['V'] = 'C';
    MAPPING['B'] = 'V';
    MAPPING['N'] = 'B';
    MAPPING['M'] = 'N';
    MAPPING[','] = 'M';
    MAPPING['.'] = ',';
    MAPPING['/'] = '.';
    MAPPING[' '] = ' ';
    MAPPING['\r'] = '\r';
    MAPPING['\n'] = '\n';

    char c;

    /* read data */
    while ((c = getchar()) != EOF)
    {
        putchar(MAPPING[c]);
    }

    return EXIT_SUCCESS;
}
