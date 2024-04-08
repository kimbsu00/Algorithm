#include <iostream>
#include <vector>
#include <queue>

using namespace std;

enum Direction
{
    LEFT,
    UP,
    RIGHT,
    DOWN
} typedef direction;

struct Heater
{
    int row, col, dir;
} typedef heater;

struct Position
{
    int row, col;
} typedef position;

struct State
{
    int row, col, temp;
} typedef state;

/**
 *  [Direction][idx]
 */
const int dr[4][3] = {
    {-1, 0, 1},   // LEFT
    {-1, -1, -1}, // UP
    {-1, 0, 1},   // RIGHT
    {1, 1, 1}     // DOWN
};
const int dc[4][3] = {
    {-1, -1, -1}, // LEFT
    {-1, 0, 1},   // UP
    {1, 1, 1},    // RIGHT
    {-1, 0, 1}    // DOWN
};

int R, C, K, W;
vector<vector<int>> temp;
vector<heater> heaters;
vector<position> searching_area;
/**
 * 1 -> 왼쪽에 벽
 * 2 -> 위쪽에 벽
 * 4 -> 오른쪽에 벽
 * 8 -> 아래쪽에 벽
 */
vector<vector<int>> wall;

void print_map(vector<vector<int>> &map)
{
    printf("\n");
    for (int row = 0; row < R; row++)
    {
        for (int col = 0; col < C; col++)
        {
            printf("%d ", map[row][col]);
        }
        printf("\n");
    }
    printf("\n");
}

bool check_range(int row, int col)
{
    return 0 <= row && row < R && 0 <= col && col < C;
}

bool check_wall(int row, int col, int dir, int type)
{
    if (dir == LEFT)
    {
        // UP - LEFT
        if (type == 0)
        {
            return ((wall[row][col] & 2) | (wall[row - 1][col] & 1)) > 0;
        }
        // LEFT
        else if (type == 1)
        {
            return (wall[row][col] & 1) > 0;
        }
        // DOWN - LEFT
        else if (type == 2)
        {
            return ((wall[row][col] & 8) | (wall[row + 1][col] & 1)) > 0;
        }
    }
    else if (dir == UP)
    {
        // LEFT - UP
        if (type == 0)
        {
            return ((wall[row][col] & 1) | (wall[row][col - 1] & 2)) > 0;
        }
        // UP
        else if (type == 1)
        {
            return (wall[row][col] & 2) > 0;
        }
        // RIGHT - UP
        else if (type == 2)
        {
            return ((wall[row][col] & 4) | (wall[row][col + 1] & 2)) > 0;
        }
    }
    else if (dir == RIGHT)
    {
        // UP - RIGHT
        if (type == 0)
        {
            return ((wall[row][col] & 2) | (wall[row - 1][col] & 4)) > 0;
        }
        // RIGHT
        else if (type == 1)
        {
            return (wall[row][col] & 4) > 0;
        }
        // DOWN - RIGHT
        else if (type == 2)
        {
            return ((wall[row][col] & 8) | (wall[row + 1][col] & 4)) > 0;
        }
    }
    else if (dir == DOWN)
    {
        // LEFT - DOWN
        if (type == 0)
        {
            return ((wall[row][col] & 1) | (wall[row][col - 1] & 8)) > 0;
        }
        // DOWN
        else if (type == 1)
        {
            return (wall[row][col] & 8) > 0;
        }
        // RIGHT - DOWN
        else if (type == 2)
        {
            return ((wall[row][col] & 4) | (wall[row][col + 1] & 8)) > 0;
        }
    }
    return false;
}

void heater_on()
{
    int visited[20][20];
    for (heater machine : heaters)
    {
        int dir = machine.dir;
        if (check_wall(machine.row, machine.col, dir, 1))
        {
            continue;
        }

        fill(&visited[0][0], &visited[19][20], false);

        queue<state> q;
        q.push({machine.row + dr[dir][1], machine.col + dc[dir][1], 5});

        while (!q.empty())
        {
            state front = q.front();
            q.pop();
            temp[front.row][front.col] += front.temp;

            if (front.temp == 1)
            {
                continue;
            }

            for (int idx = 0; idx < 3; idx++)
            {
                int next_row = front.row + dr[dir][idx];
                int next_col = front.col + dc[dir][idx];

                if (check_range(next_row, next_col) && !visited[next_row][next_col])
                {
                    if (!check_wall(front.row, front.col, dir, idx))
                    {
                        visited[next_row][next_col] = true;
                        q.push({next_row, next_col, front.temp - 1});
                    }
                }
            }
        }
    }
}

void temperature_control()
{
    int add_temp[20][20];
    fill(&add_temp[0][0], &add_temp[19][20], 0);
    for (int row = 0; row < R; row++)
    {
        for (int col = 0; col < C; col++)
        {
            int left_row = row;
            int left_col = col - 1;
            if (check_range(left_row, left_col) && !check_wall(row, col, LEFT, 1))
            {
                int diff = temp[left_row][left_col] - temp[row][col];
                add_temp[row][col] += diff / 4;
            }

            int up_row = row - 1;
            int up_col = col;
            if (check_range(up_row, up_col) && !check_wall(row, col, UP, 1))
            {
                int diff = temp[up_row][up_col] - temp[row][col];
                add_temp[row][col] += diff / 4;
            }

            int right_row = row;
            int right_col = col + 1;
            if (check_range(right_row, right_col) && !check_wall(row, col, RIGHT, 1))
            {
                int diff = temp[right_row][right_col] - temp[row][col];
                add_temp[row][col] += diff / 4;
            }

            int down_row = row + 1;
            int down_col = col;
            if (check_range(down_row, down_col) && !check_wall(row, col, DOWN, 1))
            {
                int diff = temp[down_row][down_col] - temp[row][col];
                add_temp[row][col] += diff / 4;
            }
        }
    }

    for (int row = 0; row < R; row++)
    {
        for (int col = 0; col < C; col++)
        {
            temp[row][col] += add_temp[row][col];
        }
    }
}

void temperature_down()
{
    if (temp[0][0] > 0)
    {
        temp[0][0] -= 1;
    }
    if (temp[0][C - 1] > 0)
    {
        temp[0][C - 1] -= 1;
    }
    if (temp[R - 1][0] > 0)
    {
        temp[R - 1][0] -= 1;
    }
    if (temp[R - 1][C - 1] > 0)
    {
        temp[R - 1][C - 1] -= 1;
    }
    for (int row = 1; row < R - 1; row++)
    {
        if (temp[row][0] > 0)
        {
            temp[row][0] -= 1;
        }
        if (temp[row][C - 1] > 0)
        {
            temp[row][C - 1] -= 1;
        }
    }
    for (int col = 1; col < C - 1; col++)
    {
        if (temp[0][col] > 0)
        {
            temp[0][col] -= 1;
        }
        if (temp[R - 1][col] > 0)
        {
            temp[R - 1][col] -= 1;
        }
    }
}

bool check_searching_area()
{
    for (position pos : searching_area)
    {
        if (temp[pos.row][pos.col] < K)
        {
            return false;
        }
    }
    return true;
}

int solve()
{
    // getchar();
    int chocolate = 0;
    while (chocolate <= 100)
    {
        heater_on();
        // print_map(temp);
        temperature_control();
        // print_map(temp);
        temperature_down();
        // print_map(temp);
        chocolate += 1;
        if (check_searching_area())
        {
            break;
        }
        // getchar();
    }
    return chocolate;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> R >> C >> K;
    temp = vector<vector<int>>(R, vector<int>(C, 0));
    wall = vector<vector<int>>(R, vector<int>(C, 0));

    int input;
    for (int row = 0; row < R; row++)
    {
        for (int col = 0; col < C; col++)
        {
            cin >> input;

            switch (input)
            {
            case 1:
                heaters.push_back({row, col, RIGHT});
                break;

            case 2:
                heaters.push_back({row, col, LEFT});
                break;

            case 3:
                heaters.push_back({row, col, UP});
                break;

            case 4:
                heaters.push_back({row, col, DOWN});
                break;

            case 5:
                searching_area.push_back({row, col});
                break;
            }
        }
    }

    cin >> W;
    int row, col, t;
    for (int idx = 0; idx < W; idx++)
    {
        cin >> row >> col >> t;
        row -= 1;
        col -= 1;

        // (row, col) 위쪽에 벽
        if (t == 0)
        {
            wall[row][col] |= 2;
            wall[row - 1][col] |= 8;
        }
        // (row, col) 오른쪽에 벽
        else if (t == 1)
        {
            wall[row][col] |= 4;
            wall[row][col + 1] |= 1;
        }
    }
    // print_map(wall);

    int answer = solve();
    printf("%d\n", answer);

    return 0;
}
