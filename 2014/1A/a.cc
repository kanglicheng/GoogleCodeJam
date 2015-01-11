#include <cstdio>
#include <cstring>
#include <algorithm>
#include <vector>

using namespace std;

const int maxL = 40;
//const int maxN = 150;

int N;
int L;

vector< vector<bool> > A;
vector< vector<bool> > B;

int countA[maxL];
int countB[maxL];

// -1 --> impossible
// otherwise --> minimum number of switches
int dfs(int ptr, int switches) {
    if (ptr == L) {
        
        return switches;
    }
    int l = countA[ptr]; 
    int r = countB[ptr];

    int flag = -1;

    if (l == r)
        flag = dfs(ptr + 1, switches);

    if (flag == -1 && N - l == r) {
        for (int i = 0; i < N; ++ i)
            A[ptr][i] = !A[ptr][i];
        flag = dfs(ptr + 1, switches + 1);
        for (int i = 0; i < N; ++ i)
            A[ptr][i] = !A[ptr][i];
    }

    return flag;
}

int main() {
    int T;
    scanf("%d", &T);    
    for (int test = 1; test <= T; ++ test) {
        printf("Case #%d: ", test);
        scanf("%d %d", &N, &L);
        A.clear();
        B.clear();
        for (int i = 0; i < L; ++ i) {
            vector<bool> x;
            x.clear();
            A.push_back(x);
            B.push_back(x);
        }
        for (int i = 0; i < N; ++ i) {
            char temp[50];
            scanf("%s", temp);
            for (int j = 0; j < L; ++ j)
                A[j].push_back(temp[j] == '1');
        }
        for (int i = 0; i < N; ++ i) {
            char temp[50];
            scanf("%s", temp);
            for (int j = 0; j < L; ++ j)
                B[j].push_back(temp[j] == '1');
        }

        memset(countA, 0, sizeof(countA));
        memset(countB, 0, sizeof(countB));

        for (int i = 0; i < L; ++ i)
            for (int j = 0; j < N; ++ j) {
                if (A[i][j])
                    countA[i] += 1;
                if (B[i][j])
                    countB[i] += 1;
            }
    }
    return 0;
}
