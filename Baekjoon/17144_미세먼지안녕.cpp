/*
  url: https://www.acmicpc.net/problem/17144
*/

#include <iostream>
#include <vector>

using namespace std;

int R, C, T;
pair<int, int> cleaner_top, cleaner_bottom;
vector<vector<int>> room;

void dust_spread() {
	vector<vector<int>> tmp(R + 2, vector<int>(C + 2, 0));
	for (int r = 1; r < R + 1; r++) {
		for (int c = 1; c < C + 1; c++) {
			if (room[r][c] == -1 || room[r][c] == 0)			continue;

			int room_num = 4;
			if (room[r - 1][c] == -1)			room_num--;
			if (room[r][c + 1] == -1)			room_num--;
			if (room[r + 1][c] == -1)			room_num--;
			if (room[r][c - 1] == -1)			room_num--;

			if (room_num != 0) {
				int spread_amount = room[r][c] * 0.2;
				if (room[r - 1][c] != -1)			tmp[r - 1][c] += spread_amount;
				if (room[r][c + 1] != -1)			tmp[r][c + 1] += spread_amount;
				if (room[r + 1][c] != -1)			tmp[r + 1][c] += spread_amount;
				if (room[r][c - 1] != -1)			tmp[r][c - 1] += spread_amount;
				room[r][c] -= spread_amount * room_num;
			}
		}
	}

	for (int r = 1; r < R + 1; r++) {
		for (int c = 1; c < C + 1; c++) {
			if (room[r][c] != -1) {
				room[r][c] += tmp[r][c];
			}
		}
	}
}

void cleaner_work() {
	for (int r = cleaner_top.first - 1; r > 1; r--) {
		room[r][1] = room[r - 1][1];
	}
	for (int c = 1; c < room[0].size() - 2; c++) {
		room[1][c] = room[1][c + 1];
	}
	int idx = room[0].size() - 2;
	for (int r = 1; r < cleaner_top.first; r++) {
		room[r][idx] = room[r + 1][idx];
	}
	for (int c = idx; c > 2; c--) {
		room[cleaner_top.first][c] = room[cleaner_top.first][c - 1];
	}
	room[cleaner_top.first][2] = 0;

	for (int r = cleaner_bottom.first + 1; r < room.size() - 2; r++) {
		room[r][1] = room[r + 1][1];
	}
	idx = room.size() - 2;
	for (int c = 1; c < room[0].size() - 2; c++) {
		room[idx][c] = room[idx][c + 1];
	}
	idx = room[0].size() - 2;
	for (int r = room.size() - 2; r > cleaner_bottom.first; r--) {
		room[r][idx] = room[r - 1][idx];
	}
	for (int c = idx; c > 2; c--) {
		room[cleaner_bottom.first][c] = room[cleaner_bottom.first][c - 1];
	}
	room[cleaner_bottom.first][2] = 0;
}

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> R >> C >> T;
	room = vector<vector<int>>(R + 2, vector<int>(C + 2, -1));
	cleaner_top = { -1,-1 };
	cleaner_bottom = { -1,-1 };

	for (int r = 1; r < R + 1; r++) {
		for (int c = 1; c < C + 1; c++) {
			cin >> room[r][c];

			if (room[r][c] == -1) {
				if (cleaner_top.first == -1) {
					cleaner_top = { r,c };
				}
				else {
					cleaner_bottom = { r,c };
				}
			}
		}
	}

	for (int i = 0; i < T; i++) {
		dust_spread();
		cleaner_work();
	}

	int answer = 0;
	for (int r = 1; r < R + 1; r++) {
		for (int c = 1; c < C + 1; c++) {
			if (room[r][c] != -1) {
				answer += room[r][c];
			}
		}
	}
	cout << answer << "\n";

	return 0;
}
