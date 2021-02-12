/*
  url: https://www.acmicpc.net/problem/5670
 
  트라이를 직접 구현했는데,
  50% 에서 메모리초과가 발생하는 코드.
  어디서 최적화를 해야할지 모르겠다.
  나중에 다시 
*/

#include<iostream>
#include<string>
#include<vector>

using namespace std;

struct Node {
	char data;
	bool isEnd;
	Node* next[26];

	Node() : data(' '), isEnd(false) {
		for (int i = 0; i < 26; i++)
			next[i] = nullptr;
	}
	Node(char data, int isEnd) : data(data), isEnd(isEnd) {
		for (int i = 0; i < 26; i++)
			next[i] = nullptr;
	}
};

class Trie
{
public:
	Node* root;

public:
	Trie();
	~Trie();

	void Insert(string input);
	void _Insert(Node* node, string input);

	int calSum();
	int _calSum(Node* node, int sum);
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
	if (input.size() == 0) {
		node->isEnd = true;
		return;
	}

	char ch = input[0];
	int index = ch - 'a';
	if (node->next[index] != nullptr) {
		return _Insert(node->next[index], input.substr(1));
	}

	Node* next = new Node(ch, input.size() == 1);
	node->next[index] = next;
	return _Insert(next, input.substr(1));
}

int Trie::calSum()
{
	int ret = 0;
	for (int i = 0; i < 26; i++) {
		Node* next = root->next[i];
		if (next != nullptr) {
			ret += _calSum(next, 1);
		}
	}
	return ret;
}

int Trie::_calSum(Node* node, int sum)
{
	int ret = 0;

	int count = 0;
	int index = -1;
	for (int i = 0; i < 26; i++) {
		Node* temp = node->next[i];
		if (temp != nullptr) {
			count += 1;
			if (count == 2)		break;
			index = i;
		}
	}

	if (count == 1) {
		Node* next = node->next[index];
		if (node->isEnd) {
			ret += _calSum(next, sum + 1);
		}
		else {
			ret += _calSum(next, sum);
		}
	}
	else if (count > 1) {
		for (int i = index; i < 26; i++) {
			Node* next = node->next[i];
			if (next != nullptr) {
				ret += _calSum(next, sum + 1);
			}
		}
	}

	if (node->isEnd)			ret += sum;

	return ret;
}

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	vector<double> answer;
	int N;
	while (cin >> N) {
		if (cin.eof())			break;

		Trie trie;
		for (int i = 0; i < N; i++) {
			string input;
			cin >> input;
			trie.Insert(input);
		}

		int sum = trie.calSum();
		double output = (double)sum / (double)N;
		answer.push_back(output);
	}

	for (double output : answer) {
		printf("%.2lf\n", output);
	}

	return 0;
}
