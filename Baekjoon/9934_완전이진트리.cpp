/*
  url: https://www.acmicpc.net/problem/9934
*/

#include<iostream>
#include<vector>

using namespace std;

void solve(int start, int end, int level);

vector<int> inorder;
// level 을 인덱스로 하는 노드들의 집합
vector<vector<int>> node;

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int K;
	cin >> K;
	node = vector<vector<int>>(K, vector<int>());
	
	int N = (1 << K) - 1;
	inorder = vector<int>(N);

	for (int i = 0; i < N; i++) {
		cin >> inorder[i];
	}

	solve(0, N, 0);

	for (vector<int> vec : node) {
		for (int output : vec) {
			cout << output << " ";
		}
		cout << "\n";
	}

	return 0;
}

void solve(int start, int end, int level) {
	if (start + 1 == end) {
		node[level].push_back(inorder[start]);
		return;
	}

	int mid = (end - start - 1) / 2;
	solve(start, start + mid, level + 1);
	solve(start + mid + 1, end, level + 1);

	node[level].push_back(inorder[start + mid]);
}
