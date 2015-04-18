#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>
#include <cmath>
//#include <bits/stdc++.h>

using namespace std;

int N;
vector<int> X;
vector<int> Y;

const double EPS = 1e-10;
const double PI = M_PI;

void solve() {
    vector<double> angles;
    for (int i = 0; i < N; ++ i) {
        angles.clear();
        for (int j = 0; j < N; ++ j) {
            if (i == j) continue;
            angles.push_back(atan2l(Y[j] - Y[i], X[j] - X[i]));
        }
        sort(angles.begin(), angles.end());
        for (int i = 0; i < N - 1; ++ i)
            angles.push_back(angles[i] + 2 * PI);
        int maxPoints = 0;
        int R = 0;
        for (int L = 0; L < N - 1; ++ L) {
            while (R < angles.size() && angles[R] <= angles[L] + PI + EPS) ++ R;
            maxPoints = max(maxPoints, R - L);
        }
        printf("%d\n", N - 1 - maxPoints);
    }
}

int main() {
    int T;
    scanf("%d", &T);    
    for (int test = 1; test <= T; ++ test) {
        scanf("%d", &N);
        X.clear(); Y.clear();
        for (int i = 0; i < N; ++ i) {
            int x, y;
            scanf("%d %d", &x, &y);
            X.push_back(x); Y.push_back(y);
        }
        printf("Case #%d:\n", test);
        solve();
    }
    return 0;
}

/*
vector<int> X, Y;
int N;

int main() {
    int T;
    scanf("%d", &T);    
    for (int test = 1; test <= T; ++ test) {
        scanf("%d", &N);
        X.clear(); Y.clear();
        for (int i = 0; i < N; ++ i) {
            int x, y;
            scanf("%d %d", &x, &y);
            X.push_back(x); Y.push_back(y);
        }
        printf("Case #%d:\n", test);
        if (N <= 3) {
            for (int i = 0; i < N; ++ i)
                printf("0\n");
        }
        else {
            for (int i = 0; i < N; ++ i) {
                int res = 0;
                for (int j = 0; j < N; ++ j) {
                    if (i == j) continue;
                    int total = 2;
                    long long vecAx = (long long)(X[j] - X[i]);
                    long long vecAy = (long long)(Y[j] - Y[i]);
                    int sideA = 0;
                    int sideB = 0;
                    for (int k = 0; k < N; ++ k) {
                        if (k == i || k == j) continue;
                        long long vecBx = (long long)(X[k] - X[i]);
                        long long vecBy = (long long)(Y[k] - Y[i]);
                        long long cp = vecAx * vecBy - vecAy * vecBx;
                        if (cp == 0)
                            ++ total;
                        else if (cp > 0)
                            ++ sideA;
                        else
                            ++ sideB;
                    }
                    total += (sideA > sideB) ? sideA : sideB;
                    if (total > res)
                        res = total;
                }
                printf("%d\n", N - res);
            }
        }
    }
    return 0;
}
*/