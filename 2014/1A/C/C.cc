#include <iostream>
#include <string>
#include <algorithm>
#include <vector>

using namespace std;

const int N = 1000;

const int Good = 500;
const int Bad = 472;
const int Threshold = (Good + Bad) >> 1;

vector<int> A;

int scoreF() {
	int ret = 0;
	for (int i = 0; i < N; ++ i)
		if (A[i] <= i - 1)
			++ ret;
	return ret;
}

int main() {
	int T = 120;
	for (int test = 1; test <= T; ++ test) {
		cout << "Case #" << test << ": ";
		int n;
		cin >> n;
		A.clear();
		for (int i = 0; i < N; ++ i) {
			cin >> n;
			A.push_back(n);
		}
		int f = scoreF();
		if (f < Threshold)
			cout << "BAD" << endl;
		else
			cout << "GOOD" << endl; 
	}
	return 0;
}
