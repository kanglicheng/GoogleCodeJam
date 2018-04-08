#include <iostream>
#include <algorithm>
#include <vector>

using namespace std;

long long D;
vector<bool> seq;

long long damage() {
    long long total = 0;
    long long d = 1;
    for (int i = 0; i < seq.size(); ++ i) {
        if (seq[i]) {
            total += d;
        } else {
            d <<= 1;
        }
    }
    return total;
}

void solve() {
    int ans = 0;
    while (damage() > D) {
        bool flag = false;
        for (int i = seq.size() - 2; i >= 0; --i) {
            if (!seq[i] && seq[i + 1]) {
                ++ ans;
                seq[i] = true;
                seq[i + 1] = false;
                flag = true;
                break;
            }
        }
        if (!flag) {
            cout << "IMPOSSIBLE" << endl;
            return;
        }
    }
    cout << ans << endl;
}

int main() {
    int T;
    cin >> T;
    for (int test = 1; test <= T; ++ test) {
        string temp;
        cin >> D >> temp;
        seq.clear();
        for (int i = 0; i < temp.size(); ++ i) {
            seq.push_back(temp[i] == 'S');
        }
        cout << "Case #" << test << ": ";
        solve();
    }
    return 0;
}
