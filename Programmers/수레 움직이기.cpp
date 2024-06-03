#include <vector>
#include <algorithm>

using namespace std;

const int MAX = 654321;
// left, top, right, bottom
const int dr[4] = {0, -1, 0, 1};
const int dc[4] = {-1, 0, 1, 0};

pair<int, int> red_dest, blue_dest;
int N, M;

bool equals(pair<int, int> &left, pair<int, int> &right)
{
    return (left.first == right.first) && (left.second == right.second);
}

bool check_range(int row, int col)
{
    return 0 <= row && row < N && 0 <= col && col < M;
}

bool can_go(int row, int col, vector<vector<int>> &maze, int color)
{
    // RED
    if (color > 0)
    {
        return maze[row][col] != 2 && maze[row][col] != 5;
    }
    // BLUE
    else if (color < 0)
    {
        return maze[row][col] != 1 && maze[row][col] != 5;
    }
    else
    {
        return false;
    }
}

int solve(pair<int, int> red_pos, pair<int, int> blue_pos, vector<vector<int>> &maze, vector<vector<int>> &visited)
{
    if (equals(red_pos, red_dest) && equals(blue_pos, blue_dest))
    {
        return 0;
    }

    int red_row = red_pos.first;
    int red_col = red_pos.second;
    int blue_row = blue_pos.first;
    int blue_col = blue_pos.second;

    int ret = MAX;
    // Red는 이미 도착한 경우
    if (equals(red_pos, red_dest))
    {
        visited[blue_row][blue_col] = (visited[blue_row][blue_col] | 2);

        for (int blue = 0; blue < 4; blue++)
        {
            int next_blue_row = blue_row + dr[blue];
            int next_blue_col = blue_col + dc[blue];

            if (check_range(next_blue_row, next_blue_col) && can_go(next_blue_row, next_blue_col, maze, -1) && (visited[next_blue_row][next_blue_col] & 2) != 2)
            {
                maze[blue_row][blue_col] = 0;
                maze[next_blue_row][next_blue_col] = 2;

                ret = min(ret, 1 + solve(red_pos, {next_blue_row, next_blue_col}, maze, visited));

                maze[next_blue_row][next_blue_col] = 0;
                maze[blue_row][blue_col] = 2;
            }
        }

        visited[blue_row][blue_col] = (visited[blue_row][blue_col] & (~2));
    }
    // Blue는 이미 도착한 경우
    else if (equals(blue_pos, blue_dest))
    {
        visited[red_row][red_col] = (visited[red_row][red_col] | 1);

        for (int red = 0; red < 4; red++)
        {
            int next_red_row = red_row + dr[red];
            int next_red_col = red_col + dc[red];

            if (check_range(next_red_row, next_red_col) && can_go(next_red_row, next_red_col, maze, 1) && (visited[next_red_row][next_red_col] & 1) != 1)
            {
                maze[red_row][red_col] = 0;
                maze[next_red_row][next_red_col] = 1;

                ret = min(ret, 1 + solve({next_red_row, next_red_col}, blue_pos, maze, visited));

                maze[next_red_row][next_red_col] = 0;
                maze[red_row][red_col] = 1;
            }
        }

        visited[red_row][red_col] = (visited[red_row][red_col] & (~1));
    }
    // 둘 다 아직 도착하지 않은 경우
    else
    {
        visited[red_row][red_col] = (visited[red_row][red_col] | 1);
        visited[blue_row][blue_col] = (visited[blue_row][blue_col] | 2);

        // Red 먼저 Blue 나중에
        for (int red = 0; red < 4; red++)
        {
            int next_red_row = red_row + dr[red];
            int next_red_col = red_col + dc[red];

            if (check_range(next_red_row, next_red_col) && can_go(next_red_row, next_red_col, maze, 1) && (visited[next_red_row][next_red_col] & 1) != 1)
            {
                maze[red_row][red_col] = 0;
                maze[next_red_row][next_red_col] = 1;
                for (int blue = 0; blue < 4; blue++)
                {
                    int next_blue_row = blue_row + dr[blue];
                    int next_blue_col = blue_col + dc[blue];

                    if (check_range(next_blue_row, next_blue_col) && can_go(next_blue_row, next_blue_col, maze, -1) && (visited[next_blue_row][next_blue_col] & 2) != 2)
                    {
                        maze[blue_row][blue_col] = 0;
                        maze[next_blue_row][next_blue_col] = 2;

                        ret = min(ret, 1 + solve({next_red_row, next_red_col}, {next_blue_row, next_blue_col}, maze, visited));

                        maze[next_blue_row][next_blue_col] = 0;
                        maze[blue_row][blue_col] = 2;
                    }
                }
                maze[next_red_row][next_red_col] = 0;
                maze[red_row][red_col] = 1;
            }
        }

        // Blue 먼저 Red 나중에
        for (int blue = 0; blue < 4; blue++)
        {
            int next_blue_row = blue_row + dr[blue];
            int next_blue_col = blue_col + dc[blue];

            if (check_range(next_blue_row, next_blue_col) && can_go(next_blue_row, next_blue_col, maze, -1) && (visited[next_blue_row][next_blue_col] & 2) != 2)
            {
                maze[blue_row][blue_col] = 0;
                maze[next_blue_row][next_blue_col] = 2;
                for (int red = 0; red < 4; red++)
                {
                    int next_red_row = red_row + dr[red];
                    int next_red_col = red_col + dc[red];
                    pair<int, int> next_red_pos = {next_red_row, next_red_col};

                    if (check_range(next_red_row, next_red_col) && can_go(next_red_row, next_red_col, maze, 1) && (visited[next_red_row][next_red_col] & 1) != 1)
                    {
                        maze[red_row][red_col] = 0;
                        maze[next_red_row][next_red_col] = 1;

                        ret = min(ret, 1 + solve({next_red_row, next_red_col}, {next_blue_row, next_blue_col}, maze, visited));

                        maze[next_red_row][next_red_col] = 0;
                        maze[red_row][red_col] = 1;
                    }
                }
                maze[next_blue_row][next_blue_col] = 0;
                maze[blue_row][blue_col] = 2;
            }
        }

        visited[red_row][red_col] = (visited[red_row][red_col] & (~1));
        visited[blue_row][blue_col] = (visited[blue_row][blue_col] & (~2));
    }

    return ret;
}

int solution(vector<vector<int>> maze)
{
    N = maze.size();
    M = maze[0].size();

    pair<int, int> red_pos, blue_pos;
    for (int row = 0; row < N; row++)
    {
        for (int col = 0; col < M; col++)
        {
            if (maze[row][col] == 1)
            {
                red_pos = {row, col};
            }
            else if (maze[row][col] == 2)
            {
                blue_pos = {row, col};
            }
            else if (maze[row][col] == 3)
            {
                red_dest = {row, col};
            }
            else if (maze[row][col] == 4)
            {
                blue_dest = {row, col};
            }
        }
    }

    vector<vector<int>> visited(N, vector<int>(M, 0));
    int answer = solve(red_pos, blue_pos, maze, visited);
    return answer >= MAX ? 0 : answer;
}
