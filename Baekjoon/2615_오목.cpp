#include <iostream>

using namespace std;

int map[19][19];

int solve(int row, int col, int color, int dir, int cnt)
{
    if (row < 0 || row > 18 || col < 0 || col > 18)
        return cnt;

    // right
    if (dir == 0)
    {
        if (map[row][col] == color)
        {
            return solve(row, col + 1, color, dir, cnt + 1);
        }
        else
        {
            return cnt;
        }
    }
    // left
    else if (dir == 1)
    {
        if (map[row][col] == color)
        {
            return solve(row, col - 1, color, dir, cnt + 1);
        }
        else
        {
            return cnt;
        }
    }
    // top
    else if (dir == 2)
    {
        if (map[row][col] == color)
        {
            return solve(row - 1, col, color, dir, cnt + 1);
        }
        else
        {
            return cnt;
        }
    }
    // bottom
    else if (dir == 3)
    {
        if (map[row][col] == color)
        {
            return solve(row + 1, col, color, dir, cnt + 1);
        }
        else
        {
            return cnt;
        }
    }
    // right bottom
    else if (dir == 4)
    {
        if (map[row][col] == color)
        {
            return solve(row + 1, col + 1, color, dir, cnt + 1);
        }
        else
        {
            return cnt;
        }
    }
    // left top
    else if (dir == 5)
    {
        if (map[row][col] == color)
        {
            return solve(row - 1, col - 1, color, dir, cnt + 1);
        }
        else
        {
            return cnt;
        }
    }
    // right top
    else if (dir == 6)
    {

        if (map[row][col] == color)
        {
            return solve(row - 1, col + 1, color, dir, cnt + 1);
        }
        else
        {
            return cnt;
        }
    }
    // left bottom
    else if (dir == 7)
    {
        if (map[row][col] == color)
        {
            return solve(row + 1, col - 1, color, dir, cnt + 1);
        }
        else
        {
            return cnt;
        }
    }

    return cnt;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    fill(&map[0][0], &map[18][19], 0);

    for (int row = 0; row < 19; row++)
    {
        for (int col = 0; col < 19; col++)
        {
            cin >> map[row][col];
        }
    }

    int ans_row = -1;
    int ans_col = -1;
    for (int row = 0; row < 19; row++)
    {
        for (int col = 0; col < 19; col++)
        {
            if (map[row][col] != 0)
            {
                int color = map[row][col];
                int left2right = solve(row, col, color, 0, 0) + solve(row, col, color, 1, 0) - 1;
                int top2bottom = solve(row, col, color, 2, 0) + solve(row, col, color, 3, 0) - 1;
                int lt2rb = solve(row, col, color, 4, 0) + solve(row, col, color, 5, 0) - 1;
                int lb2rt = solve(row, col, color, 6, 0) + solve(row, col, color, 7, 0) - 1;

                if ((left2right == 5) || (top2bottom == 5) || (lt2rb == 5))
                {
                    ans_row = row;
                    ans_col = col;
                    break;
                }
                else if (lb2rt == 5)
                {
                    ans_row = row + 4;
                    ans_col = col - 4;
                    break;
                }
            }
        }
        if (ans_row != -1 && ans_col != -1)
            break;
    }

    if (ans_row == -1 || ans_col == -1)
    {
        cout << "0\n";
    }
    else
    {
        cout << map[ans_row][ans_col] << "\n";
        cout << (ans_row + 1) << " " << (ans_col + 1) << "\n";
    }

    return 0;
}
