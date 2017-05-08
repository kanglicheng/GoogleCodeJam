#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <map>
#include <cstdio>
#include <set>
#include <cmath>

using namespace std;

int N, K;
double U;

vector<double> P;

double solve_small() {
    if (N == 1) return U + P[0];
    sort(P.begin(), P.end());
    double last = P[0];
    int i;
    for (i = 1; i < N; ++ i) {
        double need = (P[i] - last) * i;
        if (U >= need) {
            last = P[i];
            U -= need;
        }
        else {
            last += U / i;
            U = 0.0;
        }
        if (U <= 0.0) break;
    }
    if (U > 0.0) {
        last += U / N;
    }
    double ans = 1.0;
    for (int j = i; j < N; ++ j)
        ans *= P[j];
    for (int j = 0; j < i; ++ j)
        ans *= last;
    return ans;
}

int main() {
    int T;
    scanf("%d", &T);
    for (int test = 1; test <= T; ++ test) {
        P.clear();
        cin >> N >> K;
        cin >> U;
        for (int i = 0; i < N; ++ i) {
            double x;
            cin >> x;
            P.push_back(x);
        }
        double ans = solve_small();
        printf("Case #%d: %.8lf\n", test, ans);
    }
    return 0;
}
