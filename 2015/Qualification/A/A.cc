#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

vector<int> A;

int f() {
    int total = A[0];
    int ret = 0;
    for (int i = 1; i < A.size(); ++ i) {
        if (i > total) {
            ret += i - total;
            total = i;
        }
        total += A[i];
    }
    return ret;
}

int main() {
    int T;
    scanf("%d", &T);    
    char temp[1200];
    for (int test = 1; test <= T; ++ test) {
        int n;
        scanf("%d %s", &n, temp);
        A.clear();
        for (int i = 0; i < strlen(temp); ++ i)
            A.push_back(temp[i] - '0');
        int res = f();
        printf("Case #%d: %d\n", test, res);
    }
    return 0;
}