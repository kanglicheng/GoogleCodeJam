#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

int N;
vector<int> A;

int f() {
    int ret = 10000000;
    for (int baseline = 1; baseline <= 1000; ++ baseline) {
        int total = baseline;
        for (int j = 0; j < N; ++ j)
            total += (A[j] - 1) / baseline;
        if (total < ret) ret = total;
    }
    return ret;
}

int main() {
    int T;
    scanf("%d", &T);    
    for (int test = 1; test <= T; ++ test) {
        scanf("%d", &N);
        A.clear();
        for (int i = 0; i < N; ++ i) {
            int k;
            scanf("%d", &k);
            A.push_back(k);
        }
        int ret = f();
        printf("Case #%d: %d\n", test, ret);
    }
    return 0;
}