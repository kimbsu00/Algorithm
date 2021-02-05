/*
  url: https://www.acmicpc.net/problem/1991
*/

#include<iostream>
#include<vector>

using namespace std;

void preorder(int node);
void inorder(int node);
void postorder(int node);

vector<pair<int, int>> tree;

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int N;
	cin >> N;

	tree = vector<pair<int, int>>(N, pair<int, int>(make_pair(-1, -1)));

	for (int i = 0; i < N; i++) {
		char root, left, right;
		cin >> root >> left >> right;

		tree[root - 'A'].first = (left == '.' ? -1 : left - 'A');
		tree[root - 'A'].second = (right == '.' ? -1 : right - 'A');
	}

	preorder(0);
	cout << "\n";
	inorder(0);
	cout << "\n";
	postorder(0);

	return 0;
}

void preorder(int node) {
	cout << char(node + 'A');

	if (tree[node].first != -1)
		preorder(tree[node].first);

	if (tree[node].second != -1)
		preorder(tree[node].second);
}

void inorder(int node) {
	if (tree[node].first != -1)
		inorder(tree[node].first);

	cout << char(node + 'A');

	if (tree[node].second != -1)
		inorder(tree[node].second);
}

void postorder(int node) {
	if (tree[node].first != -1)
		postorder(tree[node].first);

	if (tree[node].second != -1)
		postorder(tree[node].second);

	cout << char(node + 'A');
}
