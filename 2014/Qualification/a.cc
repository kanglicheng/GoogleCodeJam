#include <cstdio>
#include <cstring>
#include <algorithm>

using namespace std;

int A[4];
int B[4];

int main() {
    int T;

    scanf("%d", &T); 

    int test = 0;
    while (T --) {
        ++ test;
        printf("Case #%d: ", test);

        int row;
        scanf("%d", &row);
        for (int i = 0; i < 4; ++ i)
            for (int j = 0; j < 4; ++ j) {
                int k;
                scanf("%d", &k);
                if (i + 1 == row)
                    A[j] = k;
            }
        scanf("%d", &row);
        for (int i = 0; i < 4; ++ i) {
            for (int j = 0; j < 4; ++ j)
                scanf("%d", &B[j]);
            if (i + 1 == row) {
                int flag = -1;
                int ans;
                for (int b = 0; b < 4; ++ b)
                    for (int a = 0; a < 4; ++ a)
                        if (A[a] == B[b]) {
                            if (flag == -1) {
                                flag = 0;
                                ans = A[a];
                            }
                            else if (flag == 0)
                                flag = 1;
                        }
                if (flag == -1)
                    printf("Volunteer cheated!\n");
                else if (flag == 0)
                    printf("%d\n", ans);
                else
                    printf("Bad magician!\n");

            }
        }
    }
    return 0;
}
