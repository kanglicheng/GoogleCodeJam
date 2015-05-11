#include <cstdio>
#include <iostream>
#include <cstring>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

int K, L, S;

char keyboard[100];

char word[1000];

double solve() {
    int count[26];
    memset(count, 0, sizeof(count));
    for (int i = 0; i < K; ++ i)
        ++ count[keyboard[i] - 'A'];

    for (int i = 0; i < L; ++ i)
        if (count[word[i] - 'A'] == 0) return 0.00;

    double prob[26];
    for (int i = 0; i < 26; ++ i)
        prob[i] = (double)count[i] / K;

    int suffix = 0;
    for (int i = 1; i < L; ++ i) {
        int len = L - i;
        bool flag = true;
        for (int j = 0; j < len; ++ j)
            if (word[i + j] != word[j]) {
                flag = false;
                break;
            }
        if (flag) {
            suffix = len;
            break;
        }
    }

    int upper = 1 + (S - L) / (L - suffix);
    double ret = 1.00;
    for (int i = 0; i < L; ++ i)
        ret = ret * prob[word[i] - 'A'];
    ret = ret * (S - L + 1);
    ret = (double)upper - ret;
    return ret;
}

int main() {
    int T;
    scanf("%d", &T);
    for (int test = 1; test <= T; ++ test) {
        scanf("%d%d%d", &K, &L, &S);
        scanf("%s", keyboard);
        scanf("%s", word);
        printf("Case #%d: %.10lf\n", test, solve());
    }
    return 0;
}
