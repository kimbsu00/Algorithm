/*
  url: https://www.acmicpc.net/problem/2839
*/

#include<iostream>
#include<algorithm>

using namespace std;

int solve(int N, int count);

const int MAX = 987654321;
int cache[5001];

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	fill(&cache[0], &cache[5001], -1);

	int N;
	cin >> N;

	int answer = solve(N, 0);
	answer == MAX ? answer = -1 : answer;
	cout << answer << "\n";

	return 0;
}

int solve(int N, int count) {
	if (N == 0)			return count;

	if (N < 0)			return MAX;

	int& ret = cache[N];
	if (ret != -1)			return ret;

	ret = min(solve(N - 3, count + 1), solve(N - 5, count + 1));
	return ret;
}
