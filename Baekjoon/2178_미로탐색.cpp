/*
  url: https://www.acmicpc.net/problem/2178
*/

#include<iostream>
#include<vector>
#include<string>
#include<queue>

using namespace std;

void bfs(int row, int col);

vector<vector<int>> map;
vector <vector<bool>> visited;
vector<vector<int>> temp;
int d[4][2] = { {1,0} , {-1,0} ,{0,1},{0,-1} };
int N, M;

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	cin >> N >> M;

	map = vector<vector<int>>(N + 2, vector<int>(M + 2, 0));
	visited = vector<vector<bool>>(N + 2, vector<bool>(M + 2, false));
	temp = vector<vector<int>>(N + 2, vector<int>(M + 2, 1));

	for (int i = 0; i < N; i++) {
		string str;
		cin >> str;
		for (int j = 0; j < str.size(); j++) {
			map[i + 1][j + 1] = str[j] - '0';
		}
	}

	bfs(1, 1);

	cout << temp[N][M] << "\n";

	return 0;
}

void bfs(int row, int col) {
	queue<pair<int, int>> q;
	q.push(make_pair(row, col));

	int ret = 1;
	while (!q.empty()) {
		int row = q.front().first;
		int col = q.front().second;
		q.pop();

		for (int i = 0; i < 4; i++) {
			int nextRow = row + d[i][0];
			int nextCol = col + d[i][1];

			if (!visited[nextRow][nextCol] && map[nextRow][nextCol]) {
				temp[nextRow][nextCol] = temp[row][col] + 1;
				visited[nextRow][nextCol] = true;
				q.push(make_pair(nextRow, nextCol));
			}
		}
	}
}
