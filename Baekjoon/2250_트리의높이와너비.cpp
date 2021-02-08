/*
  url: https://www.acmicpc.net/problem/2250
*/

#include<iostream>
#include<vector>
#include<algorithm>

using namespace std;

int findRoot();
void calculateWidth(int node, int level);

int _max = -1, _level = 0;
int row;
vector<int> parent;
// 안댁수룰 parent 로 하고, 왼쪽 서브트리를 first, 오른쪽 서브트리를 second 로 함
vector<pair<int, int>> tree;
// 인덱스를 level 로 하고, 해당하는 level 에서 맨 오른쪽에 있는 노드를 first, 맨 왼쪽에 있는 노드를 second 로 함
vector<pair<int, int>> width;

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int N;
	cin >> N;

	row = 0;
	parent = vector<int>(N, -1);
	tree = vector<pair<int, int>>(N, make_pair(-1, -1));
	width = vector<pair<int, int>>(N, make_pair(-1, 987654321));

	for (int i = 0; i < N; i++) {
		int _parent, left, right;
		cin >> _parent >> left >> right;

		if (left != -1) {
			tree[_parent - 1].first = left - 1;
			parent[left - 1] = _parent - 1;
		}
		if (right != -1) {
			tree[_parent - 1].second = right - 1;
			parent[right - 1] = _parent - 1;
		}
	}

	int root = findRoot();
	calculateWidth(root, 0);

	for (int i = 0; i < width.size(); i++) {
		if (width[i].first == -1)			break;

		int distance = width[i].first - width[i].second + 1;
		if (distance > _max) {
			_max = distance;
			_level = i;
		}
	}

	cout << _level + 1 << " " << _max << "\n";

	return 0;
}

int findRoot() {
	int ret = 0;
	while (parent[ret] != -1)		ret = parent[ret];
	return ret;
}

// Inorder Traversal
void calculateWidth(int node, int level) {
	int left = tree[node].first;
	if (left != -1)		calculateWidth(left, level + 1);

	width[level].first = max(width[level].first, row);
	width[level].second = min(width[level].second, row);
	row += 1;

	int right = tree[node].second;
	if (right != -1)		calculateWidth(right, level + 1);
}
