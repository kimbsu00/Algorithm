/*
  url: https://codeforces.com/problemset/problem/217/A
*/

#include<iostream>
#include<vector>

using namespace std;

void dfs(int index);

int N;
vector<pair<int, int>> coord;
vector<vector<int>> linked;
vector<int> visited;

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> N;
	coord.resize(N, { -1,-1 });
	linked.resize(N, vector<int>(0));
	visited.resize(N, false);

	for (int i = 0; i < N; i++) {
		cin >> coord[i].first >> coord[i].second;
	}

	for (int i = 0; i < N; i++) {
		for (int j = i + 1; j < N; j++) {
			if (coord[i].first == coord[j].first || coord[i].second == coord[j].second) {
				linked[i].push_back(j);
				linked[j].push_back(i);
			}
		}
	}

	int output = 0;
	for (int i = 0; i < N; i++) {
		if (!visited[i]) {
			dfs(i);
			output += 1;
		}
	}

	cout << output - 1 << "\n";

	return 0;
}

void dfs(int index) {
	visited[index] = true;

	for (int i = 0; i < linked[index].size(); i++) {
		int next = linked[index][i];
		if (!visited[next]) {
			dfs(next);
		}
	}
}
