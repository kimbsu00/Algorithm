/*
  url: https://www.acmicpc.net/problem/2263
*/

#include<iostream>
#include<vector>

using namespace std;

void preorder(int i_start, int i_end, int p_start, int p_end);

vector<int> inorder;
vector<int> postorder;

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int N;
	cin >> N;

	inorder = vector<int>(N);
	postorder = vector<int>(N);

	for (int i = 0; i < N; i++) {
		cin >> inorder[i];
	}

	for (int i = 0; i < N; i++) {
		cin >> postorder[i];
	}

	preorder(0, inorder.size(), 0, postorder.size());

	return 0;
}

/*
inorder index -> [i_start, i_end)
postorder index -> [p_start, p_end)
*/
void preorder(int i_start, int i_end, int p_start, int p_end) {
	if (i_start == i_end)			return;

	if (i_start + 1 == i_end) {
		cout << inorder[i_start] << " ";
		return;
	}

	int root = postorder[p_end - 1];
	int index = i_start;
	for (int i = i_start; i < i_end; i++) {
		if (inorder[i] == root) {
			index = i;
			break;
		}
	}

	cout << root << " ";
	preorder(i_start, index, p_start, p_start + (index - i_start));
	preorder(index + 1, i_end, p_start + (index - i_start), p_end - 1);
}
