/*
  url: https://www.acmicpc.net/problem/11266
*/

#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int findCutVertex(int node, bool isRoot);

vector<vector<int>> graph;
// node 를 인덱스로 하고, dfs(node) 가 종료된 상태면 양수, 아니면 -1 을 갖는다.
vector<int> discovered;
vector<bool> isCutVertex;
int dfs_count = 0;

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int V, E;
	cin >> V >> E;

	graph = vector<vector<int>>(V, vector<int>());
	discovered = vector<int>(V, -1);
	isCutVertex = vector<bool>(V, false);

	for (int i = 0; i < E; i++) {
		int a, b;
		cin >> a >> b;
		graph[a - 1].push_back(b - 1);
		graph[b - 1].push_back(a - 1);
	}

	for (int i = 0; i < V; i++) {
		if (discovered[i] < 0)
			findCutVertex(i, true);
	}

	int count = 0;
	vector<int> answer;
	for (int i = 0; i < V; i++) {
		if (isCutVertex[i]) {
			count += 1;
			answer.push_back(i);
		}
	}
	sort(answer.begin(), answer.end(), less<int>());

	cout << count << "\n";
	for (int output : answer)
		cout << output + 1 << " ";

	return 0;
}

int findCutVertex(int node, bool isRoot) {
	discovered[node] = dfs_count++;
	int ret = discovered[node];

	// root 가 cut vertex 인지 확인하기 위한 변수 
	// childrent >= 2 이어야만 root 가 cut vertex 가 될 수 있음
	int children = 0;
	for (int next : graph[node]) {
		// next 를 방문하지 않은 경우
		if (discovered[next] < 0) {
			children += 1;
			// next 를 루트로 하는 서브트리에서 갈 수 있는 가장 높은 node
			int subtree = findCutVertex(next, false);

			// 이 노드가 node 이하에 존재하면 node 는 cut vertex 가 된다.
			if (!isRoot && subtree >= discovered[node])			isCutVertex[node] = true;

			ret = min(ret, subtree);
		}
		else {
			ret = min(ret, discovered[next]);
		}
	}

	if (isRoot)			isCutVertex[node] = (children >= 2);
	return ret;
}
