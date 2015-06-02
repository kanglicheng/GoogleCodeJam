#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#include <string>
#include <map>
#include <unordered_set>
#include <unordered_map>

using namespace std;

int N;
unordered_map<string, int> hash_f;
int hash_count;
vector<int> A[200];


typedef int F;
#define MAXE 50000
#define MAXV 20000
#define F_INF 1000000

struct MaxFlow {
    int V, E;
    int start[MAXV], next[MAXE], v[MAXE];
    int used[MAXV], level[MAXV];
    F cap[MAXE], flow[MAXE];

    MaxFlow(int n) {
        int i;
        V = n; E = 0;
        memset(start, -1, sizeof(start));
    }

    void add_edge(int x, int y, F c) {
        cap[E] = c; flow[E] = 0; v[E] = y; next[E] = start[x]; start[x] = E; ++ E;
        cap[E] = 0; flow[E] = 0; v[E] = x; next[E] = start[y]; start[y] = E; ++ E;
    }

    bool bfs(int s, int t) {
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

    F dfs(int s, int t, F f) {
        if (s == t) return f;
        for (int &i = used[s]; i != -1; i = next[i])
            if (level[v[i]] > level[s] && cap[i] > flow[i]) {
                F temp = dfs(v[i], t, min(f, cap[i] - flow[i]));
                if (temp > 0) {
                    flow[i] += temp; flow[i^1] -= temp;
                    return temp;
                }
            }
        return 0;
    }

    F maxflow(int s, int t) {
        while (bfs(s, t)) {
            for (int i = 0; i < V; ++ i)
                used[i] = start[i];
            while (dfs(s, t, F_INF) != 0);
        }
        F ret = 0;
        for (int i = start[s]; i != -1; i = next[i])
            ret += flow[i];
        return ret;
    }
};

int solve() {
    MaxFlow mf(2 * hash_count + 2 * N);

    for (int i = 0; i < N; ++ i)
        mf.add_edge(2 * i, 2 * i + 1, 10000);
    for (int i = 0; i < hash_count; ++ i)
        mf.add_edge((N + i) * 2 + 1, (N + i) * 2, 1);
    for (int i = 0; i < N; ++ i)
        for (int j = 0; j < A[i].size(); ++ j) {
            int k = A[i][j];
            mf.add_edge((N + k) * 2, 2 * i, 10000);
            mf.add_edge(2 * i + 1, (N + k) * 2 + 1, 10000);
        }

    int ret = mf.maxflow(0, 3);
    return ret;
}

int hashing(const string &s) {
    if (hash_f.find(s) != hash_f.end())
        return hash_f[s];
    hash_f[s] = hash_count;
    return hash_count ++;
}

vector<int> INPUT() {
    char c;
    string s;
    vector<int> ret;
    while (cin.get(c)) {
        if (c == '\n') break;
        if (c == ' ') {
            ret.push_back(hashing(s));
            s = "";
        }
        else
            s = s + c;
    }
    if (s != "")
        ret.push_back(hashing(s));
    return ret;
}

int main() {
    int T;
    scanf("%d", &T);
    for (int test = 1; test <= T; ++ test) {
        hash_f.clear(); hash_count = 0;

        scanf("%d", &N);
        cin.get();
        for (int i = 0; i < N; ++ i) {
            A[i] = INPUT();

        }
        //fprintf(stderr, "case %d\n", test);
        printf("Case #%d: %d\n", test, solve());
    }
    return 0;
}
