#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <map>
#include <cstdio>
#include <set>
#include <cmath>

using namespace std;


#define MAXN    60

double F[MAXN][MAXN];

double compute_prob(const vector<double> &P, const int K) {
    int N = P.size();
    for (int i = 0; i <= N; ++ i)
        for (int j = 0; j <= N; ++ j)
            F[i][j] = 0.0;
    F[0][0] = 1.0;


    for (int i = 1; i <= N; ++ i) {
        F[i][0] = F[i - 1][0] * (1.0 - P[i - 1]);
        for (int j = 1; j <= i; ++ j)
            F[i][j] = F[i - 1][j - 1] * P[i - 1] + F[i - 1][j] * (1.0 - P[i - 1]);
    }

    /*
    for (int i = 0; i <= N; ++ i) {
        for (int j = 0; j <= i; ++ j)
            cout << F[i][j] << " ";
        cout << endl;
    }
    */


    double ans = 0.0;
    for (int k = K; k <= N; ++ k)
        ans += F[N][k];
    return ans;
}

void allocate_prob(vector<double> &P, double &U) {
    int N = P.size();
    if (U == 0.0) return;
    if (N == 1) {
        if (P[0] + U > 1.0) {
            U -= (1.0 - P[0]);
            P[0] = 1.0;
        }
        else {
            P[0] += U;
            U = 0.0;
        }
        return;
    }
    double last = P[0];
    for (int i = 1; i < N; ++ i) {
        double need = (P[i] - last) * i;
        if (U >= need) {
            last = P[i];
            U -= need;
        }
        else {
            last += U / i;
            U = 0.0;
            break;
        }
    }
    if (U > 0.0) {
        if (U / N + last > 1.0) {
            U -= (1.0 - last) * N;
            last = 1.0;
        }
        else {
            last += U / N;
            U = 0.0;
        }
    }

    for (int j = 0; j < N; ++ j)
        P[j] = max(last, P[j]);

    /*
    double ans = 1.0;
    for (int j = i; j < N; ++ j)
        ans *= P[j];
    for (int j = 0; j < i; ++ j)
        ans *= last;
    return ans;
    */
}

vector<double> P;
int N, K;
double U;

double solve() {
    double ans = 0.0;
    sort(P.begin(), P.end());
    for (int k = N - 1; k >= 0; -- k) {
        vector<double> p;
        for (int i = k; i < N; ++ i)
            p.push_back(P[i]);
        /*
        for (const double &pr : p)
            cout << pr << " ";
        cout << endl;
        */
        double u = U;
        allocate_prob(p, u);
        /*
        for (const double &pr : p)
            cout << pr << " ";
        cout << endl;
        */
        if (u > 0.0 && k > 0) {
            for (int i = 0; i < k - 1; ++ i)
                p.push_back(P[i]);
            p.push_back(min(1.0, u + P[k - 1]));
        }
        else {
            for (int i = 0; i < k; ++ i)
                p.push_back(P[i]);
        }
        /*
        for (const double &pr : p)
            cout << pr << " ";
        cout << endl;
        */
        double pr = compute_prob(p, K);
        //printf("Pr = %.10lf\n", pr);
        //cout << k << " " << pr << endl;
        //cout << pr << endl;
        ans = max(ans, pr);
    }
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
        double ans = solve();
        printf("Case #%d: %.20lf\n", test, ans);
    }
    return 0;
}
