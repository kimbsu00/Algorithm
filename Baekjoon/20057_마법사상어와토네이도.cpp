/*
  url: https://www.acmicpc.net/problem/20057
*/

#include <iostream>
#include <vector>

using namespace std;

enum Direction {
	LEFT = 0,
	DOWN = 1,
	RIGHT = 2,
	UP = 3
};

int N;
vector<vector<int>> map;
int dx[4][10] = {
	{-1, 1, -1, 1, -2, 2, -1, 1, 0, 0},		// left
	{-1, -1, 0, 0, 0, 0, 1, 1, 2, 1},		// down
	{-1, 1, -1, 1, -2, 2, -1, 1, 0, 0},		// right
	{1, 1, 0, 0, 0, 0, -1, -1, -2, -1}		// up
};
int dy[4][10] = {
	{1, 1, 0, 0, 0, 0, -1, -1, - 2, -1},	// left
	{-1, 1, -1, 1, -2, 2, -1, 1, 0, 0},		// down
	{-1, -1, 0, 0, 0, 0, 1, 1, 2, 1},		// right
	{-1, 1, -1, 1, -2, 2, -1, 1, 0, 0}		// up
};
float d[10] = { 0.01, 0.01, 0.07, 0.07, 0.02, 0.02, 0.1, 0.1, 0.05 };

void calculate(int x, int y, int dir) {
	int sand = map[x][y];
	int sum = 0;
	int X, Y;
	for (int i = 0; i < 9; i++) {
		X = x + dx[dir][i];
		Y = y + dy[dir][i];
		int value = (int)sand * d[i];
		sum += value;
		map[X][Y] += value;
	}
	X = x + dx[dir][9];
	Y = y + dy[dir][9];
	map[X][Y] += (sand - sum);

	map[x][y] = 0;
}

int solve(int x, int y) {
	int ret = 0;
	int count = 0;
	int loop = 1;
	while (!(x == 2 && y == 2)) {
		for (int i = 0; i < loop; i++) {
			int dir = count % 4;
			switch (dir) {
			case LEFT:
				y--;
				calculate(x, y, LEFT);
				break;
			case DOWN:
				x++;
				calculate(x, y, DOWN);
				break;
			case RIGHT:
				y++;
				calculate(x, y, RIGHT);
				break;
			case UP:
				x--;
				calculate(x, y, UP);
				break;
			}

			if (x == 2 && y == 2)			break;
		}
		count++;
		if (count % 2 == 0)			loop++;
	}

	for (int i = 0; i < map.size(); i++) {
		for (int j = 0; j < map[i].size(); j++) {
			if (i >= 2 && j >= 2 && i < map.size() - 2 && j < map[i].size() - 2)			continue;

			ret += map[i][j];
		}
	}
	return ret;
}

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> N;
	map = vector<vector<int>>(N + 4, vector<int>(N + 4, 0));

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> map[i + 2][j + 2];
		}
	}

	int center = N / 2 + 2;
	int answer = solve(center, center);
	cout << answer << "\n";

	return 0;
}
