#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cstring>

using namespace std;

int A;

bool state[30][30];

void solve(int x, int y) {
    memset(state, false, sizeof(state));
    while (1) {
        int best_x = 1, best_y = 1;
        int max_pr = -1;
        for (int i = 1; i < x - 1; ++ i)
            for (int j = 1; j < y - 1; ++ j) {
                int c = 0;
                for (int dx = -1; dx <= 1; ++ dx)
                    for (int dy = -1; dy <= 1; ++ dy)
                        if (!state[i + dx][j + dy])
                            ++ c;
                if (c > max_pr) {
                    max_pr = c;
                    best_x = i;
                    best_y = j;
                }
            }
        cout << best_x + 1 << " " << best_y + 1 << endl << flush;

        int xx, yy;
        cin >> xx >> yy;
        if (xx == 0 && yy == 0) return;
        if (xx == -1 && yy == -1) {
            cerr << "Error!" << endl;
            return;
        }
        state[xx - 1][yy - 1] = true;
    }
}

int main() {
    int T;
    cin >> T;
    for (int test = 1; test <= T; ++ test) {
        cin >> A;
        if (A == 20) {
            solve(4, 5);
        } else if (A == 200) {
            solve(20, 10);
        }
    }
    return 0;
}
