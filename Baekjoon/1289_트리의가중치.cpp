/*
  url: https://www.acmicpc.net/problem/1289
*/

#include<iostream>
#include<vector>

using namespace std;

void makeGraph(int node);
long long solve(int node);

const int MOD = 1000000007;
int N;
vector<vector<pair<int, int>>> tree;
vector <vector<pair<int, int>>> directedGraph;
vector<bool> visited;
long long output = 0;

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> N;
	tree = vector<vector<pair<int, int>>>(N, vector<pair<int, int>>());
	directedGraph = vector<vector<pair<int, int>>>(N, vector<pair<int, int>>());
	visited = vector<bool>(N, false);
	for (int i = 1; i < N; i++) {
		int A, B, W;
		cin >> A >> B >> W;
		tree[A - 1].push_back(make_pair(B - 1, W));
		tree[B - 1].push_back(make_pair(A - 1, W));
	}

	makeGraph(0);

	solve(0);

	cout << output << "\n";

	return 0;
}

void makeGraph(int node) {
	visited[node] = true;

	for (pair<int, int> p : tree[node]) {
		if (!visited[p.first]) {
			directedGraph[node].push_back(p);
			makeGraph(p.first);
		}
	}
}

long long solve(int node) {
	long long ret = 1;
	for (pair<int, int> p : directedGraph[node]) {
		int child = p.first;
		int weight = p.second;

		long long temp = (solve(child) * weight) % MOD;
		output += (temp * ret) % MOD;
		output %= MOD;
		ret = (ret + temp) % MOD;
	}

	return ret;
}
