#include <iostream>
#include <string>
#include <algorithm>
#include <vector>
#include <unordered_set>

using namespace std;

int N, L;
vector<string> A, B;
unordered_set<string> Hash;
vector<bool> flip;

bool check() {
    for (int i = 0; i < N; ++ i) {
        string S = A[i];
        for (int j = 0; j < L; ++ j)
            if (flip[j])
                S[j] = char(int('1') + int('0') - int(S[j]));
        if (Hash.find(S) == Hash.end())
            return false;
    }
    return true;
}

int solve() {
    cin >> N >> L;
    A.clear(); B.clear();
    Hash.clear();
    for (int i = 0; i < N; ++ i) {
        string temp;
        cin >> temp;
        A.push_back(temp);
    }
    for (int i = 0; i < N; ++ i) {
        string temp;
        cin >> temp;
        B.push_back(temp);
        Hash.insert(temp);
    }
    string left = A[0];
    int ret = -1;
    for (int i = 0; i < N; ++ i) {
        string right = B[i];
        flip.clear();
        int total = 0;
        for (int j = 0; j < L; ++ j)
            if (left[j] != right[j]) {
                ++ total;
                flip.push_back(true);
            }
            else
                flip.push_back(false);
        if (ret == -1 || total < ret)
            if (check())
                ret = total;
    }
    return ret;
}

int main() {
    int test;
    cin >> test;
    for (int i = 1; i <= test; ++ i) {
        cout << "Case #" << i << ": ";
        int ans = solve();
        if (ans == -1)
            cout << "NOT POSSIBLE" << endl;
        else
            cout << ans << endl;
    }
    return 0;
}

/*
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
*/
