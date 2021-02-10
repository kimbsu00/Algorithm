/*
  url: https://www.acmicpc.net/problem/4256
*/

#include<iostream>
#include<vector>

using namespace std;

void postorder(int p_start, int p_end, int i_start, int i_end);

vector<int> preorder;
vector<int> inorder;

int main(void) {
	int T;
	cin >> T;

	for (int i = 0; i < T; i++) {
		int N;
		cin >> N;

		preorder = vector<int>(N);
		inorder = vector<int>(N);

		for (int j = 0; j < N; j++)
			cin >> preorder[j];
		for (int j = 0; j < N; j++)
			cin >> inorder[j];

		postorder(0, N, 0, N);
		cout << "\n";
	}

	return 0;
}

void postorder(int p_start, int p_end, int i_start, int i_end) {
	if (p_start + 1 == p_end) {
		cout << preorder[p_start] << " ";
		return;
	}
	
	for (int i = i_start; i < i_end; i++) {
		if (preorder[p_start] == inorder[i]) {
			postorder(p_start + 1, p_start + 1 + (i - i_start), i_start, i);
			postorder(p_start + 1 + (i - i_start), p_end, i + 1, i_end);
			cout << preorder[p_start] << " ";
			return;
		}
	}
}
