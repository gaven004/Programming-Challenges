//
// Created by Gaven Auyeu on 2024/12/30.
//
#include <iostream>
#include <cstdio>
#include <cstring>
#include <algorithm>
using namespace std;

const int d[4][2] = {{1, 0}, {0, 1}, {0, -1}, {-1, 0}};
const int ans[4][4] = {
    {1, 2, 3, 4},
    {5, 6, 7, 8},
    {9, 10, 11, 12},
    {13, 14, 15, 0}
};
const char mp[4] = {'D', 'R', 'L', 'U'};

inline void read(int &x) {
    x = 0;
    int f = 1;
    char ch = getchar();
    while (ch < '0' || ch > '9') {
        if (ch == '-') {
            f = -1;
        }
        ch = getchar();
    }
    while (ch >= '0' && ch <= '9') {
        x = x * 10 + ch - '0';
        ch = getchar();
    }
    x *= f;
}

int a[4][4];

inline int check() {
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (a[i][j] != ans[i][j]) {
                return 0;
            }
        }
    }
    return 1;
}

int found;

inline int count_1(int v, int x0, int y0, int x1, int y1) {
    int goal_x = (v - 1) / 4;
    int goal_y = (v - 1) % 4;
    return (abs(goal_x - x1) + abs(goal_y - y1)) - (abs(goal_x - x0) + abs(goal_y - y0));
}

inline int count() {
    int cnt = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            if (!a[i][j]) {
                continue;
            }
            int goal_x = (a[i][j] - 1) / 4;
            int goal_y = (a[i][j] - 1) % 4;
            cnt += abs(goal_x - i) + abs(goal_y - j);
        }
    }
    return cnt;
}

char sol[50];

void IDA_STAR(int step, int x, int y, int max_step, int last_step, int h) {
    if (step == max_step) {
        if (h == 0) {
            found = 1;
        }
        return;
    }
    for (int i = 0; i < 4; i++) {
        int x1 = x + d[i][0], y1 = y + d[i][1];
        if (i + last_step == 3) {
            continue;
        }
        if (x1 < 0 || x1 > 3 || y1 < 0 || y1 > 3) {
            continue;
        }
        int v = a[x1][y1];
        int d = count_1(v, x, y, x1, y1);
        swap(a[x][y], a[x1][y1]);
        if (!(h - d + step > max_step) && !found) {
            sol[step + 1] = mp[i];
            IDA_STAR(step + 1, x1, y1, max_step, i, h - d);
        }
        swap(a[x][y], a[x1][y1]);
    }
}

int p[20];

inline int solveable() {
    int cnt = 0, con = 0;
    for (int i = 0; i < 4; i++) {
        for (int j = 0; j < 4; j++) {
            p[con++] = a[i][j];
        }
    }
    for (int i = 0; i < 16; i++) {
        if (p[i] == 0) {
            cnt += 3 - (i / 4);
        } else {
            for (int j = 0; j < i; j++) {
                if (p[j] && p[j] > p[i]) {
                    cnt++;
                }
            }
        }
    }
    return !(cnt & 1);
}

int main() {
    int t;
    read(t);
    while (t--) {
        int sx, sy;
        for (int i = 0; i < 4; i++) {
            for (int j = 0; j < 4; j++) {
                read(a[i][j]);
                if (a[i][j] == 0) {
                    sx = i;
                    sy = j;
                }
            }
        }
        int h = count();
        if (h == 0) {
            printf("\n");
            continue;
        }
        if (!solveable()) {
            printf("This puzzle is not solvable.\n");
            continue;
        }
        int max_step = h;
        for (;; max_step++) {
            IDA_STAR(0, sx, sy, max_step, -1, h);
            if (found) {
                break;
            }
        }
        if (found) {
            for (int i = 1; i <= max_step; i++) {
                putchar(sol[i]);
            }
            putchar('\n');
        }
        found = 0;
    }
    return 0;
}
