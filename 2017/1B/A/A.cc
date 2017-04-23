#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <map>
#include <cstdio>
#include <set>
#include <cmath>

#define MAXN    15000

using namespace std;

int K[MAXN], S[MAXN];

int N, D;

void solve() {
    double slow = 0.0;
    for (int i = 0; i < N; ++ i) {
        double t = (double)(D - K[i]) / S[i];
        slow = max(slow, t);
    }
    double ans = (double)D / slow;
    printf("%.6lf\n", ans);
}

int main() {
    int T;
    scanf("%d", &T);
    for (int test = 1; test <= T; ++ test) {
        cin >> D >> N;
        for (int i = 0; i < N; ++ i)
            cin >> K[i] >> S[i];
        printf("Case #%d: ", test);
        solve();
    }
    return 0;
}
