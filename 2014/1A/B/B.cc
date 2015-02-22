#include <iostream>
#include <algorithm>
#include <vector>
#include <cstring>
#include <utility>

using namespace std;

const int maxN = 1000;
int N;

vector<int> neighbor[maxN];

/*
// method A: O(N^2)
int dfs(int x, int parent) {
	int largestA, largestB;
	largestA = largestB = -1;
	for (int i = 0; i < neighbor[x].size(); ++ i) {
		int y = neighbor[x][i];
		if (y == parent) continue;
		int k = dfs(y, x);
		if (k > largestA) {
			largestB = largestA;
			largestA = k;
		}
		else if (k > largestB)
			largestB = k;
	}
	if (largestA != -1 && largestB != -1)
		return 1 + largestA + largestB;
	return 1;
}
*/

// method B: O(N)
struct top3 {
	pair<int, int> A, B, C;
};

struct top3 Top[maxN];

void updateTop(struct top3 &parent, pair<int, int> key) {
	if (key.first > parent.A.first) {
		parent.C = parent.B; parent.B = parent.A; parent.A = key;
		return;
	}
	if (key.first > parent.B.first) {
		parent.C = parent.B; parent.B = key;
		return;
	}
	if (key.first > parent.C.first)
		parent.C = key;
}

pair<int, int> compare(int child, int parent, struct top3 &X) {
	if (X.A.second == child) {
		if (X.B.first == -1 || X.C.first == -1) return make_pair(1, parent);
		return make_pair(X.B.first + X.C.first + 1, parent);
	}
	if (X.B.second == child) {
		if (X.A.first == -1 || X.C.first == -1) return make_pair(1, parent);
		return make_pair(X.A.first + X.C.first + 1, parent);
	}
	if (X.C.second == child) {
		if (X.A.first == -1 || X.B.first == -1) return make_pair(1, parent);
		return make_pair(X.A.first + X.B.first + 1, parent);
	}
	if (X.B.first == -1) return make_pair(1, parent);
	return make_pair(X.A.first + X.B.first + 1, parent);
}

int dfsA(int x, int parent) {
	for (int i = 0; i < neighbor[x].size(); ++ i) {
		int y = neighbor[x][i];
		if (y == parent) continue;
		updateTop(Top[x], make_pair(dfsA(y, x), y));
	}

	if (Top[x].A.first != -1 && Top[x].B.first != -1)
		return 1 + Top[x].A.first + Top[x].B.first;
	return 1;
}

void dfsB(int x, int parent) {
	for (int i = 0; i < neighbor[x].size(); ++ i) {
		int y = neighbor[x][i];
		if (y == parent) continue;
		updateTop(Top[y], compare(y, x, Top[x]));
		dfsB(y, x);
	}
}

int solve() {
	cin >> N;
	for (int i = 0; i < N; ++ i)
		neighbor[i].clear();
	for (int i = 0; i < N - 1; ++ i) {
		int x, y;
		cin >> x >> y;
		-- x; -- y;
		neighbor[x].push_back(y);
		neighbor[y].push_back(x);
	}
	for (int i = 0; i < N; ++ i)
		Top[i].A = Top[i].B = Top[i].C = make_pair(-1, -1);
	dfsA(0, -1);
	dfsB(0, -1);
	int ans = 0;
	for (int i = 0; i < N; ++ i) {
		//cout << Top[i].A.first << " " << Top[i].B.first << " " << Top[i].C.first << endl;
		int k = 1;
		if (Top[i].A.first != -1 && Top[i].B.first != -1)
			k += Top[i].A.first + Top[i].B.first;
		ans = max(ans, k);
	}
	return N - ans;
/*
// method A:
	int ans = 0;
	for (int root = 0; root < N; ++ root)
		ans = max(ans, dfs(root, -1));
	return N - ans;
*/
}


int main() {
	int test;
	cin >> test;
	for (int t = 1; t <= test; ++ t) {
		cout << "Case #" << t << ": ";
		int ans = solve();
		cout << ans << endl;
	}
	return 0;
}
