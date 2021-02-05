/*
  url: https://www.acmicpc.net/problem/1068
  
  노드(A)를 제거했을 때, 제거한 노드(A)의 부모(B)가 자식으로 A 노드만을 갖고 있었던 경우에는
  B 노드가 leaf 노드가 되는 경우를 처음에 생각하지 못했던 문제.
*/

#include<iostream>
#include<vector>

using namespace std;

int calculateLeaf(int node);

vector<vector<int>> tree;
vector<int> parent;
vector<int> underLeaf;

int main(void) {
	int N;
	cin >> N;

	tree = vector<vector<int>>(N, vector<int>());
	parent = vector<int>(N, -1);
	underLeaf = vector<int>(N, 0);

	int root = -1;
	for (int i = 0; i < N; i++) {
		int _parent;
		cin >> _parent;
		parent[i] = _parent;
		if (_parent == -1) {
			root = i;
			continue;
		}
		tree[_parent].push_back(i);
	}

	int deleteNode;
	cin >> deleteNode;

	tree[deleteNode].clear();

	calculateLeaf(root);

	int diff;
	// deleteNode 의 부모가 자식으로 deleteNode 만을 갖고 있는 경우에는
	// deleteNode 를 제거하면 deleteNode 의 부모가 left 가 되므로,
	// 이 경우에만 +1 을 해서 출력한다.
	underLeaf[parent[deleteNode]] == 1 ? 
		diff = underLeaf[root] - underLeaf[deleteNode] + 1 : diff = underLeaf[root] - underLeaf[deleteNode];
	cout << diff << "\n";

	return 0;
}

int calculateLeaf(int node) {
	if (tree[node].empty()) {
		underLeaf[node] = 1;
		return 1;
	}

	int& ret = underLeaf[node];
	for (int child : tree[node]) {
		ret += calculateLeaf(child);
	}
	return ret;
}
