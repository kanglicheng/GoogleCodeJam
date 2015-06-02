#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

int N;
double V, X;
double R[100], C[100];
double eps = 1e-10;

void solve_small() {
    if (N == 1) {
        if (abs(C[0] - X) > eps) {
            printf("IMPOSSIBLE\n");
            return;
        }
        double ret = V / R[0];
        printf("%.9lf\n", ret);
        return;
    }
    if (C[0] > eps + X && C[1] > eps + X) {
        printf("IMPOSSIBLE\n");
        return;
    }
    if (C[0] < X - eps && C[1] < X - eps) {
        printf("IMPOSSIBLE\n");
        return;
    }
    if (abs(C[0] - C[1]) <= eps) {
        double ret = V / (R[0] + R[1]);
        printf("%.9lf\n", ret);
        return;
    }
    double v0 = V * (X - C[1]) / (C[0] - C[1]);
    double v1 = V - v0;
    double ret = max(v0 / R[0], v1 / R[1]);
    printf("%.9lf\n", abs(ret));
}

double get_lower(double total) {
    double ret = 0.0;
    for (int i = 0; i < N; ++ i) {
        double k = min(total, R[i]);
        total -= k;
        ret += k * C[i];
    }
    return ret;
}

double get_upper(double total) {
    double ret = 0.0;
    for (int i = N - 1; i >= 0; -- i) {
        double k = min(total, R[i]);
        total -= k;
        ret += k * C[i];
    }
    return ret;
}

void solve() {
    vector< pair<double, double> > tosort;
    for (int i = 0; i < N; ++ i)
        tosort.push_back(make_pair(C[i], R[i]));
    sort(tosort.begin(), tosort.end());
    for (int i = 0; i < N; ++ i) {
        C[i] = tosort[i].first;
        R[i] = tosort[i].second;
    }

    if (!(X >= C[0] && X <= C[N - 1])) {
        printf("IMPOSSIBLE\n");
        return;
    }

    if (X == C[0] || X == C[N - 1]) {
        double v = 0.0;
        for (int i = 0; i < N; ++ i)
            if (C[i] == X) v += R[i];
        double ans = V / v;
        printf("%.9lf\n", ans);
        return;
    }

    double left = 0.0;
    double right = 0.0;
    for (int i = 0; i < N; ++ i)
        right += R[i];
    for (int iteration = 0; iteration < 100; ++ iteration) {
        double mid = (left + right) / 2.0;
        double lower = get_lower(mid);
        double upper = get_upper(mid);
        if (lower <= X * mid && X * mid <= upper)
            left = mid;
        else
            right = mid;
    }

    double ans = V / left;
    printf("%.9lf\n", ans);
}

int main() {
    int T;
    scanf("%d", &T);
    for (int test = 1; test <= T; ++ test) {
        scanf("%d%lf%lf", &N, &V, &X);
        for (int i = 0; i < N; ++ i)
            scanf("%lf%lf", &R[i], &C[i]);
        printf("Case #%d: ", test);
        //solve_small();
        solve();
    }
    return 0;
}
