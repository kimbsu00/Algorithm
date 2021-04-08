/*
  url: https://codeforces.com/problemset/problem/602/B
*/

#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int solve(int index, int left, int right);

int N;
vector<int> input;
// cache[index][0]  -> input[index] 값이 최대값일 때, 가장 긴 길이
// cache[index][1]  -> input[index] 값이 최소값일 때, 가장 긴 길이
int cache[100000][2];

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	memset(cache, -1, sizeof(cache));
	cin >> N;
	input = vector<int>(N);
	for (int i = 0; i < N; i++) {
		cin >> input[i];
	}

	int answer = -1;
	for (int i = 0; i < N; i++) {
		answer = max(answer, max(solve(i, input[i], input[i] + 1), solve(i, input[i] - 1, input[i])));
	}
	cout << answer << "\n";

	return 0;
}

int solve(int index, int left, int right) {
	if (index == N)			return 0;

	if (abs(input[index] - left) > 1 || abs(input[index] - right) > 1)			return 0;

	bool check = input[index] == left;
	int& ret = cache[index][check];
	if (ret != -1)			return ret;

	if (check) {
		ret = max(ret, 1 + solve(index + 1, left, right));
	}
	else {
		ret = max(ret, 1 + solve(index + 1, left, right));
	}

	return ret;
}
