#include <iostream>

using namespace std;

int N, M;
int **map;
bool **visited;
int dr[4] = {0, -1, 0, 1};
int dc[4] = {-1, 0, 1, 0};

int solve(int row, int col, int sum, int cnt)
{
    if (cnt >= 4)
    {
        return sum;
    }

    visited[row][col] = true;
    int ret = sum;
    for (int idx = 0; idx < 4; idx++)
    {
        int next_row = row + dr[idx];
        int next_col = col + dc[idx];

        if (next_row >= 0 && next_row < N && next_col >= 0 && next_col < M && !visited[next_row][next_col])
        {
            int tmp = solve(next_row, next_col, sum + map[row][col], cnt + 1);
            ret = max(ret, tmp);
        }
    }

    if (cnt == 1)
    {
        if (col - 1 >= 0 && visited[row][col - 1] && row - 1 >= 0 && row + 1 < N)
        {
            int top = map[row - 1][col];
            int bottom = map[row + 1][col];
            ret = max(ret, sum + map[row][col] + top + bottom);
        }

        if (row - 1 >= 0 && visited[row - 1][col] && col - 1 >= 0 && col + 1 < M)
        {
            int left = map[row][col - 1];
            int right = map[row][col + 1];
            ret = max(ret, sum + map[row][col] + left + right);
        }

        if (col + 1 < M && visited[row][col + 1] && row - 1 >= 0 && row + 1 < N)
        {
            int top = map[row - 1][col];
            int bottom = map[row + 1][col];
            ret = max(ret, sum + map[row][col] + top + bottom);
        }

        if (row + 1 < N && visited[row + 1][col] && col - 1 >= 0 && col + 1 < M)
        {
            int left = map[row][col - 1];
            int right = map[row][col + 1];
            ret = max(ret, sum + map[row][col] + left + right);
        }
    }

    visited[row][col] = false;

    return ret;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N >> M;

    map = new int *[N];
    visited = new bool *[N];
    for (int row = 0; row < N; row++)
    {
        map[row] = new int[M];
        visited[row] = new bool[M];
    }

    for (int row = 0; row < N; row++)
    {
        for (int col = 0; col < M; col++)
        {
            cin >> map[row][col];
            visited[row][col] = false;
        }
    }

    int answer = -1;
    for (int row = 0; row < N; row++)
    {
        for (int col = 0; col < M; col++)
        {
            answer = max(answer, solve(row, col, 0, 0));
        }
    }

    cout << answer << "\n";

    return 0;
}
