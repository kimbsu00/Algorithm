#include <iostream>
#include <string>

using namespace std;

int N, M;
char map[4][4];
bool visited[4][4];

int solve(int row, int col)
{
    if (row == N)
    {
        return 0;
    }
    if (col == M)
    {
        return solve(row + 1, 0);
    }

    if (visited[row][col])
    {
        if (col + 1 == N)
        {
            return solve(row + 1, 0);
        }
        else
        {
            return solve(row, col + 1);
        }
    }

    int ret = 0;
    string num = "";
    int right = col;
    for (; right < M; right++)
    {
        if (visited[row][right])
        {
            break;
        }
        else
        {
            num += map[row][right];
            visited[row][right] = true;
            ret = max(ret, stoi(num) + solve(row, right + 1));
        }
    }
    for (int idx = col; idx < right; idx++)
    {
        visited[row][idx] = false;
    }

    int bottom = row;
    num.clear();
    for (; bottom < N; bottom++)
    {
        if (visited[bottom][col])
        {
            break;
        }
        else
        {
            num += map[bottom][col];
            visited[bottom][col] = true;
            ret = max(ret, stoi(num) + solve(row, col + 1));
        }
    }
    for (int idx = row; idx < bottom; idx++)
    {
        visited[idx][col] = false;
    }

    return ret;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    N = getchar() - '0';
    getchar();
    M = getchar() - '0';
    getchar();
    for (int row = 0; row < N; row++)
    {
        for (int col = 0; col < M; col++)
        {
            map[row][col] = getchar();
        }
        getchar();
    }

    int answer = solve(0, 0);
    printf("%d\n", answer);

    return 0;
}
