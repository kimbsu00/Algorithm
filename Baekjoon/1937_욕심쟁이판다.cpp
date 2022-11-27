/*
  url: https://www.acmicpc.net/problem/1937
*/

#include <iostream>
#include <algorithm>

using namespace std;

// left, top, right, bottom
const int dx[4] = {-1, 0, 1, 0};
const int dy[4] = {0, -1, 0, 1};

int N;
int forest[502][502];
int cache[502][502];

// forest[row][col] 에서 시작했을 때, 판다가 이동할 수 있는 칸의 최대 값을 리턴하는 함수
int solve(int row, int col)
{
    int &ret = cache[row][col];
    if (ret != -1)
        return ret;

    ret = 1;
    for (int idx = 0; idx < 4; idx++)
    {
        int next_row = row + dx[idx];
        int next_col = col + dy[idx];

        if (forest[row][col] < forest[next_row][next_col])
            ret = max(ret, 1 + solve(next_row, next_col));
    }

    return ret;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    fill(&forest[0][0], &forest[501][502], -1);
    fill(&cache[0][0], &cache[501][502], -1);

    cin >> N;
    for (int row = 1; row <= N; row++)
    {
        for (int col = 1; col <= N; col++)
        {
            cin >> forest[row][col];
        }
    }

    int answer = -1;
    for (int row = 1; row <= N; row++)
    {
        for (int col = 1; col <= N; col++)
        {
            answer = max(answer, solve(row, col));
        }
    }
    cout << answer << "\n";

    return 0;
}
