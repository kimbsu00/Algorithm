/*
  url: https://codeforces.com/problemset/problem/558/E
*/

#include<iostream>
#include<string>

using namespace std;

class Node {
public:
	// 현재 노드를 루트로 하는 서브트리에 포함되는 인덱스 범위를 의미 [left, right]
	int left, right;
	int count;
	int lazy;
};

void setCount(int alphabet, int index);
void makeIndexTree(int alphabet, int index, int left, int right);
void pushDown(int alphabet, int index);
int query(int alphabet, int index, int left, int right);
void update(int alphabet, int index, int left, int right, int value);

int N, Q;
char input[100005];
Node tree[26][400000];

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	scanf("%d %d", &N, &Q);
	scanf("%s", &input);

	for (int i = 0; i < 26; i++) {
		makeIndexTree(i, 1, 1, N);
	}

	for (int index = 0; index < Q; index++) {
		int i, j, k;
		cin >> i >> j >> k;

		int num[26];
		for (int t = 0; t < 26; t++) {
			num[t] = query(t, 1, i, j);
			update(t, 1, i, j, 0);
		}
		int left = i;
		// sort non-decreasing order
		if (k) {
			for (int t = 0; t < 26; t++) {
				if (num[t] > 0)			update(t, 1, left, left + num[t] - 1, 1);
				left += num[t];
			}
		}
		// sort non-increasing order
		else {
			for (int t = 25; t >= 0; t--) {
				if (num[t] > 0)			update(t, 1, left, left + num[t] - 1, 1);
				left += num[t];
			}
		}
	}

	string output = "";
	for (int i = 1; i <= N; i++) {
		for (int j = 0; j < 26; j++) {
			if (query(j, 1, i, i) == 1) {
				output += 'a' + j;
			}
		}
	}
	cout << output << "\n";

	return 0;
}

void setCount(int alphabet, int index) {
	tree[alphabet][index].count = tree[alphabet][index * 2].count + tree[alphabet][index * 2 + 1].count;
}

void makeIndexTree(int alphabet, int index, int left, int right) {
	tree[alphabet][index].left = left;
	tree[alphabet][index].right = right;
	tree[alphabet][index].lazy = -1;

	if (left == right) {
		if (input[left - 1] == 'a' + alphabet) {
			tree[alphabet][index].count = 1;
		}
		else {
			tree[alphabet][index].count = 0;
		}
		return;
	}

	int mid = (left + right) / 2;
	makeIndexTree(alphabet, index * 2, left, mid);
	makeIndexTree(alphabet, index * 2 + 1, mid + 1, right);
	setCount(alphabet, index);
	return;
}

void pushDown(int alphabet, int index) {
	if (tree[alphabet][index].lazy == 1) {
		tree[alphabet][index * 2].lazy = 1;
		tree[alphabet][index * 2].count = tree[alphabet][index * 2].right - tree[alphabet][index * 2].left + 1;
		tree[alphabet][index * 2 + 1].lazy = 1;
		tree[alphabet][index * 2 + 1].count = tree[alphabet][index * 2 + 1].right - tree[alphabet][index * 2 + 1].left + 1;
	}
	else if (tree[alphabet][index].lazy == 0) {
		tree[alphabet][index * 2].lazy = 0;
		tree[alphabet][index * 2].count = 0;
		tree[alphabet][index * 2 + 1].lazy = 0;
		tree[alphabet][index * 2 + 1].count = 0;
	}
	tree[alphabet][index].lazy = -1;
}

// alphabet 트리의 [left, right] 범위에 존재하는 count 값을 리턴한다.
int query(int alphabet, int index, int left, int right) {
	int leftChild = tree[alphabet][index].left;
	int rightChild = tree[alphabet][index].right;

	if (left <= leftChild && rightChild <= right)			return tree[alphabet][index].count;

	if (leftChild > right || left > rightChild)			return 0;

	pushDown(alphabet, index);

	int leftRet = query(alphabet, index * 2, left, right);
	int rightRet = query(alphabet, index * 2 + 1, left, right);
	return leftRet + rightRet;
}

// alphabet 트리의 [left, right] 범위 값을 value로 설정한다.
void update(int alphabet, int index, int left, int right, int value) {
	int leftChild = tree[alphabet][index].left;
	int rightChild = tree[alphabet][index].right;

	if (left <= leftChild && rightChild <= right) {
		if (value) {
			tree[alphabet][index].lazy = 1;
			tree[alphabet][index].count = tree[alphabet][index].right - tree[alphabet][index].left + 1;
		}
		else {
			tree[alphabet][index].lazy = 0;
			tree[alphabet][index].count = 0;
		}
		return;
	}

	if (leftChild > right || left > rightChild)			return;

	pushDown(alphabet, index);
	update(alphabet, index * 2, left, right, value);
	update(alphabet, index * 2 + 1, left, right, value);
	setCount(alphabet, index);
	return;
}
