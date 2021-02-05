/*
  url: https://www.acmicpc.net/problem/1167
*/

#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int solve(int node, int sum);

vector<vector<pair<int,int>>> tree;
vector<bool> visited;
vector<int> diameter;

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int V;
	cin >> V;

	tree = vector<vector<pair<int, int>>>(V, vector<pair<int, int>>());
	visited = vector<bool>(V, false);

	for (int i = 0; i < V; i++) {
		int node1;
		cin >> node1;
		while (true) {
			int node2;
			cin >> node2;
			if (node2 == -1)		break;
			int weight;
			cin >> weight;
			tree[node1 - 1].push_back(make_pair(node2 - 1, weight));
		}
	}

	int max = solve(0, 0);
	for (int d : diameter) {
		d > max ? max = d : d;
	}

	cout << max << "\n";

	return 0;
}

int solve(int node, int sum) {
	visited[node] = true;
	vector<int> weight;

	for (int i = 0; i < tree[node].size(); i++) {
		if (!visited[tree[node][i].first])
			weight.push_back(solve(tree[node][i].first, sum + tree[node][i].second));
	}

	if (weight.size() > 1) {
		sort(weight.begin(), weight.end(), greater<int>());
		diameter.push_back(weight[0] + weight[1] - 2 * sum);
	}

	if (weight.empty())			return sum;

	return weight[0];
}
