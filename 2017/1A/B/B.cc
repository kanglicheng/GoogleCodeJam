#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cstdio>
#include <set>
#include <cmath>

using namespace std;


const int MAXN = 60;

int A[MAXN][MAXN];
int R[MAXN];

struct interval {
    int l, r;
    int id;
    bool covered;
};

vector<interval> I;

struct cmp {
    bool operator() (const interval &A, const interval &B) {
        if (A.l < B.l) return true;
        if (A.l > B.l) return false;
        return (A.r < B.r);
    }
};

vector<int> Pos;

int N, P;

void solve() {
    Pos.clear(); I.clear();

    for (int i = 0; i < N; ++ i)
        for (int j = 0; j < P; ++ j) {
            interval temp;
            //temp.l = int(ceil((double)A[i][j] / ((double)R[i] * 1.1)));
            //temp.r = int((double)A[i][j] / ((double)R[i] * 0.9));
            temp.l = (A[i][j] * 10 - 1) / (11 * R[i]) + 1;
            temp.r = (A[i][j] * 10) / (9 * R[i]);
            //cout << A[i][j] << " " << temp.l << " " << temp.r << endl;
            temp.id = i;
            temp.covered = false;
            I.push_back(temp);
            Pos.push_back(temp.l); Pos.push_back(temp.r);
        }

    sort(Pos.begin(), Pos.end());
    sort(I.begin(), I.end(), cmp());
    int ans = 0;
    bool flag[MAXN];
    for (int x : Pos) {
        //cout << x << endl;
        memset(flag, false, sizeof(flag));
        int count = 0;
        vector<int> todo;
        for (int i = 0; i < I.size(); ++ i)
            if (!I[i].covered && !flag[I[i].id] && I[i].l <= x && I[i].r >= x) {
                flag[I[i].id] = true;
                todo.push_back(i);
                ++ count;
                if (count == N) break;
            }
        //cout << "count = " << count << endl;
        if (count == N) {
            ++ ans;
            for (int i = 0; i < todo.size(); ++ i)
                I[todo[i]].covered = true;
        }
    }

    printf("%d\n", ans);
}


int main() {
    int T;
    scanf("%d", &T);
    for (int test = 1; test <= T; ++ test) {
        scanf("%d %d", &N, &P);
        for (int i = 0; i < N; ++ i)
            scanf("%d", &R[i]);
        for (int i = 0; i < N; ++ i)
            for (int j = 0; j < P; ++ j)
                scanf("%d", &A[i][j]);
        printf("Case #%d: ", test);
        solve();
    }
    return 0;
}
