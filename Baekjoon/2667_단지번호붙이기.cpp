/*
  url: https://www.acmicpc.net/problem/2667
*/

#include<iostream>
#include<vector>
#include<string>
#include<queue>
#include<algorithm>

using namespace std;

void bfs(int row, int col);

int map[27][27];
int d[4][2] = { {1,0} , {-1,0} ,{0,1},{0,-1} };
vector<int> answer;

int main(void) {
	ios_base::sync_with_stdio(0);
	cin.tie(0);

	fill(&map[0][0], &map[26][27], 0);

	int N;
	cin >> N;
	for (int i = 0; i < N; i++) {
		string str;
		cin >> str;
		for (int j = 0; j < N; j++) {
			map[i + 1][j + 1] = str[j] - '0';
		}
	}

	for (int i = 0; i < N; i++) {
		for (int j = 0; j < N; j++) {
			if (map[i + 1][j + 1] == 1) {
				bfs(i + 1, j + 1);
			}
		}
	}

	sort(answer.begin(), answer.end(), less<int>());
	cout << answer.size() << "\n";
	for (int output : answer) {
		cout << output << "\n";
	}
	
	return 0;
}

void bfs(int row, int col) {
	int ret = 1;

	queue<pair<int, int>> q;
	map[row][col] = 0;
	q.push(make_pair(row, col));

	while (!q.empty()) {
		int row = q.front().first;
		int col = q.front().second;
		q.pop();

		for (int i = 0; i < 4; i++) {
			int nextR = row + d[i][0];
			int nextC = col + d[i][1];

			if (map[nextR][nextC]) {
				ret += 1;
				map[nextR][nextC] = 0;
				q.push(make_pair(nextR, nextC));
			}
		}
	}

	answer.push_back(ret);
}
