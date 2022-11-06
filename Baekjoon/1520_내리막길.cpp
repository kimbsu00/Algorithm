/*
  url: https://www.acmicpc.net/problem/1520
*/

#include <iostream>

using namespace std;

int M, N;
int map[502][502];
int cache[502][502];

int solve(int row, int col)
{
    if (row == M && col == N)
        return 1;

    int &ret = cache[row][col];
    if (ret != -1)
        return ret;

    ret = 0;
    int cur_height = map[row][col];
    // left
    if (map[row][col - 1] < cur_height)
    {
        ret += solve(row, col - 1);
    }
    // top
    if (map[row - 1][col] < cur_height)
    {
        ret += solve(row - 1, col);
    }
    // right
    if (map[row][col + 1] < cur_height)
    {
        ret += solve(row, col + 1);
    }
    // bottom
    if (map[row + 1][col] < cur_height)
    {
        ret += solve(row + 1, col);
    }

    return ret;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> M >> N;

    fill(&map[0][0], &map[501][502], 987654321);
    fill(&cache[0][0], &cache[501][502], -1);

    for (int row = 1; row <= M; row++)
    {
        for (int col = 1; col <= N; col++)
        {
            cin >> map[row][col];
        }
    }

    cout << solve(1, 1) << "\n";

    return 0;
}
