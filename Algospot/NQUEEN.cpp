/*
  url: https://algospot.com/judge/problem/read/NQUEEN
  
  처음에는 board 배열에 queen 을 하나 넣을 때마다 queen 이 이동할 수 있는 모든 위치에 false 값을 대입하고 
  재귀호출이 끝나면 이를 다시 true 로 바꿔주면 되겠다고 생각했지만,
  이렇게 하면 임의의 시점에 대하여 현재 queen(A) 을 넣었다가 재귀 호출이 끝나고 퀸을 제거할 때, 이전에 넣어뒀던 queen(B) 의 공격 범위가 변경될 수도 있다는 문제가 존재했다.
  그래서 queen(A) 을 넣을 때 queen(A) 의 공격 범위에 다른 queen(B) 이 존재하는지 체크하는 방법으로 바꿔서 구현함.
  
  또한 checkQueen() 함수에서 각각의 for loop 가 끝나면 if 문으로 종료 조건을 일일이 넣어놨는데,
  이렇게 하지 않을 경우 시간 초과로 오답 처리가 되더라..
  N 의 범위가 최대 12여서 크게 신경 쓰지 않았는데 역시 최적화는 할 수 있으면 하는 게 좋은 것 같다.
*/

#include<iostream>
#include<vector>

using namespace std;

void showBoard();
int NQUEEN(int row, int count);
bool checkQueen(int row, int col);

int N;
// "board[row][col] == false" means queen is at board[row][col]
vector<vector<bool>> board;

int main(void) {
	int C;
	cin >> C;
	vector<int> answer(C);

	for (int i = 0; i < C; i++) {
		cin >> N;
		board = vector<vector<bool>>(N, vector<bool>(N, true));

		answer[i] = NQUEEN(0, 0);
	}

	for (int output : answer) {
		cout << output << endl;
	}

	return 0;
}

int NQUEEN(int row, int count) {
	if (count == N)		return 1;

	if (row == N)		return 0;

	int ret = 0;
	for (int col = 0; col < N; col++) {
		if (checkQueen(row, col)) {
			// push queen
			board[row][col] = false;
			ret += NQUEEN(row + 1, count + 1);
			// pop queen
			board[row][col] = true;
		}
	}

	return ret;
}

// board[row][col] 에 queen 을 놓을 수 있으면 true 반환, 그렇지 않으면 false 반환
bool checkQueen(int row, int col) {
	bool ret = true;

	ret = ret && board[row][col];

	if (!ret)		return ret;

	// up, down, left, right
	for (int i = 0; i < N; i++) {
		ret = ret && board[row][i];
		ret = ret && board[i][col];
	}

	if (!ret)		return ret;

	// right top 
	for (int i = row - 1, j = col + 1; i >= 0 && j < N; i--, j++) {
		ret = ret && board[i][j];
	}

	if (!ret)		return ret;

	// left top
	for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
		ret = ret && board[i][j];
	}

	if (!ret)		return ret;

	// right bottom
	for (int i = row + 1, j = col + 1; i < N && j < N; i++, j++) {
		ret = ret && board[i][j];
	}

	if (!ret)		return ret;

	// left bottom
	for (int i = row + 1, j = col - 1; i < N && j >= 0; i++, j--) {
		ret = ret && board[i][j];
	}

	return ret;
}
