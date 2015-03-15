#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

double C;
double F;
double X;

double gettime(int farms) {
    double rate = 2.0;
    double ret = 0.0;
    for (int i = 1; i <= farms; ++ i) {
        ret += C / rate;
        rate += F;
    }
    ret += X / rate;
    return ret;
}

int main() {
    int T;
    scanf("%d", &T);
    for (int test = 1; test <= T; ++ test) {
        printf("Case #%d: ", test);
        scanf("%lf %lf %lf", &C, &F, &X);
        double opt = gettime(0);
        int farms = 1;
        while (1) {
            double time = gettime(farms);
            if (time < opt)
                opt = time;
            else
                break;
            ++ farms;
        }
        printf("%.7lf\n", opt);
    }
    return 0;
}
