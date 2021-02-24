/*
  url: https://www.acmicpc.net/problem/4803
  
  input 으로 주어지는 간선은 양방향이기 때문에,
  (간선의 개수 / 2) == (노드의 개수 - 1) 를 만족하는 집합이 존재한다면, 
  이 집합은 트리이다.
*/

#include<iostream>
#include<vector>
#include<set>

using namespace std;

int getVertexNum(int node);
int getEdgeNum(int node);

vector<vector<int>> graph;
vector<bool> visited;
vector<bool> passed;

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	vector<int> answer;
	int N, M;
	while (true) {
		cin >> N >> M;
		if (N == 0 && M == 0)			break;

		graph = vector<vector<int>>(N, vector<int>());
		visited = vector<bool>(N, false);
		passed = vector<bool>(N, false);

		for (int i = 0; i < M; i++) {
			int a, b;
			cin >> a >> b;
			graph[a - 1].push_back(b - 1);
			graph[b - 1].push_back(a - 1);
		}

		int count = 0;
		for (int i = 0; i < N; i++) {
			if (!visited[i]) {
				int vertex = getVertexNum(i);
				int edge = getEdgeNum(i);
				// 트리의 조건
				if (vertex - 1 == edge / 2)			count += 1;
			}
		}

		answer.push_back(count);
	}

	for (int i = 0; i < answer.size(); i++) {
		cout << "Case " << i + 1 << ": ";
		if (answer[i] == 0)
			cout << "No trees.\n";
		else if (answer[i] == 1)
			cout << "There is one tree.\n";
		else
			cout << "A forest of " << answer[i] << " trees.\n";
	}

	return 0;
}

int getVertexNum(int node) {
	int ret = 1;
	visited[node] = true;

	for (int next : graph[node]) {
		if (!visited[next]) {
			ret += getVertexNum(next);
		}
	}

	return ret;
}

int getEdgeNum(int node) {
	int ret = graph[node].size();
	passed[node] = true;

	for (int next : graph[node]) {
		if (!passed[next]) {
			ret += getEdgeNum(next);
		}
	}

	return ret;
}
