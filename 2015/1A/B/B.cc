#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

int N;
long long M;

int A[1000];

int solve() {
    long long L = 0;
    long long R = 100000000000000LL;
    while (L + 1 != R) {
        long long mid = (L + R) >> 1;
        long long total = 0;
        for (int i = 0; i < N; ++ i) {
            total += mid / (long long)A[i];
            if (mid % A[i] != 0) ++ total;
        }
        //printf("(%lld %lld %lld)\n", L, R, total);
        if (total < M)
            L = mid;
        else
            R = mid;
    }
    //printf("Time = %lld\n", L);
    long long total = 0;
    for (int i = 0; i < N; ++ i) {
        total += L / (long long)A[i];
        if (L % A[i] != 0) ++ total;
    }
    for (int i = 0; i < N; ++ i)
        if (L % A[i] == 0) {
            ++ total;
            if (total == M) return i + 1;
        }
    return 0;
}

int main() {
    int T;
    scanf("%d", &T);
    for (int test = 1; test <= T; ++ test) {
        scanf("%d %lld", &N, &M);
        for (int i = 0; i < N; ++ i)
            scanf("%d", A + i);
        int res = solve();
        printf("Case #%d: %d\n", test, res);
    }
}

/*
// STUPID!!!
long long gcd(long long a, long long b) {
    if (b == 0) return a;
    return gcd(b, a % b);
}

int N;
long long M;

vector<int> A;

vector<int> B;

int main() {
    int T;
    scanf("%d", &T);    
    for (int test = 1; test <= T; ++ test) {
        //fprintf(stderr, "Running %d:\n", test);
        scanf("%d %lld", &N, &M);
        A.clear();
        for (int i = 0; i < N; ++ i) {
            int k;
            scanf("%d", &k);
            A.push_back(k);
        }
        long long lcm = A[0];
        for (int i = 1; i < N; ++ i) {
            long long k = gcd(lcm, A[i]);
            lcm = (long long)(A[i] / k) * lcm;
        }
        long long single = 0;
        for (int i = 0; i < N; ++ i)
            single += lcm / A[i];
        M = M % single;
        B.clear();
        for (int i = 0; i < N; ++ i)
            B.push_back(0);
        int def = 0;
        for (int i = 1; i < N; ++ i)
            if (A[i] <= A[def]) def = i;
        int min = def;
        while (M --) {
            min = 0;
            for (int i = 1; i < N; ++ i)
                if (B[min] > B[i]) min = i;
            B[min] += A[min];
        }
        printf("Case #%d: %d\n", test, min + 1);
    }
    return 0;
}
*/