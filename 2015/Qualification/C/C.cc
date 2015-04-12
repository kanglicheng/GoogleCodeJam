#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

int mapping(char ch) {
    if (ch == '1') return 1;
    return (ch - 'i' + 2);
}

int I = 2;
int J = 3;
int K = 4;

int multiply(int a, int b) {
    int sign = 1;
    if (a < 0) {
        sign = sign * -1;
        a = -a;
    }
    if (b < 0) {
        sign = sign * -1;
        b = -b;
    }
    if (a == 1) return sign * b;
    if (b == 1) return sign * a;
    if (a == b) return sign * -1; 
    if (a == J && b == I) return sign * -K;
    if (a == K && b == I) return sign * J;
    if (a == K && b == J) return sign * -I;
    if (a == I && b == J) return sign * K;
    if (a == I && b == K) return sign * -J;
    if (a == J && b == K) return sign * I;
    return 0;
}

int L, X;
vector<int> S;

bool solve() {
    int times = min(4, X);
    
    int single = 1;
    for (int i = 0; i < L; ++ i)
        single = multiply(single, S[i]);
    int all = 1;
    for (int i = 0; i < (X % 4); ++ i)
        all = multiply(all, single);
    if (all != -1) return false;

    //printf("all passed!\n");

    int left, right;

    int res = 1;
    for (left = 0; left < times * L; ++ left) {
        res = multiply(res, S[left % L]);
        if (res == I) break;
    }
    //printf("left = %d\n", left);
    if (left == times * L) return false;

    res = 1;
    for (right = times * L - 1; right >= 0; -- right) {
        res = multiply(S[right % L], res);
        if (res == K) break;
    }
    //printf("right = %d\n", right);
    if (right < 0) return false;
    right = right + (X - times) * L;

    //printf("left, right = %d, %d\n", left, right);
    return left < right;
}

int main() {
    int T;
    scanf("%d", &T);    
    for (int test = 1; test <= T; ++ test) {
        long long XX;
        scanf("%d %lld", &L, &XX);
        //printf("%lld\n", XX);
        X = (XX >= 100) ? (XX % 4) + 4 : XX;

        char temp[10000];
        scanf("%s", temp);
        S.clear();
        for (int i = 0; i < L; ++ i)
            S.push_back(mapping(temp[i]));
        bool res = solve();
        if (res)
            printf("Case #%d: YES\n", test);
        else
            printf("Case #%d: NO\n", test);
    }
    return 0;
}
