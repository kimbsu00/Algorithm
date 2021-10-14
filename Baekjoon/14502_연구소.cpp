/*
  url: https://www.acmicpc.net/problem/14502
*/

#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

int N, M;
vector<vector<int>> map;
vector<pair<int, int>> virus_pos;
int wall_num = 0;
// top, right, bottom, left
int dx[4] = { -1, 0, 1, 0 };
int dy[4] = { 0, 1, 0, -1 };

int get_safety_area() {
	vector<vector<bool>> visited(N, vector<bool>(M, false));

	queue<pair<int, int>> q;
	int virus_area = 0;
	for (pair<int, int> pos : virus_pos) {
		q.push(pos);

		while (!q.empty()) {
			pair<int, int> tmp = q.front();
			q.pop();
			
			if (visited[tmp.first][tmp.second])			continue;

			virus_area += 1;
			visited[tmp.first][tmp.second] = true;

			for (int i = 0; i < 4; i++) {
				int x = tmp.first + dx[i];
				int y = tmp.second + dy[i];

				if (0 <= x && x < N && 0 <= y && y < M) {
					if (map[x][y] == 0 && !visited[x][y]) {
						q.push({ x,y });
					}
				}
			}
		}
	}

	return (N * M) - wall_num - virus_area - 3;
}

int solve(int x, int y, int block) {
	if (block == 0) {
		return get_safety_area();
	}

	if (x == N) {
		return 0;
	}

	int ret = 0;
	int next_y = (y + 1 == M ? 0 : y + 1);
	int next_x = (next_y == 0 ? x + 1 : x);

	ret = max(ret, solve(next_x, next_y, block));

	if (map[x][y] == 0) {
		map[x][y] = 1;
		ret = max(ret, solve(next_x, next_y, block - 1));
		map[x][y] = 0;
	}

	return ret;
}

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> N >> M;
	map = vector<vector<int>>(N, vector<int>(M, 0));
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> map[i][j];
			if (map[i][j] == 2) {
				virus_pos.push_back({ i,j });
			} 
			else if (map[i][j] == 1) {
				wall_num += 1;
			}
		}
	}

	int answer = solve(0, 0, 3);
	cout << answer << "\n";

	return 0;
}
