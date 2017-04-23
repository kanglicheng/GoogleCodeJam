#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cstdio>

using namespace std;

#define MAXN 105

// empty -- 0
// + -- 1
// x -- 2
// o -- 3

int A[MAXN][MAXN];

int N;

int O[MAXN][MAXN];

bool check2(int x, int y) {
    for (int k = 0; k < N; ++ k) {
        if (k != y && A[x][k] != 1 && A[x][k] != 0) return false;
        if (k != x && A[k][y] != 1 && A[k][y] != 0) return false;
    }
    return true;
}

bool check1(int x, int y) {
    for (int k = 1; x + k < N && y + k < N; ++ k)
        if (A[x + k][y + k] != 2 && A[x + k][y + k] != 0) return false;
    for (int k = 1; x - k >= 0 && y - k >= 0; ++ k)
        if (A[x - k][y - k] != 2 && A[x - k][y - k] != 0) return false;
    for (int k = 1; x + k < N && y - k >= 0; ++ k)
        if (A[x + k][y - k] != 2 && A[x + k][y - k] != 0) return false;
    for (int k = 1; x - k >= 0 && y + k < N; ++ k)
        if (A[x - k][y + k] != 2 && A[x - k][y + k] != 0) return false;
    return true;
}

bool check3(int x, int y) {
    return check1(x, y) && check2(x, y);
}

void solve() {
    for (int k = 0; k < N; ++ k) {
        for (int x = k; x < N - k; ++ x) {
            if (A[x][k] == 0 && check1(x, k))
                A[x][k] = 1;
            if (A[x][N - 1 - k] == 0 && check1(x, N - 1 - k))
                A[x][N - 1 - k] = 1;
        }
        for (int y = k; y < N - k; ++ y) {
            if (A[k][y] == 0 && check1(k, y))
                A[k][y] = 1;
            if (A[N - 1 - k][y] == 0 && check1(N - 1 - k, y))
                A[N - 1 - k][y] = 1;
        }
    }

    for (int x = 0; x < N; ++ x)
        for (int y = 0; y < N; ++ y) {
            if (check3(x, y))
                A[x][y] = 3;
        }

    for (int x = 0; x < N; ++ x)
        for (int y = 0; y < N; ++ y) {
            if (A[x][y] == 0 && check2(x, y))
                A[x][y] = 2;
        }

    int total = 0;
    for (int x = 0; x < N; ++ x)
        for (int y = 0; y < N; ++ y)
            if (A[x][y] != O[x][y])
                ++ total;

    int score = 0;
    //printf("\n");
    for (int x = 0; x < N; ++ x) {
        for (int y = 0; y < N; ++ y) {
            score += ((A[x][y] == 1 || A[x][y] == 2) ? 1 : (A[x][y] == 3 ? 2 : 0));
            //printf("%d", A[x][y]);
        }
        //printf("\n");
    }
    //printf("%d %d\n", 2 * N, score);

    //printf("%d %d\n", 2 * N, total);
    printf("%d %d\n", score, total);
    for (int x = 0; x < N; ++ x)
        for (int y = 0; y < N; ++ y)
            if (A[x][y] != O[x][y])
                printf("%c %d %d\n", (A[x][y] == 1 ? '+' : (A[x][y] == 2 ? 'x' : 'o')), x + 1, y + 1);
}

int main() {
    int T;
    scanf("%d", &T);
    for (int test = 1; test <= T; ++ test) {
        int M;
        scanf("%d %d", &N, &M);
        memset(A, 0, sizeof(A));
        memset(O, 0, sizeof(O));
        while (M --){
            char c;
            int x, y;
            getchar();
            scanf("%c %d %d", &c, &x, &y);
            -- x; -- y;
            A[x][y] = O[x][y] = (c == 'o' ? 3 : (c == '+' ? 1 : 2));
        }
        printf("Case #%d: ", test);
        solve();
    }
    return 0;
}
