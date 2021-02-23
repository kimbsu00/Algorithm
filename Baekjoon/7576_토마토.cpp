/*
  url: https://www.acmicpc.net/problem/7576
*/

#include<iostream>
#include<vector>
#include<queue>
#include<algorithm>

using namespace std;

int bfs();

int N, M;
vector<vector<int>> graph;
vector<pair<int, int>> start;
vector <vector<int>> visited;
int dr[4] = { 1, -1, 0, 0 };
int dc[4] = { 0, 0, 1, -1 };

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> M >> N;

	graph = vector<vector<int>>(N, vector<int>(M));
	visited = vector<vector<int>>(N, vector<int>(M, -1));

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			cin >> graph[i][j];
			if (graph[i][j] == 1) {
				start.push_back(make_pair(i, j));
				visited[i][j] = 0;
			}
		}
	}

	cout << bfs() << "\n";

	return 0;
}

int bfs() {
	queue<pair<int, int>> q;
	for (int i = 0; i < start.size(); i++) {
		q.push(start[i]);
	}

	while (!q.empty()) {
		int row = q.front().first;
		int col = q.front().second;
		q.pop();

		for (int i = 0; i < 4; i++) {
			int nextR = row + dr[i];
			int nextC = col + dc[i];
			
			if (nextR < 0 || nextR >= N || nextC < 0 || nextC >= M)			continue;

			if (graph[nextR][nextC] == 0 && visited[nextR][nextC] == -1) {
				visited[nextR][nextC] = visited[row][col] + 1;
				q.push(make_pair(nextR, nextC));
			}
		}
	}

	int ret = 0;
	bool check = false;
	for (int i = 0; i < N; i++) {
		for (int j = 0; j < M; j++) {
			ret = max(ret, visited[i][j]);

			if (graph[i][j] == 0 && visited[i][j] == -1) {
				check = true;
				break;
			}
		}
	}

	check ? ret = -1 : ret;

	return ret;
}
