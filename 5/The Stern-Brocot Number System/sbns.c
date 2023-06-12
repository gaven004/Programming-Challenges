/*
 * The Stern-Brocot Number System
 * PC/UVa IDs: 110507/10077
 */

#include <stdio.h>

#define MAXLENGTH 10000

int main() {
    int lx = 0, ly = 1, cx = 1, cy = 1, rx = 1, ry = 0;
    int x, y;
    int r;
    char buff[MAXLENGTH];
    char *ptr;

    while (scanf("%d %d", &x, &y) != EOF) {
        if (x == 1 && y == 1) {
            break;
        }

        ptr = buff;
        lx = 0, ly = 1, cx = 1, cy = 1, rx = 1, ry = 0;
        r = cx * y - x * cy;
        while (r != 0) {
            if (r > 0) {
                *ptr = 'L';
                rx = cx, ry = cy;
            } else {
                *ptr = 'R';
                lx = cx, ly = cy;
            }
            cx = lx + rx, cy = ly + ry;
            r = cx * y - x * cy;
            ptr++;
        }

        *ptr = '\0';
        puts(buff);
    }
}