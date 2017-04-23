#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cstdio>

using namespace std;

const int MAXN = 105;


const int MAXV = 4 * MAXN;
const int MAXE = MAXV * MAXV;

class Graph {
public:
    static const int nulledge = -1;
    int V, E;

    Graph(int V) : V(V), E(0) {
        memset(start_u, nulledge, sizeof(start_u));
    }
    void add_edge(int x, int y) {
        edge_v[E] = y; next_edge[E] = start_u[x]; start_u[x] = E; ++ E;
    }

    void add_edge_undirected(int x, int y) {
        add_edge(x, y); add_edge(y, x);
    }

    int start(int u) {
        return start_u[u];
    }

    int next(int e) {
        return next_edge[e];
    }

    int v(int e) {
        return edge_v[e];
    }

private:
    int next_edge[MAXE];
    int edge_v[MAXE];
    int start_u[MAXV];

};

class BipartiteMatching {
public:
    Graph *graph;
    int L, R;

    BipartiteMatching(Graph *graph, int L, int R) : graph(graph), L(L), R(R) {}

    int matching();
    vector<pair<int, int>> get_matchings();

private:
    int m[MAXV];
    bool flag[MAXV];

    bool extend_path(int);
};

vector<pair<int, int>> BipartiteMatching::get_matchings() {
    vector<pair<int, int>> ret;
    for (int r = L; r < L + R; ++ r)
        if (m[r] != -1)
            ret.push_back({m[r], r});
    return ret;
}

bool BipartiteMatching::extend_path(int l) {
    for (int e = graph->start(l); e != Graph::nulledge; e = graph->next(e)) {
        int r = graph->v(e);
        if (flag[r]) {
            flag[r] = false;
            if (m[r] == -1 || extend_path(m[r])) {
                m[r] = l;
                return true;
            }
        }
    }
    return false;
}

int BipartiteMatching::matching() {
    int res = 0;
    memset(m, -1, sizeof(m));
    for (int l = 0; l < L; ++ l) {
        memset(flag, true, sizeof(flag));
        if (extend_path(l)) ++ res;
    }
    return res;
}

char A[MAXN][MAXN];
int N;
char O[MAXN][MAXN];

bool used_row[MAXN * 2], used_column[MAXN * 2];

void solve() {
    Graph *rook_graph = new Graph(2 * N);
    memset(used_row, false, sizeof(used_row));
    memset(used_column, false, sizeof(used_column));

    for (int i = 0; i < N; ++ i)
        for (int j = 0; j < N; ++ j)
            if (O[i][j] == 'x' || O[i][j] == 'o') {
                used_row[i] = true; used_column[j] = true;
            }

    for (int i = 0; i < N; ++ i)
        for (int j = 0; j < N; ++ j)
            if ((O[i][j] == ' ' || O[i][j] == '+') && !used_row[i] && !used_column[j])
                rook_graph->add_edge(i, N + j);
    BipartiteMatching *rook_matching = new BipartiteMatching(rook_graph, N, N);
    rook_matching->matching();


    Graph *bishop_graph = new Graph(4 * N - 2);
    memset(used_row, false, sizeof(used_row));
    memset(used_column, false, sizeof(used_column));
    for (int i = 0; i < N; ++ i)
        for (int j = 0; j < N; ++ j)
            if (O[i][j] == '+' || O[i][j] == 'o') {
                used_row[i + j] = true; used_column[i - j + N - 1] = true;
            }
    for (int i = 0; i < N; ++ i)
        for (int j = 0; j < N; ++ j)
            if ((O[i][j] == ' ' || O[i][j] == 'x') && !used_row[i + j] && !used_column[i - j + N - 1])
                bishop_graph->add_edge(i + j, 2 * N - 1 + (i - j + N - 1));
    BipartiteMatching *bishop_matching = new BipartiteMatching(bishop_graph, 2 * N - 1, 2 * N - 1);
    bishop_matching->matching();

    vector<pair<int, int>> matchings = rook_matching->get_matchings();
    for (const pair<int, int> &p : matchings) {
        int x = p.first;
        int y = p.second - N;
        A[x][y] = (A[x][y] == '+' ? 'o' : 'x');
    }

    matchings = bishop_matching->get_matchings();
    for (const pair<int, int> &p : matchings) {
        int a = p.first;
        int b = p.second - (2 * N - 1);
        int x = (a + b - (N - 1)) / 2;
        int y = a - x;
        A[x][y] = (A[x][y] == 'x' ? 'o' : '+');
    }

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
