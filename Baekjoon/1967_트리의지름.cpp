/*
    url: https://www.acmicpc.net/problem/1967
    
    "리프 - 루트 - 리프" 가 최장거리인 경우 1가지
    "리프 - 루트가 아닌 다른 노드 - 리프" 가 최장거리인 경우 1가지
    이렇게 총 2 가지의 경우를 고려해서 해결함.
    
    tree 변수에는 부모 노드에서 자식 노드로 가는 엣지만 추가했는데, 이는 재귀호출 과정에서 자식 노드에서 부모 노드로 다시 올라가는 일을 차단하기 위함.
    사실 자식 노드에서 부모 노드로 가는 엣지도 추가하고, vector<bool> visited 변수 하나 추가해서 이미 방문했는지 여부를 따로 저장해도 되지만,
    메모리 절약을 위해서 트리를 방향 그래프처럼 저장해서 해결함
*/

#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;
 
int solve(int node, int sum);

// tree[parent] = pair<child, weight>
vector<vector<pair<int, int>>> tree;
vector<int> diameter;

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int N;
	cin >> N;
	tree = vector<vector<pair<int, int>>>(N, vector<pair<int, int>>());

	N--;
	while (N--) {
		int parent, child, weight;
		cin >> parent >> child >> weight;

		tree[parent - 1].push_back(make_pair(child - 1, weight));
	}
	
	int max = solve(0, 0);
	for (int d : diameter) {
		d > max ? max = d : d;
	}

	cout << max << "\n";

	return 0;
}

int solve(int node, int sum) {
	if (tree[node].empty())		return sum;

	vector<int> weight;

	for (int i = 0; i < tree[node].size(); i++) {
		weight.push_back(solve(tree[node][i].first, sum + tree[node][i].second));
	}

	if (weight.size() > 1) {
		sort(weight.begin(), weight.end(), greater<int>());
		diameter.push_back(weight[0] + weight[1] - 2 * sum);
	}

	return weight[0];
}
