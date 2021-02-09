/*
  url: https://www.acmicpc.net/problem/5052
  
  트라이를 직접 구현해서 해결함.
  트라이에 문자열을 Insert 하기 전에 문자열 길이에 대하여 오름차순 정렬을 수행한 후에 Insert 를 진행함.
  임의의 전화번호(A)가 다른 전화번호(B)의 접두사가 되려면, A 의 길이 < B 의 길이 이어야만 하기 때문에,
  길이가 짧은 전화번호를 먼저 Insert 하고, 길이가 긴 전화번호를 Insert 하면,
  길이가 긴 전화번호를 Insert 하는 과정에서 이전에 Insert 했던 전화번호가 존재하는지 여부를 쉽게 판단할 수 있다.
*/

#include<iostream>
#include<vector>
#include<string>
#include<algorithm>

using namespace std;

class Node
{
public:
	char data;
	bool isEnd;
	vector<Node*> next[10];

public:
	Node();
	Node(char data, bool isEnd);
	~Node();
};

Node::Node()
	: data(' '), isEnd(false)
{
}

Node::Node(char data, bool isEnd)
	: data(data), isEnd(isEnd)
{
}

Node::~Node()
{
}

class Trie
{
public:
	vector<Node*> root;

public:
	Trie();
	~Trie();

	bool Insert(string input);
	bool _Insert(Node* node, string input);
};

Trie::Trie()
	: root(vector<Node*>(10))
{
	for (int i = 0; i < 10; i++) {
		root[i] = new Node('0' + i, false);
	}
}

Trie::~Trie()
{
}

bool Trie::Insert(string input)
{
	char ch = input[0];
	int index = ch - '0';
    
    	if (input.size() == 1)
		root[index]->isEnd = true;

	return _Insert(root[index], input.substr(1));
}

bool Trie::_Insert(Node* node, string input)
{
	if (input.size() == 0)			return true;

	if (node->isEnd)			return false;

	char ch = input[0];
	int index = ch - '0';
	for (Node* next : node->next[index]) {
		if (next->data == ch) {
			return _Insert(next, input.substr(1));
		}
	}

	Node* next = new Node(ch, input.size() == 1);
	node->next[index].push_back(next);
	return _Insert(next, input.substr(1));
}

bool compare(const string& a, const string& b);

vector<string> number;

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int T;
	cin >> T;
	vector<bool> answer(T, true);

	for (int i = 0; i < T; i++) {
		int N;
		cin >> N;

		number = vector<string>(N);
		for (int j = 0; j < N; j++) {
			cin >> number[j];
		}

		sort(number.begin(), number.end(), compare);

		Trie trie;
		for (string input : number) {
			if (!trie.Insert(input)) {
				answer[i] = false;
				break;
			}
		}
	}

	for (bool output : answer)
		cout << (output ? "YES\n" : "NO\n");

	return 0;
}

bool compare(const string& a, const string& b) {
	return a.size() < b.size();
}
