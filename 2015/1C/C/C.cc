#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

int C, D;
long long V;

vector<int> A;

int solve() {
    int ret = 0;
    sort(A.begin(), A.end());
    long long next = 0;
    int k = 0;
    while (next < V) {
        while (k < D && A[k] <= next + 1) {
            next += (long long)A[k] * C;
            ++ k;
        }
        if (next >= V) break;
        next += (next + 1) * C;
        ++ ret;
    }
    return ret;
}

int main() {
    int T;
    scanf("%d", &T);
    for (int test = 1; test <= T; ++ test) {
        scanf("%d%d%lld", &C, &D, &V);
        A.clear();
        for (int i = 0; i < D; ++ i) {
            int k;
            scanf("%d", &k);
            A.push_back(k);
        }
        printf("Case #%d: %d\n", test, solve());
    }
    return 0;
}
