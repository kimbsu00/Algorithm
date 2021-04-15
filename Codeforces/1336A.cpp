/*
  url: https://codeforces.com/problemset/problem/1336/A
*/

#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int makeGraph(int node, int level);
bool compare(const int& a, const int& b);

int N, K;
vector<vector<int>> graph;
vector<bool> visited;
// root node의 level을 0으로 설정함
vector<int> level;
vector<int> descendant;

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> N >> K;
	graph = vector<vector<int>>(N, vector<int>());
	visited = vector<bool>(N, false);
	level = vector<int>(N, 0);
	descendant = vector<int>(N, 0);
	for (int i = 1; i < N; i++) {
		int u, v;
		cin >> u >> v;
		graph[u - 1].push_back(v - 1);
		graph[v - 1].push_back(u - 1);
	}

	descendant[0] = makeGraph(0, 0);
	vector<int> distance;
	for (int i = 0; i < N; i++) {
		distance.push_back(level[i] - descendant[i]);
	}
	sort(distance.begin(), distance.end(), compare);

	long long output = 0;
	for (int i = 0; i < K; i++) {
		output += distance[i];
	}
	cout << output << "\n";
		 
	return 0;
}

int makeGraph(int node, int m_level) {
	visited[node] = true;
	level[node] = m_level;

	int ret = 0;
	for (int next : graph[node]) {
		if (!visited[next]) {
			ret += 1;
			ret += makeGraph(next, m_level + 1);
		}
	}

	descendant[node] = ret;
	return ret;
}

bool compare(const int& a, const int& b) {
	return a > b;
}
