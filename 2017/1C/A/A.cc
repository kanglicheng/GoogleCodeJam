#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <map>
#include <cstdio>
#include <set>
#include <cmath>

using namespace std;

vector<pair<double, double>> A;
vector<double> B;

const double PI = atan(1.0) * 4;

int N, K;

void solve() {
    sort(A.begin(), A.end());
    B.clear();
    double ans = 0.0;
    for (int i = 0; i < K - 1; ++ i)
        B.push_back(2 * PI * A[i].first * A[i].second);

    for (int i = K - 1; i < N; ++ i) {
        double cur = PI * A[i].first * A[i].first + 2 * PI * A[i].first * A[i].second;
        for (int j = 0; j < K - 1; ++ j) {
            cur += B[B.size() - 1 - j];
        }
        ans = max(ans, cur);
        B.push_back(2 * PI * A[i].first * A[i].second);
        sort(B.begin(), B.end());
    }
    printf("%.9lf\n", ans);
}

int main() {
    int T;
    scanf("%d", &T);
    for (int test = 1; test <= T; ++ test) {
        A.clear();
        cin >> N >> K;
        for (int i = 0; i < N; ++ i) {
            int r, h;
            cin >> r >> h;
            A.push_back({(double)r, (double)h});
        }
        printf("Case #%d: ", test);
        solve();
    }
    return 0;
}
