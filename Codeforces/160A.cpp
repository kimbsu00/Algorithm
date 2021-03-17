/*
  url: https://codeforces.com/problemset/problem/160/A
*/

#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

bool _greater(const int& a, const int& b);

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int N;
	cin >> N;
	vector<int> input(N);
	int sum = 0;
	for (int i = 0; i < N; i++) {
		cin >> input[i];
		sum += input[i];
	}
	sort(input.begin(), input.end(), _greater);

	int mine = 0;
	int answer = -1;
	for (int i = 0; i < N; i++) {
		mine += input[i];
		sum -= input[i];
		if (mine > sum) {
			answer = i + 1;
			break;
		}
	}

	cout << answer << "\n";

	return 0;
}

bool _greater(const int& a, const int& b) {
	return a >= b;
}
