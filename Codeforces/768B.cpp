/*
  url: https://codeforces.com/problemset/problem/768/B
*/

#include<iostream>

using namespace std;

int solve(long long start, long long end, long long L, long long R, long long N);

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	long long N, L, R;
	cin >> N >> L >> R;

	long long length = 1;
	long long temp = N;
	while (temp > 1) {
		temp /= 2;
		length = length * 2 + 1;
	}

	cout << solve(1, length, L, R, N) << "\n";

	return 0;
}

int solve(long long start, long long end, long long L, long long R, long long N) {
	if (L <= start && end <= R)			return N;

	long long mid = (start + end) >> 1;
	long long ret = 0;
	
	if (L < mid) {
		ret += solve(start, mid - 1, L, R, N / 2);
	}
	if (mid < R) {
		ret += solve(mid + 1, end, L, R, N / 2);
	}
	if (L <= mid && mid <= R) {
		ret += solve(mid, mid, L, R, N % 2);
	}

	return ret;
}
