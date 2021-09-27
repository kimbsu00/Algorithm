/*
  url: https://www.acmicpc.net/problem/5052
*/

#include <iostream>
#include <vector>
#include <string>
#include <algorithm>

#define SIZE 10

using namespace std;

class Node {
public:
	char ch;
	bool is_end;
	vector<Node*> next;

	Node()
		: ch(' '), is_end(false)
	{
		next = vector<Node*>(SIZE, nullptr);
	}

	Node(char ch)
		: ch(ch), is_end(false)
	{
		next = vector<Node*>(SIZE, nullptr);
	}
};

class Trie {
public:
	Node* root;

	Trie() {
		root = new Node();
	}

	bool insert(string input) {
		return _insert(root, input);
	}

	bool _insert(Node* node, string input) {
		if (node->is_end)			return false;

		if (input.empty()) {
			node->is_end = true;
			return true;
		}
		
		char ch = input[0];
		int idx = ch - '0';

		if (node->next[idx] == nullptr) {
			Node* tmp = new Node(ch);
			node->next[idx] = tmp;
			return _insert(tmp, input.substr(1));
		} 
		else {
			return _insert(node->next[idx], input.substr(1));
		}
	}
};

bool compare(const string& a, const string& b) {
	return a.size() < b.size();
}

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	vector<string> answer;

	int T;
	cin >> T;
	for (int t = 0; t < T; t++) {
		Trie* trie = new Trie();

		int N;
		cin >> N;

		vector<string> inputs(N);
		for (int n = 0; n < N; n++) {
			cin >> inputs[n];
		}
		sort(inputs.begin(), inputs.end(), compare);

		bool flag = true;
		for (string input: inputs) {
			if (!(flag = trie->insert(input)))			break;
		}
		answer.push_back(flag ? "YES" : "NO");
	}

	for (string ans : answer) {
		cout << ans << "\n";
	}

	return 0;
}
