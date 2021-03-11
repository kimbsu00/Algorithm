/*
  url: https://codeforces.com/problemset/problem/1003/C
*/

#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

double getAverage(int start, int end);
int rangeSum(int start, int end);

vector<int> prefixSum;

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int N, K;
	cin >> N >> K;
	prefixSum = vector<int>(N, 0);

	cin >> prefixSum[0];
	for (int i = 1; i < N; i++) {
		int num;
		cin >> num;
		prefixSum[i] += prefixSum[i - 1] + num;
	}

	double maxAverage = -1;
	for (int i = 0; i < N - K + 1; i++) {
		for (int j = i + K - 1; j < N; j++) {
			maxAverage = max(maxAverage, getAverage(i, j));
		}
	}

	printf("%.8lf\n", maxAverage);

	return 0;
}

double getAverage(int start, int end) {
	return (double)rangeSum(start, end) / (double)(end - start + 1);
}

int rangeSum(int start, int end) {
	if (start == 0)			return prefixSum[end];

	return prefixSum[end] - prefixSum[start - 1];
}
