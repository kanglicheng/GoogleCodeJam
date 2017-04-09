#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cstdio>

using namespace std;

int N;

const int maxN = 1010;

int F[maxN];

int ans;

bool in_cycle[maxN];

int visited[maxN];

void find_cycle(int x, int parent, int depth) {
    visited[x] = depth;
    if (F[x] == parent) return;
    if (visited[F[x]] == 0)
        find_cycle(F[x], x, depth + 1);
    else if (visited[F[x]] == 1) {
        int count = 0;
        for (int i = 1; i <= N; ++ i)
            if (visited[i] > 0) {
                in_cycle[i] = true;
                ++ count;
            }
        ans = max(ans, count);
    }
}

bool reach_cycle(int x) {
    int parent = -1;
    while (1) {
        if (in_cycle[x]) return true;
        if (F[x] == parent) return false;
        parent = x;
        x = F[x];
    }
}

int dist[maxN];

void dfs(int x, int depth) {
    if (depth <= dist[x]) return;
    dist[x] = depth;
    if (F[F[x]] == x) return;
    dfs(F[x], depth + 1);
}

void solve() {
    ans = 0;
    memset(in_cycle, false, sizeof(in_cycle));
    for (int i = 1; i <= N; ++ i)
        if (!in_cycle[i]) {
            memset(visited, 0, sizeof(visited));
            find_cycle(i, -1, 1);
        }

    for (int i = 1; i <= N; ++ i)
        if (!in_cycle[i])
            if (reach_cycle(i))
                in_cycle[i] = true;

    memset(dist, 0, sizeof(dist));
    for (int i = 1; i <= N; ++ i)
        if (!in_cycle[i]) dfs(i, 1);

/*
    for (int i = 1; i <= N; ++ i)
        cout << i << " " << dist[i] << endl;
*/
    memset(visited, false, sizeof(visited));
    int total = 0;
    for (int i = 1; i <= N; ++ i)
        if (!in_cycle[i] && !visited[i])
            if (F[F[i]] == i) {
                visited[i] = visited[F[i]] = true;
                int len = dist[i] + dist[F[i]];
                total += len;
            }
    ans = max(ans, total);

    printf("%d\n", ans);
}

int main() {
    int T;
    scanf("%d", &T);
    for (int test = 1; test <= T; ++ test) {
        scanf("%d", &N);
        for (int i = 1; i <= N; ++ i)
            scanf("%d", &F[i]);
        printf("Case #%d: ", test);
        solve();
    }
    return 0;
}
