/*
  url: https://www.acmicpc.net/problem/3584
  
  처음에 문제를 봤을 때 나는 당연히 루트 노드가 1 인 줄 알고 문제를 접근했는데,
  한참이 지나고 나서야 루트 노드를 특정해 주지 않았음을 깨닫게 되었다.
  이 때문에 맨 처음에 생각했던 방법은 다음과 같다.
  
    공통 조상을 찾고자 하는 노드 2개를 각각 node1, node2 라고 하면,
    1. 루트 노드를 찾고,
    2. 루트 노드에서 부터 node1 과 node2 를 찾고, 찾은 경로를 stack 에 기록한다.
    3. stack 의 top 에는 루트 노드가 있을 것이고 stack 의 bottom 에는 node1 or node2 가 있을 것이므로, 
       stack 에서 값을 하나씩 꺼내면서 stack 의 top 이 처음으로 달라지는 경우에 공통 조상을 알 수 있다.
  
  위의 방법은 올바른 정답을 찾아내기는 하나, 시간제한 1000ms 에 걸려서 오답 처리가 된다.
  
  따라서 문제의 input 이 "부모 - 자식" 의 순서로 트리의 간선 정보를 제공하므로,
  각 노드마다 부모 노드를 저장해서 node1 과 node2 에서 시작해서 루트 쪽으로 올라가는 방법을 이용했다.
  node1 과 node2 의 depth 가 서로 같으면, 서로 한 칸씩 위로 올라가면 되고,
  node1 과 node2 의 depth 가 서로 다르면, 두 노드의 depth 를 먼저 맞춰주고 한 칸씩 위로 올라가면 된다.
*/ 

#include<iostream>
#include<vector>

using namespace std;

int solve(int node1, int node2);
int getDepth(const int& node);

vector<int> parent;

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int T;
	cin >> T;
	vector<int> answer(T);

	for (int i = 0; i < T; i++) {
		int N;
		cin >> N;

		parent = vector<int>(N, -1);

		for (int j = 1; j < N; j++) {
			int a, b;
			cin >> a >> b;

			parent[b - 1] = a - 1;
		}

		int node1, node2;
		cin >> node1 >> node2;
		answer[i] = solve(node1 - 1, node2 - 1);
	}

	for (int output : answer) {
		cout << output + 1 << "\n";
	}

	return 0;
}

int solve(int node1, int node2) {
	int depth1 = getDepth(node1);
	int depth2 = getDepth(node2);

	// node1 과 node2 의 depth 가 서로 다르면, 두 노드의 depth 를 먼저 맞춰주고
	if (depth1 < depth2) {
		while (depth1 != depth2) {
			node2 = parent[node2];
			depth2 -= 1;
		}
	}
	else if (depth1 > depth2) {
		while (depth1 != depth2) {
			node1 = parent[node1];
			depth1 -= 1;
		}
	}

	// 서로 한 칸씩 위로 올라가면 된다.
	while (node1 != node2) {
		node1 = parent[node1];
		node2 = parent[node2];
	}

	return node1;
}

int getDepth(const int& node) {
	int ret = 0;

	int next = node;
	while (next != -1) {
		next = parent[next];
		ret += 1;
	}

	return ret;
}
