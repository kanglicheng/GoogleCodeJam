#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <queue>
#include <cstdio>

using namespace std;

const int MAXN = 105;

typedef int F;
const int MAXV = 4 * MAXN;
const int MAXE = MAXV * MAXV * 2;
const int F_INF = 10000000;

class MaxFlow {
public:
    int V, E;

    MaxFlow(int V) : V(V), E(0) {
        memset(start, -1, sizeof(start));
    }

    void add_edge(int x, int y, F c) {
        cap[E] = c; flow[E] = 0; v[E] = y; next[E] = start[x]; start[x] = E; ++ E;
        cap[E] = 0; flow[E] = 0; v[E] = x; next[E] = start[y]; start[y] = E; ++ E;
    }

    bool BFS(int, int);
    F DFS(int, int, F);
    F maxflow(int, int);

    vector<pair<int, int>> get_flows();

private:
    int start[MAXV], next[MAXE], v[MAXE];
    int used[MAXV], level[MAXV];
    F cap[MAXE], flow[MAXE];
};

vector<pair<int, int>> MaxFlow::get_flows() {
    vector<pair<int, int>> ret;
    for (int i = 0; i < V; ++ i)
        for (int j = start[i]; j != -1; j = next[j])
            if (flow[j] > 0)
                ret.push_back({i, v[j]});
    return ret;
}

bool MaxFlow::BFS(int s, int t) {
    memset(level, -1, sizeof(level));
    queue<int> q;
    q.push(s); level[s] = 0;
    while (!q.empty()) {
        int x = q.front(); q.pop();
        for (int i = start[x]; i != -1; i = next[i])
            if (level[v[i]] == -1 && cap[i] > flow[i]) {
                q.push(v[i]);
                level[v[i]] = level[x] + 1;
            }
    }
    return (level[t] != -1);
}

F MaxFlow::DFS(int s, int t, F f) {
    if (s == t) return f;
    for (int &i = used[s]; i != -1; i = next[i])
        //if (level[v[i]] > level[s] && cap[i] > flow[i]) { // should be same
        if (level[v[i]] == level[s] + 1 && cap[i] > flow[i]) {
            F temp = DFS(v[i], t, min(f, cap[i] - flow[i]));
            if (temp > 0) {
                flow[i] += temp; flow[i^1] -= temp;
                return temp;
            }
        }
    return 0;
}

F MaxFlow::maxflow(int s, int t) {
    while (BFS(s, t)) {
        for (int i = 0; i < V; ++ i)
            used[i] = start[i];
        while (DFS(s, t, F_INF) != 0);
    }
    F ret = 0;
    for (int i = start[s]; i != -1; i = next[i])
        ret += flow[i];
    return ret;
}

char A[MAXN][MAXN];
int N;
char O[MAXN][MAXN];

bool used_row[MAXN * 2], used_column[MAXN * 2];

void solve() {
    MaxFlow *rook = new MaxFlow(2 * N + 2);
    memset(used_row, false, sizeof(used_row));
    memset(used_column, false, sizeof(used_column));

    for (int i = 0; i < N; ++ i)
        for (int j = 0; j < N; ++ j)
            if (O[i][j] == 'x' || O[i][j] == 'o') {
                used_row[i] = true; used_column[j] = true;
            }

    for (int i = 0; i < N; ++ i) {
        rook->add_edge(2 * N, i, 1);
        rook->add_edge(N + i, 2 * N + 1, 1);
    }

    for (int i = 0; i < N; ++ i)
        for (int j = 0; j < N; ++ j)
            if ((O[i][j] == ' ' || O[i][j] == '+') && !used_row[i] && !used_column[j])
                rook->add_edge(i, N + j, 1);

    rook->maxflow(2 * N, 2 * N + 1);

    MaxFlow *bishop = new MaxFlow(4 * N);
    memset(used_row, false, sizeof(used_row));
    memset(used_column, false, sizeof(used_column));

    for (int i = 0; i < N; ++ i)
        for (int j = 0; j < N; ++ j)
            if (O[i][j] == '+' || O[i][j] == 'o') {
                used_row[i + j] = true; used_column[i - j + N - 1] = true;
            }

    for (int i = 0; i < 2 * N - 1; ++ i) {
        bishop->add_edge(4 * N - 2, i, 1);
        bishop->add_edge(2 * N - 1 + i, 4 * N - 1, 1);
    }

    for (int i = 0; i < N; ++ i)
        for (int j = 0; j < N; ++ j)
            if ((O[i][j] == ' ' || O[i][j] == 'x') && !used_row[i + j] && !used_column[i - j + N - 1])
                bishop->add_edge(i + j, 2 * N - 1 + (i - j + N - 1), 1);

    bishop->maxflow(4 * N - 2, 4 * N - 1);


    vector<pair<int, int>> matchings = rook->get_flows();
    for (const pair<int, int> &p : matchings) {
        if (p.first >= 2 * N || p.second >= 2 * N) continue;
        int x = p.first;
        int y = p.second - N;
        A[x][y] = (A[x][y] == '+' ? 'o' : 'x');
    }

    matchings = bishop->get_flows();
    for (const pair<int, int> &p : matchings) {
        if (p.first >= 4 * N - 2 || p.second >= 4 * N - 2) continue;
        int a = p.first;
        int b = p.second - (2 * N - 1);
        int x = (a + b - (N - 1)) / 2;
        int y = a - x;
        A[x][y] = (A[x][y] == 'x' ? 'o' : '+');
    }

    delete rook;
    delete bishop;

    int total = 0;
    int score = 0;
    for (int x = 0; x < N; ++ x)
        for (int y = 0; y < N; ++ y) {
            if (A[x][y] != O[x][y])
                ++ total;
            score += (A[x][y] == 'o' ? 2 : (A[x][y] != ' ' ? 1 : 0));
        }

    printf("%d %d\n", score, total);
    for (int x = 0; x < N; ++ x)
        for (int y = 0; y < N; ++ y)
            if (A[x][y] != O[x][y])
                printf("%c %d %d\n", A[x][y], x + 1, y + 1);
}

int main() {
    int T;
    scanf("%d", &T);
    for (int test = 1; test <= T; ++ test) {
        int M;
        scanf("%d %d", &N, &M);
        for (int i = 0; i < N; ++ i)
            for (int j = 0; j < N; ++ j)
                O[i][j] = A[i][j] = ' ';
        while (M --){
            char c; int x, y;
            scanf(" %c %d %d", &c, &x, &y);
            -- x; -- y;
            A[x][y] = O[x][y] = c;
        }
        printf("Case #%d: ", test);
        solve();
    }
    return 0;
}
