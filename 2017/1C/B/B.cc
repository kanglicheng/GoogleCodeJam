#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <map>
#include <cstdio>
#include <set>
#include <cmath>

using namespace std;

int C, J, N;

int A[1450];

int F[2][1450][721][2];

const int INF = 1000000000;

int solve() {
    for (int k = 0; k <= 1; ++ k)
        for (int i = 0; i <= 1440; ++ i)
            for (int j = 0; j <= 720; ++ j) {
                F[k][i][j][0] = INF;
                F[k][i][j][1] = INF;
            }

    F[0][0][0][0] = 0;
    F[1][0][0][1] = 0;

    for (int first = 0; first <= 1; ++ first) {
        for (int t = 1; t <= 1440; ++ t) {
            if (A[t - 1] >= 0) {
                for (int k = 0; k <= 720; ++ k)
                F[first][t][k][0] = min(F[first][t - 1][k][1] + 1, F[first][t - 1][k][0]);
            }
            if (A[t - 1] <= 0) {
                for (int k = 1; k <= 720; ++ k)
                F[first][t][k][1] = min(F[first][t - 1][k - 1][1], F[first][t - 1][k - 1][0] + 1);
            }
        }
    }
    return min(min(F[0][1440][720][0], F[1][1440][720][1]), 1 + min(F[1][1440][720][0], F[0][1440][720][1]));
}

int main() {
    int T;
    scanf("%d", &T);
    for (int test = 1; test <= T; ++ test) {
        for (int i = 0; i < 1440; ++ i)
            A[i] = 0;
        cin >> C >> J;
        for (int i = 0; i < C; ++ i) {
            int x, y;
            cin >> x >> y;
            for (int j = x; j < y; ++ j)
                A[j] = 1;
        }
        for (int i = 0; i < J; ++ i) {
            int x, y;
            cin >> x >> y;
            for (int j = x; j < y; ++ j)
                A[j] = -1;
        }
        printf("Case #%d: %d\n", test, solve());
    }
    return 0;
}
