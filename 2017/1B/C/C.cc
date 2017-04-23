#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <map>
#include <cstdio>
#include <set>
#include <cmath>

#define MAXN    105
#define MAXQ    105

using namespace std;

double dist[MAXN][MAXN];

const double INF = 1e100;

int E[MAXN], S[MAXN];
long long D[MAXN][MAXN];

pair<int, int> Query[MAXQ];

int N, Q;

void solve() {
    for (int k = 0; k < N; ++ k)
        for (int i = 0; i < N; ++ i)
            for (int j = 0; j < N; ++ j)
                if (i != j && i != k && k != j)
                    if (D[i][k] != -1 && D[k][j] != -1) {
                        if (D[i][j] == -1)
                            D[i][j] = D[i][k] + D[k][j];
                        else
                            D[i][j] = min(D[i][j], D[i][k] + D[k][j]);
                    }

    for (int i = 0; i < N; ++ i) {
        for (int j = 0; j < N; ++ j)
            if (D[i][j] == -1 || D[i][j] > E[i])
                dist[i][j] = INF;
            else
                dist[i][j] = (double)D[i][j] / S[i];
    }
    for (int k = 0; k < N; ++ k)
        for (int i = 0; i < N; ++ i)
            for (int j = 0; j < N; ++ j)
                if (i != j && i != k && k != j)
                    dist[i][j] = min(dist[i][j], dist[i][k] + dist[k][j]);
    for (int i = 0; i < Q; ++ i) {
        int x = Query[i].first;
        int y = Query[i].second;
        printf(" %.6lf", dist[x][y]);
    }
    printf("\n");
}

int main() {
    int T;
    scanf("%d", &T);
    for (int test = 1; test <= T; ++ test) {
        cin >> N >> Q;
        for (int i = 0; i < N; ++ i)
            cin >> E[i] >> S[i];
        for (int i = 0; i < N; ++ i)
            for (int j = 0; j < N; ++ j)
                cin >> D[i][j];
        for (int i = 0; i < Q; ++ i) {
            int x, y;
            cin >> x >> y;
            Query[i] = make_pair(x - 1, y - 1);
        }
        printf("Case #%d:", test);
        solve();
    }
    return 0;
}
