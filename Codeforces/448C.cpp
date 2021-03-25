/*
  url: https://codeforces.com/problemset/problem/448/C
*/

#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int solve(int start, int end, int height);

vector<int> fence;

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int N;
	cin >> N;
	fence = vector<int>(N);
	for (int i = 0; i < N; i++) {
		cin >> fence[i];
	}
	
	cout << solve(0, fence.size() - 1, 0) << "\n";

	return 0;
}

int solve(int start, int end, int height) {
	if (start > end)			return 0;

	int minHeight = 1000000001;
	int index = start;
	for (int i = start; i <= end; i++) {
		if (minHeight > fence[i]) {
			minHeight = fence[i];
			index = i;
		}
	}

	return min(end - start + 1, (minHeight - height) + solve(start, index - 1, minHeight) + solve(index + 1, end, minHeight));
}
