#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <cstdio>

using namespace std;

string S;

int main() {
    int T;
    int test = 1;
    for (cin >> T; T --;) {
        cin >> S;
        string ret = "";
        for (int i = 0; i < S.size(); ++ i)
            ret = max(ret + S[i], S[i] + ret);
        cout << "Case #" << test ++ << ": " << ret << endl;
    }
    return 0;
}
