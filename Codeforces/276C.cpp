/*
  url: https://codeforces.com/problemset/problem/276/C
*/

#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

bool compare(const int& a, const int& b);

int N, Q;
vector<int> input;
vector<int> queryCount;

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> N >> Q;
	input = vector<int>(N);
	queryCount = vector<int>(N + 1, 0);
	for (int i = 0; i < N; i++) {
		cin >> input[i];
	}
	sort(input.begin(), input.end(), compare);

	for (int i = 0; i < Q; i++) {
		int l, r;
		cin >> l >> r;
		queryCount[l - 1] += 1;
		queryCount[r] -= 1;
	}

	for (int i = 1; i < N; i++) {
		queryCount[i] += queryCount[i - 1];
	}
	sort(queryCount.begin(), queryCount.end(), compare);

	long long output = 0;
	for (int i = 0; i < N; i++) {
		output += (long long)queryCount[i] * (long long)input[i];
	}
	cout << output << "\n";

	return 0;
}

bool compare(const int& a, const int& b) {
	return a > b;
}
