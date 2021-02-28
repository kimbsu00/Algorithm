/*
  url: https://www.acmicpc.net/problem/14725
*/

#include<iostream>
#include<vector>
#include<string>
#include<map>

using namespace std;

class Node {
public:
	map<string, Node*> children;
	map<string, Node*>::iterator it;

	void Insert(vector<string>& input, int index) {
		if (index == input.size())			return;

		string str = input[index];
		it = children.find(str);

		// 이미 존재하는 경우, 재귀호출
		if (it != children.end()) {
			it->second->Insert(input, index + 1);
		}
		// 존재하지 않는 경우, 새롭게 추가해주면 된다.
		else {
			Node* node = new Node();
			children.insert(make_pair(str, node));
			node->Insert(input, index + 1);
		}
	}

	void Print(int floor) {
		for (auto child = children.begin(); child != children.end(); child++) {
			for (int i = 0; i < floor; i++) {
				cout << "--";
			}
			cout << child->first << "\n";
			child->second->Print(floor + 1);
		}
	}
};

Node root;

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int N;
	cin >> N;

	for (int i = 0; i < N; i++) {
		int K;
		cin >> K;
		vector<string> vec(K);
		for (int j = 0; j < K; j++) {
			cin >> vec[j];
		}
		root.Insert(vec, 0);
	}

	root.Print(0);

	return 0;
}
