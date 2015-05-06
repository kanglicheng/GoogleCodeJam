#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

typedef long long LL;

int N;

int D[1000], H[1000], M[1000];

struct Hiker {
    LL  t, lap;
    Hiker() {}
    Hiker(LL t, LL lap): t(t), lap(lap) {}
    bool operator < (const Hiker &other) const {
        return t > other.t;
    }
};

LL solve() {
    priority_queue<Hiker> Q;
    vector< pair<LL, int> > V;
    LL total = 0;
    for (int i = 0; i < N; ++ i) {
        total += H[i];
        for (int j = 0; j < H[i]; ++ j) {
            LL K = (LL)j + (LL)M[i];
            //fprintf(stderr, "%lld\n", K * (LL)(360 - D[i]));
            V.push_back(make_pair((LL)(360 - D[i]) * K, 1));
            Q.push(Hiker((LL)(720 - D[i]) * K, 360 * K));
        }
    }
    //fprintf(stderr, "%lld\n", total);
    for (int i = 0; i < total; ++ i) {
        Hiker nearest = Q.top(); Q.pop();
        V.push_back(make_pair(nearest.t, 0));
        Q.push(Hiker(nearest.t + nearest.lap, nearest.lap));
    }
    sort(V.begin(), V.end());
    LL ret = total;
    for (int i = 0; i < V.size(); ++ i) {
        if (V[i].second == 0) ++ total; else -- total;
        ret = min(ret, total);
    }
    return ret;
}

int main() {
    int T;
    scanf("%d", &T);    
    for (int test = 1; test <= T; ++ test) {
        scanf("%d", &N);
        for (int i = 0; i < N; ++ i)
            scanf("%d %d %d", &D[i], &H[i], &M[i]);
        LL res = solve();
        printf("Case #%d: %lld\n", test, res);
    }
    return 0;
}
