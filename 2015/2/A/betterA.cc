#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#include <string>

using namespace std;

int R, C;

int dx[4] = {-1, 0, 0, 1};
int dy[4] = {0, -1, 1, 0};
string direction = "^<>v";

vector<string> map;

bool check(int x, int y, int d) {
    for (;;) {
        x += dx[d];
        y += dy[d];
        if (x >= R || x < 0 || y >= C || y < 0) return false;
        if (map[x][y] != '.') return true;
    }
}

void solve() {
    int ret = 0;
    for (int i = 0; i < R; ++ i)
        for (int j = 0; j < C; ++ j) {
            if (map[i][j] == '.') continue;
            int d = direction.find(map[i][j]);
            if (check(i, j, d)) continue;
            for (d = 0; d < 4; ++ d)
                if (check(i, j, d)) break;
            if (d == 4) {
                printf("IMPOSSIBLE\n");
                return;
            }
            ++ ret;
        }
    printf("%d\n", ret);
}

int main() {
    int T;
    scanf("%d", &T);
    for (int test = 1; test <= T; ++ test) {
        map.clear();
        scanf("%d%d", &R, &C);
        for (int i = 0; i < R; ++ i) {
            string temp;
            cin >> temp;
            map.push_back(temp);
        }
        printf("Case #%d: ", test);
        solve();
    }
    return 0;
}
