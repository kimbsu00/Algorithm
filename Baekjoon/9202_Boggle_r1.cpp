/*
  url: https://www.acmicpc.net/problem/9202
  
  (https://github.com/kimbsu00/Algorithm/blob/master/Baekjoon/9202_Boggle.cpp) 에 올려두었던 코드의 문제점은 다음과 같다.
  1. 트라이에 존재하는 문자를 찾았음에도 불구하고, 단어를 찾음을 확인하는 코드가 그 다음번 재귀호출에 존재한다.
     따라서 문자를 찾은 상태에서 주변에 존재하는 다른 주사위들이 이미 방문했거나, 인덱스 범위 외부인 경우에는,
     단어를 찾았음에도 불구하고 찾지 못한 것으로 계산되어 정답에 포함되지 않는 문제가 발생한다.
     이를 해결하기 위해서 Search() 함수를 수정했다.
     
  2. 트라이를 구현할 때, map<char, Node*> 를 이용했는데
     이렇게 구현할 경우에 발생가능한 문제점은 Insert() 함수의 속도가 느려진다는 것이다.
     Insert() 함수에서는 매개변수로 전달받은 char 변수가 map 에 존재하는지 여부를 확인하고,
     만약 존재한다면 바로 재귀호출을 하고, 존재하지 않는다면 map 에 make_pair(char, Node*) 를 추가하고 재귀호출을 했는데
     map 의 insert 함수는 log(n) 의 시간이 걸리기 때문에
     log(1) 의 시간이 걸리는 아래 코드보다 훨씬 느린 속도를 갖게 됨을 알게 되었다.
     
  3. Search() 함수를 수정한 상태에서는 정답은 나오지만, 시간초과가 발생했다.
     이는 set<string> 에 찾은 단어를 insert() 하는 횟수 때문에 발생한 것으로 추측된다.
     이 때문에 Search() 함수의 틀을 크게 한 번 바꾸게 되었다.
*/

#include<iostream>
#include<vector>
#include<string>
#include<set>

using namespace std;

int getScore(int count);

const int GAMESIZE = 4;
vector<string> board;
vector<vector<bool>> visited;
// 12시 방향에서 시작해서 시계방향으로 돌아감
int dr[8] = { -1, -1, 0, 1, 1, 1, 0, -1 };
int dc[8] = { 0, 1, 1, 1, 0, -1, -1, -1 };
set<string> s;
int score = 0;

struct Node {
public:
	Node* children[26];
	bool isEnd;

	Node() : isEnd(false) {
		fill(&children[0], &children[26], nullptr);
	}

	void Insert(const char* ch) {
		if (*ch == '\0')			isEnd = true;
		else {
			int cur = *ch - 'A';
			if (children[cur] == nullptr)			children[cur] = new Node();
			children[cur]->Insert(ch + 1);
		}
	}

	void Search(int row, int col, string word) {
		if (word.size() > 8)			return;

		visited[row][col] = true;
		word += board[row][col];

		Node* child = children[board[row][col] - 'A'];
		if (child == nullptr) {
			visited[row][col] = false;
			return;
		}
		if (child->isEnd) {
			auto it = s.insert(word);
			if(it.second)
				score += getScore(word.size());
		}
		for (int i = 0; i < 8; i++) {
			int nextR = row + dr[i];
			int nextC = col + dc[i];
			if (nextR < 0 || nextR >= 4 || nextC < 0 || nextC >= 4)			continue;
			if (visited[nextR][nextC])			continue;
			child->Search(nextR, nextC, word);
		}
		visited[row][col] = false;
	}
};

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	Node* root = new Node();

	int W;
	cin >> W;
	for (int i = 0; i < W; i++) {
		char input[10] = {};
		cin >> input;
		root->Insert(input);
	}

	int B;
	cin >> B;
	for (int i = 0; i < B; i++) {
		board = vector<string>(GAMESIZE);
		visited = vector<vector<bool>>(GAMESIZE, vector<bool>(GAMESIZE, false));
		s.clear();
		for (int j = 0; j < GAMESIZE; j++) {
			cin >> board[j];
		}

		score = 0;
		for (int row = 0; row < GAMESIZE; row++) {
			for (int col = 0; col < GAMESIZE; col++) {
				root->Search(row, col, "");
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
