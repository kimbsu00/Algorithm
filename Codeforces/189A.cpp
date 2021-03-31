/*
  url: https://codeforces.com/problemset/problem/189/A
*/

#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int solve(int length, int sum);

int n, a, b, c;
int cache[4001];

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	memset(cache, - 1, 4001 * sizeof(int));
	vector<int> abc(3);
	cin >> n >> abc[0] >> abc[1] >> abc[2];
	sort(abc.begin(), abc.end(), less<int>());
	a = abc[0];
	b = abc[1];
	c = abc[2];

	cout << solve(n, 0) << "\n";

	return 0;
}

int solve(int length, int sum) {
	// 기저 사례 처리
	if (length == 0)			return sum;

	if (length < a && length < b && length < c)			return 0;

	int& ret = cache[length];

	if (ret != -1)			return ret;
	ret = 0;

	if (length >= a) {
		ret = max(ret, solve(length - a, sum + 1));
	}
	if (length >= b) {
		ret = max(ret, solve(length - b, sum + 1));
	}
	if (length >= c) {
		ret = max(ret, solve(length - c, sum + 1));
	}

	return ret;
}
