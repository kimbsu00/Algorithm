/*
  url: https://www.acmicpc.net/problem/1693
   
  밑이 2인 log 에 대하여
  log 100000 = 16.60964... 이기 때문에, 
  100000개의 노드를 서로 다른 색으로 색칠하기 위해 필요한 색깔은 17개면 충분함을 알 수 있다.
  
  처음에 100000(십만)을 10000(만)으로 잘못 봐서 틀렸던 문제.
*/

#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

void makeGraph(int node);
int solve(int node, int cost);

int N;
vector<vector<int>> tree;
vector<vector<int>> directedGraph;
vector<bool> visited;
int cache[100000][17];

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> N;

	tree = vector<vector<int>>(N, vector<int>());
	directedGraph = vector<vector<int>>(N, vector<int>());
	visited = vector<bool>(N, false);
	fill(&cache[0][0], &cache[99999][17], -1);
	for (int i = 1; i < N; i++) {
		int a, b;
		cin >> a >> b;
		tree[a - 1].push_back(b - 1);
		tree[b - 1].push_back(a - 1);
	}

	makeGraph(0);

	int output = 987654321;
	for (int i = 1; i < 17; i++) {
		output = min(output, solve(0, i));
	}
	cout << output << "\n";

	return 0;
}

void makeGraph(int node) {
	visited[node] = true;

	for (int next : tree[node]) {
		if (!visited[next]) {
			directedGraph[node].push_back(next);
			makeGraph(next);
		}
	}
}

int solve(int node, int cost) {
	int& ret = cache[node][cost];
	if (ret != -1)			return ret;

	int childrenCost = 0;
	for (int child : directedGraph[node]) {
		int childCost = 987654321;
		for (int i = 1; i < 17; i++) {
			if (i == cost)			continue;

			childCost = min(childCost, solve(child, i));
		}
		childrenCost += childCost;
	}

	return ret = childrenCost + cost;
}
