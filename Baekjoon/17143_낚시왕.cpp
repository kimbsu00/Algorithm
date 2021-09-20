/*
  url: https://www.acmicpc.net/problem/17143
*/

#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

enum Direction {
	UP = 1,
	DOWN = 2,
	RIGHT = 3,
	LEFT = 4
};

int R, C, M;

class Shark {
public:
	int idx;
	int x, y, s, d, z;

	Shark(int idx, int x, int y, int s, int d, int z)
		: idx(idx), x(x), y(y), s(s), d(d), z(z)
	{}

	bool operator < (const Shark& other) const {
		return this->z < other.z;
	}
};

class Pool {
public:
	vector<Shark> sharks;
	int** loc;

	Pool(int R, int C) {
		loc = new int*[R];
		for (int i = 0; i < R; i++) {
			loc[i] = new int[C];
		}

		for (int r = 0; r < R; r++) {
			for (int c = 0; c < C; c++) {
				loc[r][c] = -1;
			}
		}
	}

	void insert_shark(Shark shark) {
		this->sharks.push_back(shark);
		loc[shark.x][shark.y] = shark.idx;
	}

	void sort_sharks() {
		sort(sharks.begin(), sharks.end());
	}

	pair<int, int> move(int loc, int dir, int dist) {
		pair<int, int> ret = { -1,-1 };

		while (dist-- > 0) {
			if (dir == UP) {
				if (loc == 0) {
					loc++;
					dir = DOWN;
				}
				else {
					loc--;
				}
			}
			else if (dir == DOWN) {
				if (loc == R - 1) {
					loc--;
					dir = UP;
				}
				else {
					loc++;
				}
			}
			else if (dir == RIGHT) {
				if (loc == C - 1) {
					loc--;
					dir = LEFT;
				}
				else {
					loc++;
				}
			}
			else if (dir == LEFT) {
				if (loc == 0) {
					loc++;
					dir = RIGHT;
				}
				else {
					loc--;
				}
			}
		}
		ret.first = loc;
		ret.second = dir;

		return ret;
	}

	void move_shark() {
		vector<bool> dead_shark(M, false);
		vector<vector<int>> new_loc(R, vector<int>(C, -1));
		for (int i = 0; i < sharks.size(); i++) {
			loc[sharks[i].x][sharks[i].y] = -1;
			int dist;
			pair<int, int> tmp;
			switch (sharks[i].d) {
			case UP:
				dist = sharks[i].s % (R * 2 - 2);
				tmp = move(sharks[i].x, UP, dist);
				sharks[i].x = tmp.first;
				sharks[i].d = tmp.second;
				break;
			case DOWN:
				dist = sharks[i].s % (R * 2 - 2);
				tmp = move(sharks[i].x, DOWN, dist);
				sharks[i].x = tmp.first;
				sharks[i].d = tmp.second;
				break;
			case RIGHT:
				dist = sharks[i].s % (C * 2 - 2);
				tmp = move(sharks[i].y, RIGHT, dist);
				sharks[i].y = tmp.first;
				sharks[i].d = tmp.second;
				break;
			case LEFT:
				dist = sharks[i].s % (C * 2 - 2);
				tmp = move(sharks[i].y, LEFT, dist);
				sharks[i].y = tmp.first;
				sharks[i].d = tmp.second;
				break;
			}

			int x = sharks[i].x;
			int y = sharks[i].y;
			if (new_loc[x][y] != -1) {
				dead_shark[new_loc[x][y]] = true;
			}
			new_loc[x][y] = sharks[i].idx;
		}

		for (int i = sharks.size() - 1; i >= 0; i--) {
			if (dead_shark[sharks[i].idx]) {
				sharks.erase(sharks.begin() + i);
			}
			else {
				int x = sharks[i].x;
				int y = sharks[i].y;
				loc[x][y] = sharks[i].idx;
			}
		}
	}

	int fish_shark(int col) {
		int ret = 0;
		int idx = -1;

		for (int row = 0; row < R; row++) {
			if (loc[row][col] != -1) {
				idx = loc[row][col];
				loc[row][col] = -1;
				break;
			}
		}

		if (idx != -1) {
			auto it = sharks.begin();
			for (; it != sharks.end(); it++) {
				if ((*it).idx == idx)			break;
			}
			ret = (*it).z;
			sharks.erase(it);
		}

		return ret;
	}
};

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> R >> C >> M;

	Pool pool(R, C);
	for (int i = 0; i < M; i++) {
		int r, c, s, d, z;
		cin >> r >> c >> s >> d >> z;
		Shark shark(i, r - 1, c - 1, s, d, z);
		pool.insert_shark(shark);
	}
	pool.sort_sharks();

	int answer = 0;
	for (int i = 0; i < C; i++) {
		answer += pool.fish_shark(i);
		pool.move_shark();
	}
	cout << answer << "\n";

	return 0;
}
