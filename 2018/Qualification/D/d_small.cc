#include <iostream>
#include <cstdio>
#include <algorithm>
#include <vector>
#include <cmath>

using namespace std;

double A;

const double eps = 0.000001;
const double sqrt2 = sqrt(2);
const double sqrt3 = sqrt(3);

void solve() {
    if (A <= sqrt2 + eps) {
        double k = sqrt(2 - A * A);
        double s = (A + k) / 2;
        double c = (A - k) / 2;

        double Ax = 0.5 * -c;
        double Ay = 0.5 * -s;
        double Az = 0;

        double Bx = 0.5 * s;
        double By = 0.5 * -c;
        double Bz = 0;

        double Cx = 0;
        double Cy = 0;
        double Cz = 0.5;

        printf("%.8lf %.8lf %.8lf\n", Ax, Ay, Az);
        printf("%.8lf %.8lf %.8lf\n", Bx, By, Bz);
        printf("%.8lf %.8lf %.8lf\n", Cx, Cy, Cz);
    } else {
        cout << 0.5 << " " << 0 << " " << 0 << endl;
        cout << 0 << " " << 0.5 << " " << 0 << endl;
        cout << 0 << " " << 0 << " " << 0.5 << endl;
    }
}

int main() {
    int T;
    cin >> T;
    for (int test = 1; test <= T; ++ test) {
        cin >> A;
        cout << "Case #" << test << ":" << endl;
        solve();
    }
    return 0;
}
