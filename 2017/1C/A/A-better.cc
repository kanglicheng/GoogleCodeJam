#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <map>
#include <cstdio>
#include <set>
#include <cmath>
#include <queue>
#include <functional>

using namespace std;

vector<pair<double, double>> A;

const double PI = atan(1.0) * 4;

int N, K;

void solve() {
    sort(A.begin(), A.end());
    priority_queue<double, vector<double>, greater<double>> topK;
    double ans = 0.0;
    double area = 0.0;
    for (int i = 0; i < K - 1; ++ i) {
        double side_area = 2 * PI * A[i].first * A[i].second;
        topK.push(side_area);
        area += side_area;
    }

    for (int i = K - 1; i < N; ++ i) {
        double side_area = 2 * PI * A[i].first * A[i].second;
        double top_area = PI * A[i].first * A[i].first;
        ans = max(ans, area + side_area + top_area);
        area += side_area;
        topK.push(side_area);
        area -= topK.top();
        topK.pop();
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
