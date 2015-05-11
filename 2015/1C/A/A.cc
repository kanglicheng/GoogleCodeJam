#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

int R, C, W;

int solve() {
    int K = C / W;
    if (C % W == 0)
        return (R - 1) * K + (K - 1) + W;
    return R * K + W;
}

int main() {
    int T;
    scanf("%d", &T);
    for (int test = 1; test <= T; ++ test) {
        scanf("%d%d%d", &R, &C, &W);
        printf("Case #%d: %d\n", test, solve());
    }
    return 0;
}
