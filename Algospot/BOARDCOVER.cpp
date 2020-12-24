/*
	url: https://algospot.com/judge/problem/read/BOARDCOVER
*/

#include<iostream>	
#include<algorithm>
#include<vector>

using namespace std;

int solve();
bool check(int x, int y, int type);

bool board[22][22];
int H, W;

/*
	□■	■■	■■	■□
	■■	■□	□■	■■
*/
const int blockType[4][3][2] = {
	{ {0,0},{1,0},{1,-1} } ,
	{ {0,0},{1,0},{0,1} },
	{ {0,0},{0,1},{1,1} },
	{ {0,0},{1,0},{1,1} }
};

int main(void) {
	int C;
	cin >> C;
	vector<int> answer(C);

	for (int i = 0; i < C; i++) {
		cin >> H >> W;

		fill(&board[0][0], &board[21][22], false);

		int count = 0;
		for (int j = 0; j < H; j++) {
			for (int k = 0; k < W; k++) {
				char ch;
				cin >> ch;
				if (ch == '.') {
					board[j + 1][k + 1] = true;
					count++;
				}
			}
		}
		if (count % 3 == 0)
			answer[i] = solve();
		else
			answer[i] = 0;
	}

	for (int i = 0; i < C; i++)
		cout << answer[i] << endl;

	return 0;
}

int solve() {
	int x = -1, y = -1;

	for (int i = 1; i < H + 1; i++) {
		for (int j = 1; j < W + 1; j++) {
			if (board[i][j]) {
				x = i;
				y = j;
				break;
			}
		}
		if (x != -1)
			break;
	}

	// 빈칸인 블록이 존재하지 않는 경우 -> 모든 칸이 블록으로 채워진 경우
	if (x == -1 && y == -1) {
		return 1;
	}

	int ret = 0;
	for (int type = 0; type < 4; type++) {
		if (check(x, y, type)) {
			for (int i = 0; i < 3; i++) {
				board[x + blockType[type][i][0]][y + blockType[type][i][1]] = false;
			}
			ret += solve();
			for (int i = 0; i < 3; i++) {
				board[x + blockType[type][i][0]][y + blockType[type][i][1]] = true;
			}
		}
	}

	return ret;
}

bool check(int x, int y, int type) {
	bool ret = true;

	for (int i = 0; i < 3; i++) {
		ret = ret && board[x + blockType[type][i][0]][y + blockType[type][i][1]];
	}

	return ret;
}
