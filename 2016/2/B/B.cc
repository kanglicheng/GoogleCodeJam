#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <set>
#include <map>

using namespace std;

int N, K;

vector<double> A;

double F[310][310];

double dp(vector<double> P) {
    memset(F, 0, sizeof(F));
    F[0][0] = 1.0;
    for (int i = 1; i <= K; ++ i) {
        F[i][i] = F[i - 1][i - 1] * (P[i - 1]);
        F[i][0] = F[i - 1][0] * (1.0 - P[i - 1]);
        for (int j = 1; j < i; ++ j) {
            if (j > 0)
                F[i][j] += F[i - 1][j - 1] * P[i - 1];
            if (i - j > 0)
                F[i][j] += F[i - 1][j] * (1.0 - P[i - 1]);
        }
    }
    return F[K][K >> 1];
}

void solve() {
    sort(A.begin(), A.end());
    vector<double> P;
    double ret = 0.0;
    for (int i = 0; i <= K; ++ i) {
        P.clear();
        for (int j = 0; j < i; ++ j)
            P.push_back(A[j]);
        for (int j = N - (K - i); j < N; ++ j)
            P.push_back(A[j]);
        //cout << P.size() << " " << K << endl;
        ret = max(ret, dp(P));
    }
    printf("%.8lf\n", ret);
}

int main() {
    int T;
    int test = 1;
    for (cin >> T; T --;) {
        cin >> N >> K;
        A.clear();
        for (int i = 0; i < N; ++ i) {
            double x;
            cin >> x;
            A.push_back(x);
        }
        cout << "Case #" << test ++ << ": ";
        solve();
    }
    return 0;
}
