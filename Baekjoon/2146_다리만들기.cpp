#include <iostream>
#include <vector>
#include <queue>
#include <algorithm>

using namespace std;

class Node
{
public:
    int row, col;
    int distance;

    Node() : row(-1), col(-1), distance(-1) {}

    Node(int p_row, int p_col, int p_distance) : row(p_row), col(p_col), distance(p_distance) {}
};

// left, top, right, bottom
const int dr[4] = {0, -1, 0, 1};
const int dc[4] = {-1, 0, 1, 0};

int N;
vector<vector<int>> map;
vector<vector<bool>> visited;

bool check_range(int row, int col)
{
    return (0 <= row && row < map.size() && 0 <= col && col < map.size());
}

void dfs(int row, int col, int group)
{
    map[row][col] = group;

    for (int idx = 0; idx < 4; idx++)
    {
        int next_row = row + dr[idx];
        int next_col = col + dc[idx];

        if (check_range(next_row, next_col) && map[next_row][next_col] == 1)
        {
            dfs(next_row, next_col, group);
        }
    }
}

int solve(int row, int col, int group)
{
    visited = vector<vector<bool>>(N, vector<bool>(N, false));

    queue<Node> q;
    visited[row][col] = true;
    q.push(Node(row, col, 0));

    while (!q.empty())
    {
        Node node = q.front();
        q.pop();

        for (int idx = 0; idx < 4; idx++)
        {
            int next_row = node.row + dr[idx];
            int next_col = node.col + dc[idx];

            if (check_range(next_row, next_col) && !visited[next_row][next_col] && map[next_row][next_col] != group)
            {
                if (map[next_row][next_col] == 0)
                {
                    visited[next_row][next_col] = true;
                    q.push(Node(next_row, next_col, node.distance + 1));
                }
                else
                {
                    return node.distance;
                }
            }
        }
    }

    return 987654321;
}

int main(void)
{
    ios_base::sync_with_stdio(0);
    cin.tie(0);

    cin >> N;

    map = vector<vector<int>>(N, vector<int>(N));
    visited = vector<vector<bool>>(N, vector<bool>(N, false));

    for (int row = 0; row < N; row++)
    {
        for (int col = 0; col < N; col++)
        {
            cin >> map[row][col];
        }
    }

    int group = 2;
    for (int row = 0; row < N; row++)
    {
        for (int col = 0; col < N; col++)
        {
            if (map[row][col] == 1)
            {
                dfs(row, col, group);
                group += 1;
            }
        }
    }

    int answer = 987654321;
    for (int row = 0; row < N; row++)
    {
        for (int col = 0; col < N; col++)
        {
            if (map[row][col] > 1)
            {
                int flag = false;
                for (int idx = 0; idx < 4; idx++)
                {
                    int next_row = row + dr[idx];
                    int next_col = col + dr[idx];

                    if (check_range(next_row, next_col) && map[next_row][next_col] != map[row][col])
                    {
                        flag = true;
                        break;
                    }
                }

                if (flag)
                {
                    answer = min(answer, solve(row, col, map[row][col]));
                }
            }
        }
    }

    cout << answer << "\n";

    return 0;
}
