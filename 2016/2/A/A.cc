#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <set>
#include <map>

using namespace std;

int N, P, R, S;

char A[14][5000];

string check(char top) {
    A[0][0] = top;
    for (int i = 1; i <= N; ++ i) {
        int m = 1 << (i - 1);
        for (int j = 0; j < m; ++ j)
            if (A[i - 1][j] == 'P') {
                A[i][j << 1] = 'P';
                A[i][(j << 1) + 1] = 'R';
            }
            else if (A[i - 1][j] == 'R') {
                A[i][j << 1] = 'R';
                A[i][(j << 1) + 1] = 'S';
            }
            else {
                A[i][j << 1] = 'P';
                A[i][(j << 1) + 1] = 'S';
            }
    }
    int PP = 0;
    int RR = 0;
    int SS = 0;
    int m = 1 << N;
    string ret = "";
    for (int i = 0; i < m; ++ i) {
        ret = ret + A[N][i];
        if (A[N][i] == 'P')
            ++ PP;
        else if (A[N][i] == 'R')
            ++ RR;
        else
            ++ SS;
    }
    //cout << PP << " " << RR << " " << SS << endl;
    if (P != PP || R != RR || S != SS) return "IMPOSSIBLE";
    return ret;
}

string find_min(string s) {
    if (s.size() == 1) return s;
    string A = find_min(s.substr(0, s.size() >> 1));
    string B = find_min(s.substr(s.size() >> 1));
    return min(A + B, B + A);
}

void solve() {
    vector<string> s;
    string S = check('P');
    if (S != "IMPOSSIBLE") s.push_back(find_min(S));
    S = check('R');
    if (S != "IMPOSSIBLE") s.push_back(find_min(S));
    S = check('S');
    if (S != "IMPOSSIBLE") s.push_back(find_min(S));
    if (s.empty()) {
        cout << "IMPOSSIBLE" << endl;
        return;
    }
    sort(s.begin(), s.end());
    cout << s[0] << endl;
}

int main() {
    int T;
    int test = 1;
    for (cin >> T; T --;) {
        cin >> N >> R >> P >> S;
        cout << "Case #" << test ++ << ": ";
        solve();
    }
    return 0;
}
