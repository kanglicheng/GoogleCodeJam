#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#include <string>
#include <unordered_set>

using namespace std;

vector<string> A[20];
int N;
int flag[20];
vector<string> commonE[20];
vector<string> commonF[20];
unordered_set<string> common;

// 1 --> English
// -1 --> French

int ret;
unordered_set<string> hashing;

int count() {
    int ret = common.size();
    unordered_set<string> hash;
    for (int i = 2; i < N; ++ i)
        if (flag[i] == -1) {
            for (int j = 0; j < commonE[i].size(); ++ j)
                if (common.find(commonE[i][j]) == common.end()) {
                        hash.insert(A[i][j]);
                    }
                }
        }
        else {

        }
    return ret;
}

void dfs(int depth) {
    if (depth == N) {
        int k = count();
        if (k < ret)
            ret = k;
        return;
    }
    flag[depth] = -1;
    dfs(depth + 1);
    flag[depth] = 1;
    dfs(depth + 1);
}

void preprocess() {
    unordered_set<string> hashF;
    unordered_set<string> hashE;

    common.clear();

    for (int i = 0; i < A[0].size(); ++ i)
        hashE.insert(A[0][i]);
    for (int i = 0; i < A[1].size(); ++ i) {
        hashF.insert(A[1][i]);
        if (hashE.find(A[1][i]) != hashE.end())
            common.insert(A[1][i]);
    }

    for (int i = 2; i < N; ++ i) {
        commonE[i].clear();
        commonF[i].clear();
        for (int j = 0; j < A[i].size(); ++ j)
            if (hashE.find(A[i][j]) != hashE.end())
                commonE[i].push_back(A[i][j]);
        for (int j = 0; j < A[i].size(); ++ j)
            if (hashF.find(A[i][j]) != hashF.end())
                commonF[i].push_back(A[i][j]);

    }

}

int small_solve() {
    hashing.clear();
    ret = 1000000000;
    flag[0] = 1;
    for (int j = 0; j < A[0].size(); ++ j)
        hashing.insert(A[0][j]);
    flag[1] = -1;
    dfs(2);
    return ret;
}

int main() {
    int T;
    scanf("%d", &T);
    for (int test = 1; test <= T; ++ test) {
        scanf("%d", &N);
        string temp;
        getline(cin, temp);
        for (int i = 0; i < N; ++ i) {
            getline(cin, temp);
            A[i].clear();
            while (1) {
                size_t pos = temp.find(" ");
                if (pos == string::npos) {
                    A[i].push_back(temp);
                    break;
                }
                A[i].push_back(temp.substr(0, pos));
                temp.erase(temp.begin(), temp.begin() + pos + 1);
            }
            /*
            for (int j = 0; j < A[i].size(); ++ j)
                cout << A[i][j] << endl;
            */
        }
        fprintf(stderr, "case %d\n", test);
        printf("Case #%d: %d\n", test, small_solve());
    }
    return 0;
}
