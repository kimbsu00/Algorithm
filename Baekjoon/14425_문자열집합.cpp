/*
  url: https://www.acmicpc.net/problem/14425
  
  트라이를 직접 구현해서 제출한 결과, 
  너무나 당연스럽게도 시간초과 발생..
*/

#include<iostream>
#include<vector>
#include<string>

using namespace std;

class Node
{
public:
	char data;
	bool isEnd;
	Node* next[26];

public:
	Node();
	Node(char data, bool isEnd);
	~Node();
};

Node::Node()
	: data(' '), isEnd(false)
{
	for (int i = 0; i < 26; i++)
		next[i] = nullptr;
}

Node::Node(char data, bool isEnd)
	: data(data), isEnd(isEnd)
{
	for (int i = 0; i < 26; i++)
		next[i] = nullptr;
}

Node::~Node()
{
}

class Trie
{
public:
	Node* root;

public:
	Trie();
	~Trie();

	void Insert(string input);
	void _Insert(Node* node, string input);

	bool Find(const string& target);
	bool _Find(Node* node, const string& target);
};

Trie::Trie()
	: root(new Node())
{
}

Trie::~Trie()
{
}

void Trie::Insert(string input)
{
	_Insert(root, input);
}

void Trie::_Insert(Node* node, string input)
{
	if (input.size() == 0)			return;
	
	char ch = input[0];
	int index = ch - 'a';
	if (node->next[index] != nullptr) {
		return _Insert(node->next[index], input.substr(1));
	}

	Node* next = new Node(ch, input.size() == 1);
	node->next[index] = next;
	return _Insert(next, input.substr(1));
}

bool Trie::Find(const string& target)
{
	return _Find(root, target);
}

bool Trie::_Find(Node* node, const string& target)
{
	if (target.size() == 0 && node->isEnd)			return true;

	if (target.size() == 0)			return false;

	char ch = target[0];
	int index = ch - 'a';
	if (node->next[index] != nullptr) {
		return _Find(node->next[index], target.substr(1));
	}

	return false;
}

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	int N, M;
	cin >> N >> M;

	Trie trie;
	for (int i = 0; i < N; i++) {
		string input;
		cin >> input;
		trie.Insert(input);
	}

	int output = 0;
	for (int i = 0; i < M; i++) {
		string target;
		cin >> target;
		if (trie.Find(target)) {
			output += 1;
		}
	}

	cout << output << "\n";

	return 0;
}
