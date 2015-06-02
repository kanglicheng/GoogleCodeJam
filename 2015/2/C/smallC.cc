#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>
#include <string>
#include <map>
#include <unordered_set>
#include <unordered_map>

using namespace std;

int N;
unordered_map<string, int> hash_f;
int hash_count;
vector<int> A[20];

int flag[1000 * 2 + 20 * 10];

int small_solve() {
    int ret = 1000000000;
    for (int mask = 0; mask < (1 << N); ++ mask) {
        int en = mask & 1;
        int fr = (mask >> 1) & 1;
        if (!(en == 0 && fr == 1)) continue;
        memset(flag, 0, sizeof(flag));
        for (int i = 0; i < N; ++ i) {
            int k = (mask >> i) & 1;
            for (int j = 0; j < A[i].size(); ++ j)
                flag[A[i][j]] |= 1 << k;
        }
        int count = 0;
        for (int i = 1; i <= hash_count; ++ i)
            if (flag[i] == 3) ++ count;
        ret = min(ret, count);
    }
    return ret;
}

int hashing(const string &s) {
    if (hash_f.find(s) != hash_f.end())
        return hash_f[s];
    ++ hash_count;
    hash_f[s] = hash_count;
    return hash_count;
}

vector<int> INPUT() {
    char c;
    string s;
    vector<int> ret;
    while (cin.get(c)) {
        if (c == '\n') break;
        if (c == ' ') {
            ret.push_back(hashing(s));
            s = "";
        }
        else
            s = s + c;
    }
    if (s != "")
        ret.push_back(hashing(s));
    return ret;
}

int main() {
    int T;
    scanf("%d", &T);
    for (int test = 1; test <= T; ++ test) {
        hash_f.clear(); hash_count = 0;

        scanf("%d", &N);
        cin.get();
        for (int i = 0; i < N; ++ i) {
            A[i] = INPUT();

        }
        fprintf(stderr, "case %d\n", test);
        printf("Case #%d: %d\n", test, small_solve());
    }
    return 0;
}
