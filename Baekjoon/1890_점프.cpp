#include<iostream>
#include<vector>

using namespace std;

long long find(int row, int col);

vector<vector<int>> board;
long long cache[100][100];

int main(void)
{
	int N;
	cin >> N;

	// input
	for (int i = 0; i < N; i++)
	{
		vector<int> vec(N);
		for (int j = 0; j < N; j++)
		{
			cin >> vec[j];
		}
		board.push_back(vec);
	}

	// reset cache memory
	fill(&cache[0][0], &cache[99][100], -1);

	cout << find(0, 0) << endl;

	return 0;
}

long long find(int row, int col)
{
	// out of index range
	if (row >= board.size() || col >= board.size())
		return 0;

	// arrive right bottom
	if (board[row][col] == 0 && row == board.size() - 1 && col == board.size() - 1)
		return 1;
	else if (board[row][col] == 0)
		return 0;

	long long ret = cache[row][col];

	if (ret != -1)
		return ret;

	ret = find(row + board[row][col], col);
	ret += find(row, col + board[row][col]);

	return cache[row][col] = ret;
}
