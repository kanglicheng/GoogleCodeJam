#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cstdio>

using namespace std;

char N[20];

char tidy[20];

int L;

bool search(int k, char last_digit, bool arbitrary) {
    if (k == L) return true;
    char start = (!arbitrary) ? N[k] : '9';
    for (char digit = start; digit >= last_digit; -- digit) {
        arbitrary = arbitrary || digit != start;
        tidy[k] = digit;
        if (search(k + 1, digit, arbitrary)) return true;
    }
    return false;
}

void solve() {
    L = strlen(N);
    /*
    for (int i = 0; i < L; ++ i)
        tidy[i] = N[i];
    */
    search(0, '0', false);
    int k = 0;
    while (tidy[k] == '0') ++ k;
    for (int i = k; i < L; ++ i)
        printf("%c", tidy[i]);
    printf("\n");
}

int main() {
    int T;
    scanf("%d", &T);
    for (int test = 1; test <= T; ++ test) {
        scanf("%s", N);
        printf("Case #%d: ", test);
        solve();
    }
    return 0;
}
