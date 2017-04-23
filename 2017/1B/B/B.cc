#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <map>
#include <cstdio>
#include <set>
#include <cmath>

using namespace std;

int N, R, O, Y, G, B, V;

string fill(int A, int B, int C, const string &a, const string &b, const string &c) {
    string ret = "";
    for (int k = C - A + B; k > 0; k --)
        ret += a + b + c;
    for (int k = A - C; k > 0; k --)
        ret += a + b;
    for (int k = A - B; k > 0; k --)
        ret += a + c;
    return ret;
}

string make_ring(int Y, int B, int R) {
    if (Y >= B && Y >= R) {
        if (B >= R)
            return fill(Y, B, R, "Y", "B", "R");
        return fill(Y, R, B, "Y", "R", "B");
    }
    if (R >= Y && R >= B) {
        if (Y >= B)
            return fill(R, Y, B, "R", "Y", "B");
        return fill(R, B, Y, "R", "B", "Y");
    }
    if (Y >= R)
        return fill(B, Y, R, "B", "Y", "R");
    return fill(B, R, Y, "B", "R", "Y");
}

string solve() {
    if (V != 0) {
        if (V == Y) {
            if (V + Y == N) {
                string ans = "";
                while (V --)
                    ans += "VY";
                return ans;
            }
            return "IMPOSSIBLE";
        }
        Y -= V;
        if (Y <= 0) return "IMPOSSIBLE";
    }
    if (G != 0) {
        if (R == G) {
            if (R + G == N) {
                string ans = "";
                while (G --)
                    ans += "RG";
                return ans;
            }
            return "IMPOSSIBLE";
        }
        R -= G;
        if (R <= 0) return "IMPOSSIBLE";
    }
    if (O != 0) {
        if (B == O) {
            if (B + O == N) {
                string ans = "";
                while (O --)
                    ans += "BO";
                return ans;
            }
            return "IMPOSSIBLE";
        }
        B -= O;
        if (B <= 0) return "IMPOSSIBLE";
    }

    if (Y > R + B || B > Y + R || R > B + Y) return "IMPOSSIBLE";

    int ALL = Y + B + R;
    string ring = make_ring(Y, B, R);
    string ans = "";
    for (int i = 0; i < ALL; ++ i)
        if (ring[i] == 'Y') {
            while (V > 0) {
                ans += "YV";
                -- V;
            }
            ans += "Y";
        }
        else if (ring[i] == 'B') {
            while (O > 0) {
                ans += "BO";
                -- O;
            }
            ans += "B";
        }
        else if (ring[i] == 'R') {
            while (G > 0) {
                ans += "RG";
                -- G;
            }
            ans += "R";
        }
    return ans;
}

int main() {
    int T;
    scanf("%d", &T);
    for (int test = 1; test <= T; ++ test) {
        cin >> N >> R >> O >> Y >> G >> B >> V;
        printf("Case #%d: ", test);
        cout << solve() << endl;
    }
    return 0;
}
