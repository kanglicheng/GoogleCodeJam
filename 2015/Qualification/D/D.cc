#include <cstring>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <queue>

using namespace std;

// return True --> GABRIEL
// R <= C
bool small_case(int R, int C, int X) {
    if (R == 1 && C == 1) return X == 1;
    if (R == 1 && C == 2) return X <= 2;
    if (R == 1 && C == 3) return X == 1;
    if (R == 1 && C == 4) return X <= 2;
    if (R == 2 && C == 2) return X <= 2;
    if (R == 2 && C == 3) return X <= 3;
    if (R == 2 && C == 4) return X <= 2;
    if (R == 3 && C == 3) return X == 1 || X == 3;
    if (R == 3 && C == 4) return true;
    if (R == 4 && C == 4) return X != 3;
    return true;
}

// return True --> GABRIEL
// R <= C
bool general(int R, int C, int X) {
    if (X == 1) return true;
    if ((R * C) % X != 0) return false;
    if (X == 2) return true;
    if (X > C) return false;
    if (X >= 2 * R) return false;
    if (X >= 7) return false;
    if (X == 5 && R == 3 && C == 5) return false; // W pentomino
    return true;
}

int main() {
    int T;
    scanf("%d", &T);    
    for (int test = 1; test <= T; ++ test) {
        int r, c, x;
        scanf("%d %d %d", &x, &r, &c);
        if (r > c) {
            int k = r; r = c; c = k;
        }
        //bool resA = small_case(r, c, x);
        //bool resB = general(r, c, x);
        //if (resA != resB) printf("%d %d %d\n", r, c, x);
        //if (check(r, c, x))
        //printf("%d %d %d ", r, c, x);
        if (general(r, c, x))
            printf("Case #%d: GABRIEL\n", test);
        else
            printf("Case #%d: RICHARD\n", test);
    }
    return 0;
}