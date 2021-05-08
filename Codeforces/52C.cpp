/*
  url: https://codeforces.com/problemset/problem/52/C
*/

#include<iostream>
#include<vector>
#include<algorithm>

#define LL long long

using namespace std;

class Node {
public:
	// 현재 노드가 위치해 있는 배열상의 인덱스를 의미
	LL index;
	// 현재 노드를 루트로 하는 서브트리에 포함되는 인덱스 범위를 의미 [left, right]
	LL left, right;
	// 현재 노드를 루트로 하는 서브트리에 존재하는 노드들 중 최소 값
	LL minValue;
	// 변화량 -> 문제에서의 v 값에 해당함
	LL diff;
};

LL makeIndexTree(LL index, LL left, LL right);
LL doQuery(LL index, LL left, LL right);
LL doUpdate(LL index, LL left, LL right, LL value);

LL N, M;
vector<LL> input;
Node tree[1000000];

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> N;
	input = vector<LL>(N + 1);
	for (int i = 1; i < N + 1; i++) {
		cin >> input[i];
	}
	makeIndexTree(1, 1, N);

	cin >> M;
	LL lf, rg, v;
	for (int i = 0; i < M; i++) {
		cin >> lf >> rg;
		lf += 1;
		rg += 1;

		char c = getchar();
		if (c == '\n') {
			if (lf > rg) {
				LL leftRet = doQuery(1, lf, N);
				LL rightRet = doQuery(1, 1, rg);
				cout << min(leftRet, rightRet) << "\n";
			}
			else {
				LL ret = doQuery(1, lf, rg);
				cout << ret << "\n";
			}
		}
		else {
			cin >> v;
			if (lf > rg) {
				doUpdate(1, lf, N, v);
				doUpdate(1, 1, rg, v);
			}
			else {
				doUpdate(1, lf, rg, v);
			}
		}
	}

	return 0;
}

LL makeIndexTree(LL index, LL left, LL right) {
	// 현재 노드의 변수 초기화
	tree[index].index = index;
	tree[index].left = left;
	tree[index].right = right;
	tree[index].diff = 0;

	// left 와 right 가 같은 경우 -> 현재 노드가 leaf 인 경우가 된다.
	if (left == right) {
		tree[index].minValue = input[left];
		return tree[index].minValue;
	}

	LL mid = (left + right) / 2;
	LL leftRet = makeIndexTree(index * 2, left, mid);
	LL rightRet = makeIndexTree(index * 2 + 1, mid + 1, right);

	tree[index].minValue = min(leftRet, rightRet);
	return tree[index].minValue;
}

LL doQuery(LL index, LL left, LL right) {
	LL leftChild = tree[index].left;
	LL rightChild = tree[index].right;

	if (leftChild >= left && rightChild <= right) {
		return tree[index].minValue + tree[index].diff;
	}

	if (left > rightChild || right < leftChild) {
		return (long long)9876543210987;
	}

	LL leftRet = doQuery(index * 2, left, right);
	LL rightRet = doQuery(index * 2 + 1, left, right);
	return min(leftRet, rightRet) + tree[index].diff;
}

LL doUpdate(LL index, LL left, LL right, LL value) {
	LL leftChild = tree[index].left;
	LL rightChild = tree[index].right;

	if (leftChild >= left && rightChild <= right) {
		tree[index].diff += value;
		return 0;
	}

	if (left > rightChild || right < leftChild) {
		return 0;
	}

	doUpdate(index * 2, left, right, value);
	doUpdate(index * 2 + 1, left, right, value);

	LL leftMin = tree[index * 2].minValue + tree[index * 2].diff;
	LL rightMin = tree[index * 2 + 1].minValue + tree[index * 2 + 1].diff;
	tree[index].minValue = min(leftMin, rightMin);

	return 0;
}
