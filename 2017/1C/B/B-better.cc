#include <iostream>
#include <cstring>
#include <vector>
#include <algorithm>
#include <map>
#include <cstdio>
#include <set>
#include <cmath>

using namespace std;

const int INF = 1000000000;

struct TI {
    int start, end, owner;

    bool operator < (const TI &other) const {
        return start < other.start;
    }
};

vector<TI> intervals;

int solve() {
    sort(intervals.begin(), intervals.end());
    int ans = 0;
    int own_time[2]{};
    for (const TI &interval : intervals) {
        own_time[interval.owner] += interval.end - interval.start;
    }

    vector<int> gaps[2];

    for (int i = 1; i < intervals.size(); ++ i) {
        if (intervals[i].owner == intervals[i - 1].owner) {
            gaps[intervals[i].owner].push_back(intervals[i].start - intervals[i - 1].end);
        }
        else
            ++ ans;
    }
    if (intervals.front().owner == intervals.back().owner) {
        gaps[intervals.front().owner].push_back(intervals.front().start + 1440 - intervals.back().end);
    }
    else
        ++ ans;

    for (int i = 0; i < 2; ++ i) {
        sort(gaps[i].begin(), gaps[i].end());

        int k;
        for (k = 0; k < gaps[i].size() && own_time[i] + gaps[i][k] <= 720; ++ k)
            own_time[i] += gaps[i][k];

        ans += (gaps[i].size() - k) * 2;
    }

    return ans;
}


int main() {
    int T;
    scanf("%d", &T);
    for (int test = 1; test <= T; ++ test) {
        intervals.clear();
        int N[2];
        cin >> N[0] >> N[1];
        for (int i = 0; i < 2; ++ i) {
            while (N[i] --) {
                TI temp;
                cin >> temp.start >> temp.end;
                temp.owner = i;
                intervals.push_back(temp);
            }
        }
        printf("Case #%d: %d\n", test, solve());
    }
    return 0;
}
