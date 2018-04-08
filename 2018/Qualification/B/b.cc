#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>

using namespace std;

int N;
vector<int> odd, even;

void solve() {
    sort(odd.begin(), odd.end());
    sort(even.begin(), even.end());
    /*
    for (int i = 0; i < odd.size(); ++ i) {
        cout << odd[i] << endl;
    }
    for (int i = 0; i < even.size(); ++ i) {
        cout << even[i] << endl;
    }
    */
    int l = 0, r = 0;
    for (int i = 1; i < N; ++ i) {
        if (i & 1) {
            if (odd[l] < even[r]) {
                cout << i - 1 << endl;
                return;
            }
            ++ r;
        } else {
            if (even[r] < odd[l]) {
                cout << i - 1 << endl;
                return;
            }
            ++ l;
        }
    }
    cout << "OK" << endl;
}

int main() {
    int T;
    cin >> T;
    for (int test = 1; test <= T; ++ test) {
        odd.clear();
        even.clear();

        cin >> N;
        for (int i = 0; i < N; ++ i) {
            int k;
            scanf("%d", &k);
            if (i & 1) {
                odd.push_back(k);
            } else {
                even.push_back(k);
            }
        }
        cout << "Case #" << test << ": ";
        solve();
    }
    return 0;
}
