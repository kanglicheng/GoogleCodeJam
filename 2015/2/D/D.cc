#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

const long long MOD = 1000000007LL;

long long f[101][2][13];

int R, C;

long long LCM(int x, int y) {
    for (int i = 1; ; ++ i)
        if (i % x == 0 && i % y == 0) return i;
}

inline void add(long long &A, long long B) {
    A = A + B;
    if (A >= MOD) A -= MOD;
}

inline long long mul(long long A, long long B) {
    return (A * B) % MOD;
}

long long solve() {
    memset(f, 0, sizeof(f));
    f[0][0][1] = f[0][1][1] = 1;
    for (int i = 0; i <= R; ++ i)
        for (int type = 0; type <= 1; ++ type)
            for (int lcm = 1; lcm <= 12; ++ lcm) {
                long long temp = f[i][type][lcm];
                if (temp == 0) continue;
                if (type == 0) {
                    if (i + 2 <= R)
                        add(f[i + 2][type ^ 1][lcm], temp);
                }
                else {
                    if (i + 1 <= R)
                        add(f[i + 1][type ^ 1][lcm], temp);
                    if (C % 3 == 0 && i + 2 <= R)
                        add(f[i + 2][type ^ 1][LCM(lcm, 3)], mul(temp, 3));
                    if (C % 6 == 0 && i + 2 <= R)
                        add(f[i + 2][type ^ 1][LCM(lcm, 6)], mul(temp, 6));
                    if (C % 4 == 0 && i + 3 <= R)
                        add(f[i + 3][type ^ 1][LCM(lcm, 4)], mul(temp, 4));
                }

            }
    long long ans = 0;
    for (int lcm = 1; lcm <= 12; ++ lcm) {
        long long temp = (f[R][0][lcm] + f[R][1][lcm]) % MOD;
        while (temp % lcm != 0) temp += MOD;
        temp /= lcm;
        add(ans, temp);
    }
    return ans;
}

int main() {
    int T;
    scanf("%d", &T);
    for (int test = 1; test <= T; ++ test) {
        scanf("%d%d", &R, &C);
        printf("Case #%d: %lld\n", test, solve());
    }
    return 0;
}
