#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cstdio>

using namespace std;

#define MAXN 2000

char S[MAXN];
int K;

int check() {
    int ret = 0;
    int len = strlen(S);
    for (int i = 0; i < len - K + 1; ++ i) {
        if (S[i] == '-') {
            ++ ret;
            for (int j = 0; j < K; ++ j)
                S[i + j] = (S[i + j] == '+' ? '-' : '+');
        }
    }
    for (int i = 0; i < len; ++ i)
        if (S[i] == '-')
            return -1;
    return ret;
}

int main() {
    int T;
    scanf("%d", &T);
    for (int test = 1; test <= T; ++ test) {
        scanf("%s %d", S, &K);
        int res = check();
        printf("Case #%d: ", test);
        if (res == -1)
            printf("IMPOSSIBLE\n");
        else
            printf("%d\n", res);
    }
    return 0;
}
