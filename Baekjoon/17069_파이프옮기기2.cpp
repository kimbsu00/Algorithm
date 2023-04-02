#include <iostream>

using namespace std;

int N;
int house[34][34];
long long pipe[34][34][3];

long long solve(int s_row, int s_col, int e_row, int e_col)
{
    if (house[s_row][s_col] == 1 || house[e_row][e_col] == 1)
    {
        return 0;
    }
    else if ((s_row == N && s_col == N) || (e_row == N && e_col == N))
    {
        return 1;
    }

    // 가로로 배치된 경우
    if ((s_row == e_row) && (s_col + 1 == e_col))
    {
        long long &ret = pipe[s_row][s_col][0];
        if (ret != -1)
            return ret;

        ret = 0;
        // 오른쪽으로 미는 경우
        if (house[e_row][e_col + 1] == 0)
            ret += solve(s_row, s_col + 1, e_row, e_col + 1);
        // 오른쪽으로 밀고 시계 방향으로 45도 회전하는 경우
        if (house[e_row][e_col + 1] == 0 && house[e_row + 1][e_col] == 0 && house[e_row + 1][e_col + 1] == 0)
            ret += solve(s_row, s_col + 1, e_row + 1, e_col + 1);

        return ret;
    }
    // 세로로 배치된 경우
    else if ((s_row + 1 == e_row) && (s_col == e_col))
    {
        long long &ret = pipe[s_row][s_col][1];
        if (ret != -1)
            return ret;

        ret = 0;
        // 아래로 미는 경우
        if (house[e_row + 1][e_col] == 0)
            ret += solve(s_row + 1, s_col, e_row + 1, e_col);
        // 아래로 밀고 시계 반대 방향으로 45도 회전하는 경우
        if (house[e_row + 1][e_col] == 0 && house[e_row][e_col + 1] == 0 && house[e_row + 1][e_col + 1] == 0)
            ret += solve(s_row + 1, s_col, e_row + 1, e_col + 1);

        return ret;
    }
    // 대각선으로 배치된 경우
    else if ((s_row + 1 == e_row) && (s_col + 1 == e_col))
    {
        long long &ret = pipe[s_row][s_col][2];
        if (ret != -1)
            return ret;

        ret = 0;
        // 대각선으로 밀고 시계 반대 방향으로 45도 회전하는 경우
        if (house[e_row][e_col + 1] == 0)
            ret += solve(s_row + 1, s_col + 1, e_row, e_col + 1);
        // 대각선으로 밀고 시계 방향을 45도 회전하는 경우
        if (house[e_row + 1][e_col] == 0)
            ret += solve(s_row + 1, s_col + 1, e_row + 1, e_col);
        // 대각선으로 미는 경우
        if (house[e_row][e_col + 1] == 0 && house[e_row + 1][e_col] == 0 && house[e_row + 1][e_col + 1] == 0)
            ret += solve(s_row + 1, s_col + 1, e_row + 1, e_col + 1);

        return ret;
    }
    // 그 외의 경우, Exception
    else
    {
        return 0;
    }
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;

    fill(&house[0][0], &house[33][34], 1);
    fill(&pipe[0][0][0], &pipe[33][33][3], -1);

    for (int row = 1; row <= N; row++)
    {
        for (int col = 1; col <= N; col++)
        {
            cin >> house[row][col];
        }
    }

    cout << solve(1, 1, 1, 2) << "\n";

    return 0;
}
