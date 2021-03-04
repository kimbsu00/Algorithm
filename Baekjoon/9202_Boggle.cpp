/*
  url: https://www.acmicpc.net/problem/9202
  
  최근 몇일동안 이 문제를 계속 고민했는데 어떤 반례 때문에 이 코드가 오답이 되는지 도저히 모르겠다...
*/

#include<iostream>
#include<vector>
#include<string>
#include<map>
#include<algorithm>
#include<set>

#define GAMESIZE 4

using namespace std;

struct Node {
public:
	map<char, Node*> children;
	bool isEnd = false;

	void Insert(string& input, int index) {
		if (index == input.size()) {
			isEnd = true;
			return;
		}

		char ch = input[index];
		Node* node = new Node();

		auto _it = children.insert(make_pair(ch, node));
		if (!_it.second) {
			return _it.first->second->Insert(input, index + 1);
		}

		return node->Insert(input, index + 1);
	}
};

int solve(int row, int col, Node* node, string word);
int getScore(int count);

Node* root;
vector<vector<char>> board;
vector<vector<bool>> visited;
int dr[8] = { -1, -1, 0, 1, 1, 1, 0, -1 };
int dc[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };
set<string> s;

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	root = new Node();

	int W;
	cin >> W;
	for (int i = 0; i < W; i++) {
		string str;
		cin >> str;
		root->Insert(str, 0);
	}

	int B;
	cin >> B;
	for (int i = 0; i < B; i++) {
		board = vector<vector<char>>(GAMESIZE, vector<char>(GAMESIZE));
		visited = vector<vector<bool>>(GAMESIZE, vector<bool>(GAMESIZE, false));
		s.clear();
		for (int j = 0; j < GAMESIZE; j++) {
			string str;
			cin >> str;
			for (int k = 0; k < GAMESIZE; k++) {
				board[j][k] = str[k];
			}
		}

		int score = 0;
		for (int row = 0; row < GAMESIZE; row++) {
			for (int col = 0; col < GAMESIZE; col++) {
				score += solve(row, col, root, "");
			}
		}

		string maxLength = "";
		for (string str : s) {
			if (str.size() > maxLength.size()) {
				maxLength = str;
			}
		}
		cout << score << " " << maxLength << " " << s.size() << "\n";
	}

	return 0;
}

int solve(int row, int col, Node* node, string word) {
	// out of index range
	if (row < 0 || row >= GAMESIZE || col < 0 || col >= GAMESIZE)			return 0;

	if (node->children.empty() && node->isEnd) {
		auto it = s.insert(word);
		if (it.second)
			return getScore(word.size());
		return 0;
	}

	if (visited[row][col])			return 0;

	visited[row][col] = true;

	int ret = 0;
	if (node->isEnd) {
		auto it = s.insert(word);
		if (it.second)
			ret += getScore(word.size());
	}

	for (auto it = node->children.begin(); it != node->children.end(); it++) {
		if (it->first == board[row][col]) {
			for (int i = 0; i < 8; i++) {
				int nextR = row + dr[i];
				int nextC = col + dc[i];
				ret += solve(nextR, nextC, it->second, word + it->first);
			}
		}
	}

	visited[row][col] = false;
	return ret;
}

int getScore(int count) {
	if (count == 3 || count == 4)
		return 1;
	else if (count == 5)
		return 2;
	else if (count == 6)
		return 3;
	else if (count == 7)
		return 5;
	else if (count == 8)
		return 11;
	else
		return 0;
}
