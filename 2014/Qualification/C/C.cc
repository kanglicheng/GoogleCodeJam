#include <iostream>
#include <string>
#include <vector>
#include <algorithm>

using namespace std;

const int maxRC = 50;

int R, C, M;

//true -> empty, false -> mine
bool board[maxRC][maxRC];

const int dx[] = {0, 0, 1, -1, 1, 1, -1, -1};
const int dy[] = {1, -1, 0, 0, 1, -1, 1, -1};

bool visit[maxRC][maxRC];

void dfs(int x, int y) {
    visit[x][y] = false;    
    for (int i = 0; i < 8; ++ i) {
        int xx = x + dx[i];
        int yy = y + dy[i];
        if (xx >= 0 && xx < R && yy >= 0 && yy < C)
            if (!board[xx][yy]) return;
    }
    for (int i = 0; i < 8; ++ i) {
        int xx = x + dx[i];
        int yy = y + dy[i];
        if (xx >= 0 && xx < R && yy >= 0 && yy < C)
            if (visit[xx][yy])
                dfs(xx, yy);
    }
}

bool check() {
    if (!board[R - 1][C - 1]) return false;
    memset(visit, true, sizeof(visit));
    dfs(R - 1, C - 1);
    int total = 0;
    int totalM = 0;
    for (int i = 0; i < R; ++ i)
        for (int j = 0; j < C; ++ j) {
            total += !visit[i][j];
            totalM += !board[i][j];
        }
    return total + totalM == R * C;
}

bool search(int mine, int r, int last) {
    if (mine == 0) {
        if (!check()) return false;
        for (int i = 0; i < R; ++ i) {
            for (int j = 0; j < C; ++ j)
                if (i == R - 1 && j == C - 1)
                    cout << "c";
                else if (board[i][j])
                    cout << ".";
                else
                    cout << "*";
            cout << endl;
        }
        return true;
    }
    if (r == R) return false;
    int curMax = min(mine, min(C, last));
    for (int i = 0; i < C; ++ i)
        board[r][i] = (i >= curMax);
    for (int k = curMax - 1; k >= 0; -- k) {
        if (search(mine - (k + 1), r + 1, k + 1))
            return true;
        board[r][k] = true;
    }
    return false;
}

int main() {
    int T;
    cin >> T;
    for (int test = 1; test <= T; ++ test) {
        cout << "Case #" << test << ":" << endl;
        cin >> R >> C >> M;
        memset(board, true, sizeof(board));
        int startR = 0;
        while (M >= 3 * C - 1) {
            M -= C;
            for (int i = 0; i < C; ++ i)
                board[startR][i] = false;
            ++ startR;
        }
        if (!search(M, startR, maxRC))
            cout << "Impossible" << endl;
    }
	return 0;
}
