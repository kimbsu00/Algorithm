/*
  url: https://www.acmicpc.net/problem/1005
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

int solve(int node);

vector<int> delay;
vector<vector<int>> reverse_graph;
int cache[1001];

int main() {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int T;
	cin >> T;
	vector<int> answer(T);
	for (int t = 0; t < T; t++) {
		fill(&cache[0], &cache[1001], -1);

		int N, K;
		cin >> N >> K;
		delay = vector<int>(N);
		for (int i = 0; i < N; i++) {
			cin >> delay[i];
		}

		reverse_graph = vector<vector<int>>(N, vector<int>());
		for (int i = 0; i < K; i++) {
			int a, b;
			cin >> a >> b;
			reverse_graph[b - 1].push_back(a - 1);
		}

		int target;
		cin >> target;

		answer[t] = solve(target - 1);
	}

	for (int output : answer) {
		cout << output << "\n";
	}

	return 0;
}

int solve(int node) {
	if (reverse_graph[node].empty())			return delay[node];

	int& ret = cache[node];
	if (ret != -1)			return ret;

	for (int i = 0; i < reverse_graph[node].size(); i++) {
		int next = reverse_graph[node][i];
		ret = max(ret, solve(next));
	}

	ret += delay[node];
	return ret;
}
