#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cstdio>

using namespace std;


long long N, K;

int log(long long X) {
    int k = 0;
    long long Y = 1LL;
    while (X > Y - 1) {
        ++ k;
        Y <<= 1;
    }
    return k;
}

void solve() {
    int level = log(K);
    //long long prev = (1LL << level) - 1;
    long long M = (1LL << (level - 1)) - 1;
    long long L = (N - M) / (M + 1);
    long long R = (N - M) % (M + 1);
    if (K - M <= R)
        ++ L;
    long long A = (L - 1) >> 1;
    long long B = (L - 1) - A;
    printf("%lld %lld\n", max(A, B), min(A, B));
}

int main() {
    int T;
    scanf("%d", &T);
    for (int test = 1; test <= T; ++ test) {
        scanf("%lld %lld", &N, &K);
        printf("Case #%d: ", test);
        solve();
    }
    return 0;
}
