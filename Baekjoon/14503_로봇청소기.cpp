#include <iostream>

using namespace std;

int N, M;
int map[50][50];

int solve(int row, int col, int dir)
{
    int ret = 0;
    if (map[row][col] == 0)
    {
        ret += 1;
        map[row][col] = -1;
    }

    for (int bias = 1; bias <= 4; bias++)
    {
        int new_dir = (dir - bias + 4) % 4;

        switch (new_dir)
        {
            // NORTH
        case 0:
            if (map[row - 1][col] == 0)
            {
                return ret + solve(row - 1, col, new_dir);
            }
            break;
            // EAST
        case 1:
            if (map[row][col + 1] == 0)
            {
                return ret + solve(row, col + 1, new_dir);
            }
            break;
            // SOUTH
        case 2:
            if (map[row + 1][col] == 0)
            {
                return ret + solve(row + 1, col, new_dir);
            }
            break;
            // WEST
        case 3:
            if (map[row][col - 1] == 0)
            {
                return ret + solve(row, col - 1, new_dir);
            }
            break;
        }
    }

    switch (dir)
    {
        // NORTH
    case 0:
        if (map[row + 1][col] != 1)
        {
            ret += solve(row + 1, col, dir);
        }
        break;
        // EAST
    case 1:
        if (map[row][col - 1] != 1)
        {
            ret += solve(row, col - 1, dir);
        }
        break;
        // SOUTH
    case 2:
        if (map[row - 1][col] != 1)
        {
            ret += solve(row - 1, col, dir);
        }
        break;
        // WEST
    case 3:
        if (map[row][col + 1] != 1)
        {
            ret += solve(row, col + 1, dir);
        }
        break;
    }

    return ret;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    fill(&map[0][0], &map[40][50], 1);
    cin >> N >> M;

    /**
     * (0, NORTH)
     * (1, EAST)
     * (2, SOUTH)
     * (3, WEST)
     */
    int robot_dir = 0;
    int robot_row, robot_col;
    cin >> robot_row >> robot_col >> robot_dir;

    for (int row = 0; row < N; row++)
    {
        for (int col = 0; col < M; col++)
        {
            cin >> map[row][col];
        }
    }

    int answer = solve(robot_row, robot_col, robot_dir);
    cout << answer << "\n";

    return 0;
}
