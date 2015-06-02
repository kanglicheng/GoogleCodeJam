#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#include <string>

using namespace std;

int R, C;

// 0 --> up
// 1 --> left
// 2 --> right
// 3 --> down
int dx[4] = {-1, 0, 0, 1};
int dy[4] = {0, -1, 1, 0};

int map[100][100];

int check(int sx, int sy) {
    int x = sx;
    int y = sy;
    int direction = -1;;
    int lastx, lasty, lastdir;
    int count = 0;
    while (x >= 0 && x < R && y >= 0 && y < C) {
        if (count > R * C) return 0;
        if (map[x][y] != -1) {
            lastx = x; lasty = y;
            lastdir = direction;
            direction = map[x][y];
        }
        x = x + dx[direction];
        y = y + dy[direction];
        ++ count;
    }
    if (lastx != sx || lasty != sy) {
        map[lastx][lasty] = 3 - lastdir;
        return 1;
    }
    return -1;
}

void solve() {
    int ret = 0;
    for (int i = 0; i < R; ++ i)
        for (int j = 0; j < C; ++ j)
            if (map[i][j] != -1) {
                int k = check(i, j);
                if (k == -1) {
                    int count = 0;
                    while (count < 3 && k == -1) {
                        ++ count;
                        map[i][j] = (map[i][j] + 1) % 4;
                        k = check(i, j);
                    }
                    if (k == -1) {
                        printf("IMPOSSIBLE\n");
                        return;
                    }
                    else
                        ret = ret + 1 + k;
                }
                else
                    ret += k;
                /*
                for (int ii = 0; ii < R; ++ ii) {
                    for (int jj = 0; jj < C; ++ jj)
                        printf("%d ", map[ii][jj]);
                    printf("\n");
                }
                */
            }
    printf("%d\n", ret);
}

int main() {
    int T;
    scanf("%d", &T);
    for (int test = 1; test <= T; ++ test) {
        scanf("%d%d", &R, &C);
        for (int i = 0; i < R; ++ i) {
            char temp[100];
            scanf("%s", temp);
            for (int j = 0; j < C; ++ j)
                if (temp[j] == '^')
                    map[i][j] = 0;
                else if (temp[j] == 'v')
                    map[i][j] = 3;
                else if (temp[j] == '<')
                    map[i][j] = 1;
                else if (temp[j] == '>')
                    map[i][j] = 2;
                else
                    map[i][j] = -1;
        }
        printf("Case #%d: ", test);
        solve();
    }
    return 0;
}
