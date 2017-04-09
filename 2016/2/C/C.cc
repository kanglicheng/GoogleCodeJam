#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <set>
#include <map>

using namespace std;

const int maxN = 20;

bool A[maxN][maxN];

int R, C;

vector< pair<int, int> > P;


void findXY(int K, int &x, int &y, int &d) {
    -- K;
    if (K < C) {
        x = 0;
        y = K;
        d = 0;
        return;
    }
    if (K < R + C) {
        x = K - C;
        y = C - 1;
        d = 1;
        return;
    }
    if (K < R + C + C) {
        x = R - 1;
        y = (C - 1) - (K - R - C);
        d = 2;
        return;
    }
    x = (R - 1) - (K - R - C - C);
    y = 0;
    d = 3;
    return;
}

// true --> /
// false --> \

bool path(int x, int y, int xx, int yy, int d, int dd) {
    if (dd == 0)
        dd = 2;
    else if (dd == 1)
        dd = 3;
    else if (dd == 2)
        dd = 0;
    else
        dd = 1;

    while (1) {
        bool flag = (x == xx && y == yy);
        if (A[x][y]) {
            if (d == 0) {
                -- y;
                d = 1;
            }
            else if (d == 3) {
                -- x;
                d = 2;
            }
            else if (d == 1) {
                ++ x;
                d = 0;
            }
            else {
                ++ y;
                d = 3;
            }
        }
        else {
            if (d == 0) {
                ++ y;
                d = 3;
            }
            else if (d == 1) {
                -- x;
                d = 2;
            }
            else if (d == 2) {
                -- y;
                d = 1;
            }
            else {
                ++ x;
                d = 0;
            }
        }
        //cout << "go: " << x << " " << y << " " << d << endl;

        if (flag && d == dd) return true;
        if (x < 0 || x >= R || y < 0 || y >= C) return false;
    }
}

bool check() {
    //cout << "check" << endl;
    for (int i = 0; i < P.size(); ++ i) {
        int S = P[i].first;
        int T = P[i].second;
        //cout << S << " " << T << endl;
        int x, y, xx, yy, d, dd;
        findXY(S, x, y, d);
        findXY(T, xx, yy, dd);
        //cout << S << " " << x << " " << y << " " << d << endl;
        //cout << T << " " << xx << " " << yy << " " << dd << endl;
        if (!path(x, y, xx, yy, d, dd)) return false;
    }
    return true;
}

void solve() {
    int K = 1 << (R * C);
    for (int M = 0; M < K; ++ M) {
        for (int i = 0; i < R; ++ i)
            for (int j = 0; j < C; ++ j) {
                int k = i * C + j;
                if (M & (1 << k))
                    A[i][j] = true;
                else
                    A[i][j] = false;
            }

        if (check()) {
            for (int i = 0; i < R; ++ i) {
                for (int j = 0; j < C; ++ j)
                    cout << (A[i][j] ? "/" : "\\");
                cout << endl;
            }
            return;
        }
    }
    cout << "IMPOSSIBLE" << endl;
}

int main() {
    int T;
    int test = 1;
    for (cin >> T; T --;) {
        P.clear();
        cin >> R >> C;
        for (int i = 0; i < R + C; ++ i) {
            int x, y;
            cin >> x >> y;
            P.push_back(make_pair(x, y));
        }
        cout << "Case #" << test ++ << ":" << endl;
        solve();
    }
    return 0;
}
