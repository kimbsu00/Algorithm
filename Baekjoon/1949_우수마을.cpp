/*
  url: https://www.acmicpc.net/problem/1949
*/

#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

void makeGraph(int node);
int solve(int node, int excellent);

vector<int> population;
vector<vector<int>> tree;
vector<vector<int>> directedGraph;
vector<bool> visited;
int cache[10001][2];

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int N;
	cin >> N;

	population = vector<int>(N);
	tree = vector<vector<int>>(N, vector<int>());
	directedGraph = vector<vector<int>>(N, vector<int>());
	visited = vector<bool>(N, false);
	fill(&cache[0][0], &cache[10000][2], -1);

	for (int i = 0; i < N; i++) {
		cin >> population[i];
	}

	for (int i = 1; i < N; i++) {
		int a, b;
		cin >> a >> b;
		tree[a - 1].push_back(b - 1);
		tree[b - 1].push_back(a - 1);
	}

	makeGraph(0);

	int output = max(solve(0, false), solve(0, true));
	cout << output << "\n";

	return 0;
}

// 트리를 방향그래프 형태로 바꾼다.
void makeGraph(int node) {
	visited[node] = true;

	for (int next : tree[node]) {
		if (!visited[next]) {
			directedGraph[node].push_back(next);
			makeGraph(next);
		}
	}
}

/*
1. node 가 우수 마을인 경우
	1.1. next 는 우수 마을이 될 수  없다.
2. node 가 우수 마을이 아닌 경우 
	2.1. next 는 우수 마을이 될 수도 있다.
	2.2. next 는 우수 마을이 되지 않을 수도 있다.

여기서 2.2 의 경우가 계속 반복되면, 모든 마을이 우수 마을이 되지 않으므로
문제에서 제시한 조건에 부합하지 않는 경우도 발생하는 것이 아닌가 하는 의문이 든다.
하지만 이는 max() 함수를 이용하여 2.1 과 2.2 의 경우 중에서 더 값이 큰 쪽을 택하기 때문에,
2.2 의 경우만 반복되는 경우는 절대로 정답으로 리턴되지 않음을 알 수 있다.
*/
int solve(int node, int excellent) {
	int& ret = cache[node][excellent];
	if (ret != -1)			return ret;

	ret = 0;
	if (excellent) {
		ret += population[node];
		for (int next : directedGraph[node]) {
			ret += solve(next, false);
		}
	}
	else {
		for (int next : directedGraph[node]) {
			ret += max(solve(next, false), solve(next, true));
		}
	}
	return ret;
}
