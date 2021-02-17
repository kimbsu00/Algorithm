/*
  url: https://www.acmicpc.net/problem/11400
*/

#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int dfs(int node, int parent);
bool compare(const pair<int, int>& a, const pair<int, int>& b);

vector<vector<int>> graph;
vector<int> discovered;
int dfs_count = 0;
vector<pair<int, int>> answer;

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int V, E;
	cin >> V >> E;

	graph = vector<vector<int>>(V, vector<int>());
	discovered = vector<int>(V, -1);

	for (int i = 0; i < E; i++) {
		int a, b;
		cin >> a >> b;
		graph[a - 1].push_back(b - 1);
		graph[b - 1].push_back(a - 1);
	}

	for (int i = 0; i < graph.size(); i++) {
		if (discovered[i] < 0)
			dfs(i, i);
	}

	sort(answer.begin(), answer.end(), compare);
	cout << answer.size() << "\n";
	for (pair<int, int> output : answer) {
		cout << output.first + 1 << " " << output.second + 1 << "\n";
	}

	return 0;
}

int dfs(int node, int parent) {
	discovered[node] = dfs_count++;
	int ret = discovered[node];

	for (int next : graph[node]) {
		if (next == parent)			continue;

		if (discovered[next] >= 0) {
			ret = min(ret, discovered[next]);
			continue;
		}

		int subtree = dfs(next, node);
		if (subtree > discovered[node]) {
			answer.push_back(make_pair(min(node, next), max(node, next)));
		}
		ret = min(ret, subtree);
	}

	return ret;
}

bool compare(const pair<int, int>& a, const pair<int, int>& b) {
	if (a.first == b.first)
		return a.second < b.second;

	return a.first < b.first;
}
