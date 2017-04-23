#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <map>
#include <cstdio>

using namespace std;

int R, C;

char A[30][30];

struct Rec {
    char c;
    int l, r, u, d;
};

map<char, Rec> all;
vector<char> CC;
void update(int x, int y) {
    if (all.find(A[x][y]) == all.end()) {
        Rec temp;
        temp.l = temp.r = y;
        temp.u = temp.d = x;
        all[A[x][y]] = temp;
        CC.push_back(A[x][y]);
    }
    else {
        Rec temp = all[A[x][y]];
        temp.l = min(temp.l, y);
        temp.r = max(temp.r, y);
        temp.u = min(temp.u, x);
        temp.d = max(temp.d, x);
        all[A[x][y]] = temp;
    }
}

bool conflict(const Rec &P, const Rec &Q) {
    if (P.r < Q.l || Q.r < P.l) return false;
    if (P.d < Q.u || Q.d < P.u) return false;
    return true;
}

void solve() {
    all.clear();
    CC.clear();
    for (int x = 0; x < R; ++ x) {
        for (int y = 0; y < C; ++ y) {
            if (A[x][y] != '?')
                update(x, y);
        }
    }
    for (int i = 0; i < CC.size(); ++ i) {
        Rec P = all[CC[i]];
        while (P.l > 0) {
            -- P.l;
            bool extend = true;
            for (int j = 0; j < CC.size(); ++ j)
                if (i != j && conflict(P, all[CC[j]])) {
                    extend = false;
                    break;
                }
            if (!extend) {
                ++ P.l;
                break;
            }
        }
        while (P.r < C - 1) {
            ++ P.r;
            bool extend = true;
            for (int j = 0; j < CC.size(); ++ j)
                if (i != j && conflict(P, all[CC[j]])) {
                    extend = false;
                    break;
                }
            if (!extend) {
                -- P.r;
                break;
            }
        }
        while (P.u > 0) {
            -- P.u;
            bool extend = true;
            for (int j = 0; j < CC.size(); ++ j)
                if (i != j && conflict(P, all[CC[j]])) {
                    extend = false;
                    break;
                }
            if (!extend) {
                ++ P.u;
                break;
            }
        }
        while (P.d < R - 1) {
            ++ P.d;
            bool extend = true;
            for (int j = 0; j < CC.size(); ++ j)
                if (i != j && conflict(P, all[CC[j]])) {
                    extend = false;
                    break;
                }
            if (!extend) {
                -- P.d;
                break;
            }
        }
        all[CC[i]] = P;
        for (int x = P.u; x <= P.d; ++ x)
            for (int y = P.l; y <= P.r; ++ y)
                A[x][y] = CC[i];
        /*
        for (int i = 0; i < R; ++ i) {
            for (int j = 0; j < C; ++ j)
                printf("%c", A[i][j]);
            printf("\n");
        }
        */
    }
    for (int i = 0; i < R; ++ i) {
        for (int j = 0; j < C; ++ j)
            printf("%c", A[i][j]);
        printf("\n");
    }
}

int main() {
    int T;
    scanf("%d", &T);
    for (int test = 1; test <= T; ++ test) {
        scanf("%d %d", &R, &C);
        for (int i = 0; i < R; ++ i)
            scanf("%s", A[i]);
        printf("Case #%d:\n", test);
        solve();
    }
    return 0;
}
