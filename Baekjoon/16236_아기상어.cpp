/*
  url: https://www.acmicpc.net/problem/16236
*/

#include <iostream>
#include <vector>
#include <queue>
#include <cmath>

using namespace std;

int N;
vector<vector<int>> space;
pair<int, int> shark_pos;
int shark_size = 2;
int eat = 0;
int dx[4] = { -1, 0, 0, 1 };			// top, left, right, bottom
int dy[4] = { 0, -1, 1, 0 };

int solve(pair<int, int> init_pos) {
	vector<vector<int>> dist(N, vector<int>(N, -1));
	dist[init_pos.first][init_pos.second] = 0;

	queue<pair<int, int>> q;
	q.push(init_pos);

	while (!q.empty()) {
		int x = q.front().first;
		int y = q.front().second;
		q.pop();

		if (space[x][y] != 9 && space[x][y] != 0 && space[x][y] < shark_size)			continue;

		for (int i = 0; i < 4; i++) {
			int cx = x + dx[i];
			int cy = y + dy[i];

			if (cx < 0 || cx >= N || cy < 0 || cy >= N)			continue;

			if (dist[cx][cy] == -1 && space[cx][cy] <= shark_size) {
				dist[cx][cy] = dist[x][y] + 1;
				q.push({ cx,cy });
			}
		}
	}

	int x = -1, y = -1;
	int min_dist = 987654321;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (space[i][j] != 9 && space[i][j] != 0 && space[i][j] < shark_size && dist[i][j] != -1 && min_dist > dist[i][j]) {
				x = i;
				y = j;
				min_dist = dist[i][j];
			}
		}
	}

	if (min_dist != 987654321) {
		space[init_pos.first][init_pos.second] = 0;
		space[x][y] = 9;
		shark_pos = { x,y };

		eat += 1;
		if (eat == shark_size) {
			eat = 0;
			shark_size += 1;
		}
		return min_dist;
	}

	return 0;
}

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> N;
	space = vector<vector<int>>(N, vector<int>(N, 0));

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			cin >> space[i][j];
			
			if (space[i][j] == 9)
				shark_pos = { i,j };
		}
	}

	int answer = 0;
	while (true) {
		int tmp = solve(shark_pos);
		if (tmp == 0)			break;
		answer += tmp;
	}
	cout << answer << "\n";

	return 0;
}
