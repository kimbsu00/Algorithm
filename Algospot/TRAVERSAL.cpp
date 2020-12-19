/*
  url: https://algospot.com/judge/problem/read/TRAVERSAL
  
  문제의 예제만 보고 BST 라고 넘겨집고 문제에 접근해서 삽푸느라 시간이 상당히 걸렸던 문제
*/

#include<iostream>
#include<vector>

using namespace std;

vector<int> postorder(vector<int> preorder, vector<int> inorder);

int main() {
	// number of test case
	int C;
	cin >> C;

	vector<int>* answer = new vector<int>[C];

	for (int i = 0; i < C; i++) {
		// number of node
		int N;
		cin >> N;

		vector<int> preorder(N, -1);
		vector<int> inorder(N, -1);

		// preorder input
		for (int k = 0; k < N; k++) {
			cin >> preorder[k];
		}

		// inorder input
		for (int k = 0; k < N; k++) {
			cin >> inorder[k];
		}

		answer[i] = postorder(preorder, inorder);
	}

	for (int i = 0; i < C; i++) {
		for (int j = 0; j < answer[i].size(); j++) {
			cout << answer[i][j] << " ";
		}
		cout << endl;
	}

	return 0;
}

vector<int> postorder(vector<int> preorder, vector<int> inorder) {
	if (preorder.size() == 0) {
		return preorder;
	}

	// preorder 순회의 첫번째 출력 값은 항상 루트의 데이터 값이 된다.
	int root = preorder[0];

	int index = -1;
	for (int i = 0; i < inorder.size(); i++) {
		if (inorder[i] == root) {
			index = i;
			break;
		}
	}

	// 루트를 기준으로 왼쪽 서브트리가 v1, 오른쪽 서브트리가 v2가 된다.
	vector<int> v1 = postorder(vector<int>(preorder.begin() + 1, preorder.begin() + 1 + index), vector<int>(inorder.begin(), inorder.begin() + index));
	vector<int> v2 = postorder(vector<int>(preorder.begin() + 1 + index, preorder.end()), vector<int>(inorder.begin() + 1 + index, inorder.end()));

	vector<int> ret;
	ret.insert(ret.end(), v1.begin(), v1.end());
	ret.insert(ret.end(), v2.begin(), v2.end());
	ret.push_back(root);

	return ret;
}
